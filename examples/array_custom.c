#include "cArray.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Custom struct */
typedef struct
{
    char name[64];
    int id;
} MyStruct;

// primitive *dest = *src works here
CARRAY_PRIMITIVE_CPY(MyStruct)

static inline int MyStruct_cmp(const MyStruct* a, const MyStruct* b)
{
    // Uncomment based on whether to sort by name/id
    return strcmp(a->name, b->name);
    // return ((a->id > b->id) - (a->id < b->id));
}

CARRAY_GENERATE(MyStruct, MyStruct_cpy, MyStruct_cmp)

static void cArray_MyStruct_print(const cArray_MyStruct* arr)
{
    printf("[\n");
    for (int i = 0; i < arr->size; i++)
    {
        printf("  {name: %s, id: %d}\n", arr->array[i].name, arr->array[i].id);
    }
    printf("]\n");
}

int main(void)
{
    /* Create a cArray for 5 elements */
    MyStruct arr_buf[5];
    cArray_MyStruct arr;
    cArray_MyStruct_init_from_buffer(&arr, arr_buf, 5);

    /* Push elements */
    MyStruct a = {.name = "Alice", .id = 3};
    MyStruct b = {.name = "Bob", .id = 1};
    MyStruct c = {.name = "Charlie", .id = 2};

    cArray_MyStruct_push(&arr, &a);
    cArray_MyStruct_push(&arr, &b);
    cArray_MyStruct_push(&arr, &c);

    printf("---- After push ----\n");
    cArray_MyStruct_print(&arr);

    /* Insert element at index 1 */
    MyStruct d = {.name = "Dave", .id = 4};
    cArray_MyStruct_insert(&arr, &d, 1);
    printf("---- After insert at index 1 ----\n");
    cArray_MyStruct_print(&arr);

    /* Delete element at index 2 */
    cArray_MyStruct_delete(&arr, 2);
    printf("---- After delete at index 2 ----\n");
    cArray_MyStruct_print(&arr);

    /* Sort array (bubble sort) */
    cArray_MyStruct_sort(&arr);
    printf("---- After sort (by id) ----\n");
    cArray_MyStruct_print(&arr);

    /* Binary insert (maintains sorted order) */
    MyStruct e = {.name = "Eve", .id = 5};
    cArray_MyStruct_binsert(&arr, &e);
    printf("---- After binary insert id=0 ----\n");
    cArray_MyStruct_print(&arr);

    /* Binary search */
    int idx = cArray_MyStruct_bsearch(&arr, &e);
    printf("Index of Eve (id=5): %d\n", idx);
    idx = cArray_MyStruct_bsearch(&arr, &b);
    printf("Index of Bob (removed): %d\n", idx);

    return 0;
}
