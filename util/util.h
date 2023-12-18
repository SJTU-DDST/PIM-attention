#ifndef __UTIL_H
#define __UTIL_H
#include <stdint.h>
#include <stddef.h>
#include<stdlib.h>

// Find the lowest index for the rank-th group
#define BLOCK_LOW(rank, size, n) ((rank) * (n) / (size))

// Find the highest index for the rank-th group
#define BLOCK_HIGH(rank, size, n) (BLOCK_LOW((rank) + 1, (size), (n)) - 1)

#define BLOCK_SIZE(id, p, n) \
	(BLOCK_LOW((id) + 1, p, n) - BLOCK_LOW((id), p, n))

uint32_t align8(uint32_t s);

uint32_t next_power(uint32_t size);


#endif