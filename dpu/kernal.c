#include <stdio.h>
#include <barrier.h>
#include "../util/util.h"
#include "shared_wram_vars.h"
#include "test.h"
#include "op_k.h"
#include "op_norm.h"
#include "op_v.h"

BARRIER_INIT(barrier1, NR_TASKLETS);
BARRIER_INIT(barrier2, NR_TASKLETS);
BARRIER_INIT(barrier3, NR_TASKLETS);
BARRIER_INIT(barrier4, NR_TASKLETS);

int master()
{
    mem_reset();
    if (!global_init_flag)
    {
        kv_cache_init(global_KV_cache, 1);
        global_init_flag = 1;
    }
    // vector_cache cache;
    // vector_cache_init(&cache, 1);
    // vector_store(&cache, global_Q_vector);
    barrier_wait(&barrier1);
    barrier_wait(&barrier2);
    barrier_wait(&barrier3);
    barrier_wait(&barrier4);

    op_v_reduce();

    // vector_dump(global_O_vector);

    return 0;
}

int slave()
{
    barrier_wait(&barrier1);
    op_k_run();
    barrier_wait(&barrier2);
    op_norm_run();
    barrier_wait(&barrier3);
    op_v_run();
    barrier_wait(&barrier4);
    return 0;
}

int main()
{
    return me() == 0 ? master() : slave();
}