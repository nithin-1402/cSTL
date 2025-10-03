/*
    MIT License

    Copyright (c) 2025 Nithin M

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/* SPDX-License-Identifier: MIT */

#pragma once

#ifndef CSTL_BITSET_H
#define CSTL_BITSET_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    uint8_t* bitset; // pointer to user-provided memory
    size_t size;     // number of bits
} cBitset;

/* Get the minimum required bytes to store num_bits */
#define CBITSET_SIZE(num_bits) ((num_bits + 7) / 8)

#define CBITSET_CREATE(bitset, num_bits)                                                           \
    uint8_t bitset##_buf[CBITSET_SIZE(num_bits)];                                                  \
    cBitset bitset;                                                                                \
    cBitset_init_from_buffer(&bitset, bitset##_buf, num_bits);

/* Initialize a cBitset with your buffer, the buffer is zeroed
NOTE: The buffer must be large enough to accomodate num_bits, use CBITSET_SIZE() to get the min
required buffer size */
static inline void cBitset_init_from_buffer(cBitset* bits, uint8_t* buffer, const size_t num_bits)
{
    bits->bitset = buffer;
    bits->size = num_bits;
    memset(bits->bitset, 0, CBITSET_SIZE(bits->size));
}

/* Set all bits to 0 */
static inline void cBitset_clear_all(cBitset* bits)
{

    memset(bits->bitset, 0, CBITSET_SIZE(bits->size));
}

/* Set all bits to 1 */
static inline void cBitset_set_all(cBitset* bits)
{
    memset(bits->bitset, 0xFF, CBITSET_SIZE(bits->size));
}

/* Read the nth bit of the bitset (index starts from 0) */
static inline bool cBitset_readbit(const cBitset* bits, const size_t n)
{
    if (n >= bits->size)
        return false;
    return (bits->bitset[n / 8] >> (n % 8)) & 1U;
}

/* Set the nth bit of the bitset to 1 (index starts from 0) */
static inline void cBitset_setbit(cBitset* bits, const size_t n)
{
    if (n >= bits->size)
        return;
    bits->bitset[n / 8] |= (uint8_t) (1U << (n % 8));
}

/* Set the nth bit of the bitset to 0 (index starts from 0) */
static inline void cBitset_clearbit(cBitset* bits, const size_t n)
{
    if (n >= bits->size)
        return;
    bits->bitset[n / 8] &= (uint8_t) (~(1U << (n % 8)));
}

/* Toggle the nth bit of the bitset (index starts from 0) */
static inline void cBitset_togglebit(cBitset* bits, const size_t n)
{
    if (n >= bits->size)
        return;
    bits->bitset[n / 8] ^= (uint8_t) (1U << (n % 8));
}

#ifdef __cplusplus
}
#endif

#endif // CSTL_BITSET_H
