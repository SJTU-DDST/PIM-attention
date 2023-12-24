# Benchmarking PIM-attention: A Puncture Experiment on a Real Processing-in-Memory Architecture

大语言模型（LLM）的高吞吐量服务需要一次批处理足够多的请求。然而，现有的推理系统面临着巨大的挑战。一方面，每个请求的键值缓存（KV cache）占用大量的内存，而且会动态增长和收缩，显存容量不足限制了批处理的大小；另一方面，attention算法中大量使用访存密集型的GEMV算子，显存带宽成为了系统瓶颈。为了解决这个问题，我们提出了PIM-attention。PIM提供了更大的内存容量和bank级并行的访存带宽，为加速attention算子提供了机遇。本文介绍了PIM-attention的设计，并且在商用PIM设备上实现了该算法。实验结果表明，PIM-attention可以有效加速

## 1 Attention in Transformer

生成式generative模型基于Transformer模型。我们给一个输入文本，模型会输出一个回答（长度为N），其实该过程中执行了N次推理过程。即GPT类模型一次推理只输出一个token，输出的token会与输入tokens 拼接在一起，然后作为下一次推理的输入，这样不断反复直到遇到终止符。在推理下一个token的过程中，Transformer模型使用了attention算法。

### 1.1 attention

下图（左）展示了输入一个长度为4的文本，生成下一个token的过程。输入的4个token【你】【爱】【我】【吗】，会嵌入到Transformer，生成4个向量$[a^{1}, a^{2}, a^{3}, a^{4}]$。4个向量$[a^{1}, a^{2}, a^{3}, a^{4}]$再生成4个key向量$[k^{1}, k^{2}, k^{3}, k^{4}]$和4个val向量$[v^{1}, v^{2}, v^{3}, v^{4}]$。输入中最后一个token会生成一个query向量$q$。

1. $q$分别与$[k^{1}, k^{2}, k^{3}, k^{4}]$进行向量内积操作，生成$[\alpha^{1}, \alpha^{2}, \alpha^{3}, \alpha^{4}]$。以$\alpha^{1}$为例进行解释，$\alpha^{1}=q[0]×k^{1}[0]+q[1]×k^{1}[1]+\cdots + q[n]×k^{1}[n]$。$\alpha^{1}$表示$a^{4}$和$a^{1}$之间的相关性。
2. 对$[\alpha^{1}, \alpha^{2}, \alpha^{3}, \alpha^{4}]$进行Norm操作。对它们进行normalization，使其转换为均值为0，方差为1的数据。
3. $b=\sum_{i}^{} \alpha ^{i} v^{i}$。根据输入向量间的相关性，计算出下一个token是【?】。

如下图（右），继续产生下一个token。上次的输出作为了本次推理的输入。其它的步骤就和上次推理完全一致。

![](https://github.com/mryvae/picture_bed/assets/83715643/e266e7a7-edad-4a50-94e5-f09e6aaf8dd7)

其实不难看出，在推理的过程中，一个token对应一个key向量和一个val向量。聪明的读者肯定发现了，这些key向量和val向量在推理过程中进行了大量的复用。如果本次推理产生了N个token，向量$k^{1}$和$v^{1}$就会被复用N次。如果我们能够把这些key向量和val向量保存下来，就可以大大提升推理效率。

这也就催生出了KV cache这个数据结构。KV cache其实就是用来保存在推理过程中的产生的key向量和val向量。

### 1.2 Multi-head attention

上述的attention算法仅仅是为了便于读者理解attention机制。在实际应用中的attention算法要更复杂，一般使用的是Multi-head attention。

在Multi-head attention，一个token对应NUM_HEAD个key向量和val向量。如下图，这一个NUM_HEAD=2的示例。输出的向量$b$由NUM_HEAD部分组成。注意，$b^{2}$的生成过程仅与一个head对应的key向量$[k^{1,2}, k^{2,2}, k^{3,2}, k^{4,2}]$和val向量$[v^{1,2}, v^{2,2}, v^{3,2}, v^{4,2}]$相关。其实，上节描述的attention就是NUM_HEAD=1的特例。

![](https://github.com/mryvae/picture_bed/assets/83715643/8127f2c9-9a1b-4138-bee5-c19898c51e94)

在llama2-7B和mpt-7B模型中，NUM_HEAD=32，向量$k^{i,j}$和$v^{i,j}$的长度为128。

## 2 Design

PIM系统首要考虑的便是数据划分。对于一个请求，系统需要维护NUM_HEAD×N个key和val向量，其中N为token的数量。如下图，当前的设计是按head进行划分，一个head对应一个PIM进行处理。如果在token维度进行切分，那么，Norm操作就需要Host端完成。

![](https://github.com/mryvae/picture_bed/assets/83715643/8ec215ee-5727-4825-a2ee-672bde279b55)

对于batch请求查询，则分配BATCH_SIZE×NUM_HEAD个DPU进行处理。

## 3 Evaluation

使用Intel(R) Xeon(R) Silver 4126 CPU和商用存算器件UPMEM。因为UPMEM不支持浮点运算，因此，将模型参数量化为了INT32 INT16 INT8类型进行测试。推理的sequence长度设置为了4096。

UPMEM 1024 DPU vs. 1 CPU socket (32 core)

INT32，运行时间如下表：

|               | batch size=2 | batch size=4 | batch size=8 | batch size=16 | batch size=32 |
| ------------- | ------------ | ------------ | ------------ | ------------- | ------------- |
| CPU-1 thread  | 36149        | 71122        | 144240       | 292320        | 575002        |
| CPU-2 thread  | 31808        | 50524        | 89443        | 167569        | 320905        |
| CPU-4 thread  | 20115        | 35302        | 67075        | 129761        | 255217        |
| CPU-8 thread  | 17562        | 34796        | 68711        | 135376        | 270380        |
| CPU-16 thread | 19967        | 38184        | 74054        | 143600        | 285429        |
| CPU-32 thread | 45081        | 57341        | 90032        | 162256        | 307577        |
| UPMEM         | 50595        | 50698        | 50733        | 51366         | 51326         |

INT16，运行时间如下表：

|              | batch size=2 | batch size=4 | batch size=8 | batch size=16 | batch size=32 |
| ------------ | ------------ | ------------ | ------------ | ------------- | ------------- |
| CPU-1 thread | 13432        | 26075        | 51847        | 104472        | 226658        |
| CPU-4 thread | 8826         | 17243        | 33434        | 65890         | 130330        |
| CPU-8 thread | 9388         | 18220        | 36184        | 70694         | 139735        |
| UPMEM        | 27666        | 27701        | 27785        | 28171         | 28656         |

INT8，运行时间如下表：

|              | batch size=2 | batch size=4 | batch size=8 | batch size=16 | batch size=32 |
| ------------ | ------------ | ------------ | ------------ | ------------- | ------------- |
| CPU-1 thread | 9792         | 17157        | 33279        | 67277         | 134062        |
| CPU-4 thread | 6050         | 11352        | 20818        | 34323         | 65852         |
| CPU-8 thread | 5016         | 9254         | 17418        | 34908         | 68823         |
| UPMEM        | 28759        | 28814        | 28854        | 29104         | 29764         |

结论：

MPT-7B模型，针对attention算子【不是端到端】，推理batch size = 32时，

模型参数量化为INT32，最高可以取得4.97倍加速比

模型参数量化为INT16，最高可以取得4.54倍加速比

模型参数量化为INT8，最高可以取得2.21倍加速比







