# cArray — Continuous Memory Array for C

`cArray` is a **generic, statically-backed array container** for C, providing dynamic-like operations (push, insert, delete, sort, search) while using statically allocated or user-provided memory (**no malloc**). It supports both **primitive types** and **custom structs** through user-defined copy and comparison functions.

All **type correctness is enforced at compile time**, while bounds and full/empty checks happen at runtime to ensure code safety.

## How it works
The library uses **MACROS** to generate a cArray and associated functions for each type. For example:
```C
typedef struct {
    char name[64];
    int id;
} MyStruct;

static inline void MyStruct_cpy(MyStruct* dest, const MyStruct* src) { *dest = *src; }
static inline int MyStruct_cmp(const MyStruct* a, const MyStruct* b) { strcmp(a->name, b->name); }

CARRAY_GENERATE(MyStruct, MyStruct_cpy, MyStruct_cmp)
```
generates:
```C
typedef struct {
    MyStruct* array;
    int size;
    int capacity;
} cArray_MyStruct;
```
and associated functions / API for that type (T = MyStruct in this case)

| Function                                          | Description                                                         |
| ------------------------------------------------- | ------------------------------------------------------------------- |
| `cArray_<T>_push(&arr, &element)`                 | Append element at the end. Returns `true` if successful.            |
| `cArray_<T>_pop(&arr)`                            | Remove the last element. Returns `false` if empty.                  |
| `cArray_<T>_insert(&arr, &element, index)`        | Insert element at index. Returns `false` if full or index invalid.  |
| `cArray_<T>_delete(&arr, index)`                  | Delete element at index. Returns `false` if empty or index invalid. |
| `cArray_<T>_find(&arr, &element)`                 | Returns the index of element using `CMP`, or `-1` if not found.     |
| `cArray_<T>_push_unique(&arr, &element)`          | Push only if element not present.                                   |
| `cArray_<T>_insert_unique(&arr, &element, index)` | Insert only if element not present.                                 |
| `cArray_<T>_binsert(&arr, &element)`              | Insert element in sorted order using binary search.                 |
| `cArray_<T>_bsearch(&arr, &element)`              | Binary search for element. Returns index or `-1`.                   |
| `cArray_<T>_sort(&arr)`                           | Sort array using bubble sort.                                       |


Since the struct and functions are defined, users can now do -
```C
MyStruct arr_buf[10];
cArray_MyStruct arr;
cArray_MyStruct_init_from_buffer(&arr, arr_buf, 10);
// or just cArray_MyStruct arr = {.array = arr_buf, .capacity = 10};

MyStruct x = {.name = "test", .id = 1};
cArray_MyStruct_push(&arr, &x);
cArray_MyStruct_pop(&arr);
cArray_MyStruct_insert(&arr, &x, 0);
...
```

## Helper Macros

For primitive types like `int`, `double`, `char`, `bool`, etc the copy and compare functions are just regular assignments are also primitive, so the library also provides primitive generation macros.  
**Note**: all cArray types must be generated using `CARRAY_GENERATE` **before** instances are created using `CARRAY_CREATE`
```C
CARRAY_PRIMITIVE_CPY(int)
// generates
static inline void int_cpy(int* dest, const int* src) { *dest = *src; }

CARRAY_PRIMITIVE_CMP(int)
// generates
static inline int int_cmp(const int* a, const int* b) { return (*a > *b) - (*a < *b); }

CARRAY_GENERATE_PRIMITIVE(int)
// generates the cArray_int struct and API using primitive cpy and cmp
```
Additionally, to eliminate the 3 step initialization of a cArray, another macro is provided -
```C
CARRAY_CREATE(arr, MyStruct, 10)
// generates - MyStruct arr_buf[10]; cArray_MyStruct arr = {.array = arr_buf, .capacity = 10};
```
For more examples, check out the `examples/` folder
