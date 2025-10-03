#include "cBitset.h"
#include <stdio.h>

#define NUM_BITS 10

static void print_bitset(const cBitset* bitset)
{
    for (int i = (bitset->size - 1); i >= 0; i--)
    {
        printf("%d", cBitset_readbit(bitset, i));
        if ((i % 4) == 0)
            printf(" ");
    }
    printf("\n");
}

int main(void)
{
    CBITSET_CREATE(bitset, NUM_BITS)

    // set one bit
    printf("---- Set bit ----\n");
    cBitset_setbit(&bitset, 1);
    print_bitset(&bitset);
    printf("\n");

    // clear a bit
    printf("---- Clear bit ----\n");
    cBitset_clearbit(&bitset, 1);
    print_bitset(&bitset);
    printf("\n");

    // toggle a bit twice
    printf("---- Toggle bit ----\n");
    cBitset_togglebit(&bitset, 8);
    print_bitset(&bitset);
    cBitset_togglebit(&bitset, 8);
    print_bitset(&bitset);
    printf("\n");

    // clear out of bounds
    printf("---- Out of bounds clear ----\n");
    cBitset_clearbit(&bitset, 11);
    print_bitset(&bitset);
    printf("\n");

    // set out of bounds
    printf("---- Out of bounds set ----\n");
    cBitset_setbit(&bitset, 10);
    print_bitset(&bitset);
    printf("\n");

    // set all
    printf("---- Set all ----\n");
    cBitset_set_all(&bitset);
    print_bitset(&bitset);
    printf("\n");

    // clear all
    printf("---- Clear all ----\n");
    cBitset_clear_all(&bitset);
    print_bitset(&bitset);
    printf("\n");

    return 0;
}
