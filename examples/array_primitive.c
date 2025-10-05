#include "cArray.h"
#include <stdbool.h>
#include <stdio.h>

CARRAY_GENERATE_PRIMITIVE(int)

static void cArray_int_print(const cArray_int* arr)
{
    if (arr->size == 0)
    {
        printf("[]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < arr->size - 1; i++)
    {
        printf("%d, ", arr->array[i]);
    }
    printf("%d]\n", arr->array[arr->size - 1]);
}

int main(void)
{
    // Create a cArray of ints
    CARRAY_CREATE(arr, int, 10)

    int x;

    // Push elements
    printf("---- Push elements ----\n");
    for (x = 1; x <= 5; x++)
    {
        cArray_int_push(&arr, &x);
    }
    cArray_int_print(&arr);

    // Pop element
    printf("---- Pop element ----\n");
    cArray_int_pop(&arr, NULL);
    cArray_int_print(&arr);

    // Insert element at index 1
    printf("---- Insert element at index 1 ----\n");
    x = 42;
    cArray_int_insert(&arr, &x, 1);
    cArray_int_print(&arr);

    // Delete element at index 2
    printf("---- Delete element at index 2 ----\n");
    cArray_int_delete(&arr, 2);
    cArray_int_print(&arr);

    // Push unique elements
    printf("---- Push unique elements ----\n");
    x = 3;
    bool pushed = cArray_int_push_unique(&arr, &x); // already exists
    printf("Push 3 success? %s\n", pushed ? "true" : "false");
    x = 99;
    pushed = cArray_int_push_unique(&arr, &x); // new
    printf("Push 99 success? %s\n", pushed ? "true" : "false");
    cArray_int_print(&arr);

    // Insert unique
    printf("---- Insert unique element at index 0 ----\n");
    x = 1;
    pushed = cArray_int_insert_unique(&arr, &x, 0); // already exists
    printf("Insert 1 success? %s\n", pushed ? "true" : "false");
    x = 55;
    pushed = cArray_int_insert_unique(&arr, &x, 0); // new
    printf("Insert 55 success? %s\n", pushed ? "true" : "false");
    cArray_int_print(&arr);

    // Sort array using insertion sort
    printf("---- Sort array - Insertion Sort ----\n");
    cArray_int_insertion_sort(&arr, 0, arr.size - 1);
    cArray_int_print(&arr);

    // Left rotate array and quick sort
    printf("---- Left rotate array and quick sort ----\n");
    cArray_int_rotate_left(&arr, 2);
    cArray_int_print(&arr);
    cArray_int_quick_sort(&arr, 0, arr.size - 1);
    cArray_int_print(&arr);

    // Right rotate array and merge sort
    printf("---- Right rotate array and merge sort ----\n");
    cArray_int_rotate_right(&arr, 2);
    cArray_int_print(&arr);
    cArray_int_merge_sort(&arr, 0, arr.size - 1);
    cArray_int_print(&arr);

    // Binary insert
    printf("---- Binary insert ----\n");
    x = 10;
    cArray_int_binsert(&arr, &x);
    cArray_int_print(&arr);

    // Binary search
    printf("---- Binary search ----\n");
    int index = cArray_int_bsearch(&arr, &x);
    printf("Index of 10: %d\n", index);
    int missing = 999;
    index = cArray_int_bsearch(&arr, &missing);
    printf("Index of 999: %d\n", index);

    return 0;
}
