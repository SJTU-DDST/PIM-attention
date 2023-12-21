#ifndef __VECTOR_H
#define __VECTOR_H

#include <cstdint>
#include <iostream>
#include "../model/model.h"

template <typename Type> class vector;
template <typename Type> std::ostream &operator<<(std::ostream &os, const vector<Type> &a);

template <typename Type>
class vector
{
private:
    Type data[DIM_HEAD];

public:
    vector(Type elem = 1);
    void vector_copy_add(const vector<Type> &b, Type k);
    const Type operator*(const vector<Type> &b);
    friend std::ostream &operator<<<Type>(std::ostream &os, const vector<Type> &a);
    ~vector() {}
};

template <typename Type>
vector<Type>::vector(Type elem)
{
    for (int i = 0; i < DIM_HEAD; i++)
    {
        this->data[i] = elem;
    }
}

template <typename Type>
void vector<Type>::vector_copy_add(const vector<Type> &b, Type k)
{
    for (int i = 0; i < DIM_HEAD; i++)
    {
        this->data[i] += k * b.data[i];
    }
}

template <typename Type>
const Type vector<Type>::operator*(const vector<Type> &b)
{
    Type ans = 0;
    for (int i = 0; i < DIM_HEAD; i++)
    {
        ans += this->data[i] * b.data[i];
    }
    return ans;
}

template <typename Type>
std::ostream &operator<<(std::ostream &os, const vector<Type> &a)
{
    for (int i = 0; i < DIM_HEAD; i++)
    {
        std::cout << a.data[i] << " ";
    }
    std::cout << std::endl;
    return os;
}

#endif