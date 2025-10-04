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

#ifndef CSTL_ARRAY_H
#define CSTL_ARRAY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Generate the cArray for type T and its associated functions
 * @param T type of the array
 * @param CPY of signature void T_cpy(T* dest, const T* src)
 * @param CMP of signature int T_cmp(const T* a, const T* b)
 *
 * @note CMP should return an integer such that:
 * @note CMP(&a, &b) = 0 => a == b
 * @note CMP(&a, &b) < 0 => a < b
 * @note CMP(&a, &b) > 0 => a > b
 */
#define CARRAY_GENERATE(T, CPY, CMP)                                                               \
    typedef struct                                                                                 \
    {                                                                                              \
        T* array;                                                                                  \
        int size;                                                                                  \
        int capacity;                                                                              \
        int head;                                                                                  \
    } cArray_##T;                                                                                  \
                                                                                                   \
    /* Initialize a cArray with the buffer and its max capacity */                                 \
    static inline void cArray_##T##_init_from_buffer(                                              \
        cArray_##T* vector, T* array, const int capacity)                                          \
    {                                                                                              \
        vector->array = array;                                                                     \
        vector->capacity = capacity;                                                               \
        vector->size = 0;                                                                          \
        vector->head = 0;                                                                          \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_push(cArray_##T* vector, const T* element)                     \
    {                                                                                              \
        if (vector->size >= vector->capacity)                                                      \
            return false;                                                                          \
        CPY(&vector->array[vector->size], element);                                                \
        vector->size++;                                                                            \
        return true;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_pop(cArray_##T* vector, T* out)                                \
    {                                                                                              \
        if (vector->size <= 0)                                                                     \
            return false;                                                                          \
        vector->size--;                                                                            \
        if (out)                                                                                   \
            CPY(out, &vector->array[vector->size]);                                                \
        return true;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_insert(cArray_##T* vector, const T* element, const int index)  \
    {                                                                                              \
        if ((vector->size >= vector->capacity) || (index > vector->size) || (index < 0))           \
            return false;                                                                          \
        for (int i = (vector->size - 1); i >= index; i--)                                          \
        {                                                                                          \
            CPY(&vector->array[i + 1], &vector->array[i]);                                         \
        }                                                                                          \
        CPY(&vector->array[index], element);                                                       \
        vector->size++;                                                                            \
        return true;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_delete(cArray_##T* vector, const int index)                    \
    {                                                                                              \
        if ((vector->size <= 0) || (index >= vector->size) || (index < 0))                         \
            return false;                                                                          \
        for (int i = index; i < (vector->size - 1); i++)                                           \
        {                                                                                          \
            CPY(&vector->array[i], &vector->array[i + 1]);                                         \
        }                                                                                          \
        vector->size--;                                                                            \
        return true;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline int cArray_##T##_find(cArray_##T* vector, const T* element)                      \
    {                                                                                              \
        for (int i = 0; i < vector->size; i++)                                                     \
        {                                                                                          \
            if (CMP(element, &vector->array[i]) == 0)                                              \
                return i;                                                                          \
        }                                                                                          \
        return -1;                                                                                 \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_push_unique(cArray_##T* vector, const T* element)              \
    {                                                                                              \
        if (cArray_##T##_find(vector, element) >= 0)                                               \
            return false;                                                                          \
        return cArray_##T##_push(vector, element);                                                 \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_insert_unique(                                                 \
        cArray_##T* vector, const T* element, const int index)                                     \
    {                                                                                              \
        if (cArray_##T##_find(vector, element) >= 0)                                               \
            return false;                                                                          \
        return cArray_##T##_insert(vector, element, index);                                        \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_binsert(cArray_##T* vector, const T* element)                  \
    {                                                                                              \
        if (vector->size >= vector->capacity)                                                      \
            return false;                                                                          \
        int head = 0, tail = vector->size - 1;                                                     \
        int index = vector->size;                                                                  \
        while (head <= tail)                                                                       \
        {                                                                                          \
            int mid = head + (tail - head) / 2;                                                    \
            if (CMP(element, &vector->array[mid]) > 0)                                             \
            {                                                                                      \
                head = mid + 1;                                                                    \
            }                                                                                      \
            else                                                                                   \
            {                                                                                      \
                index = mid;                                                                       \
                tail = mid - 1;                                                                    \
            }                                                                                      \
        }                                                                                          \
        return cArray_##T##_insert(vector, element, index);                                        \
    }                                                                                              \
                                                                                                   \
    static inline int cArray_##T##_bsearch(cArray_##T* vector, const T* element)                   \
    {                                                                                              \
        if (vector->size <= 0)                                                                     \
            return -1;                                                                             \
        if ((CMP(element, &vector->array[vector->size - 1]) > 0) ||                                \
            (CMP(element, &vector->array[0]) < 0))                                                 \
            return -1;                                                                             \
                                                                                                   \
        int head = 0, tail = vector->size - 1;                                                     \
        while (head <= tail)                                                                       \
        {                                                                                          \
            int index = head + (tail - head) / 2;                                                  \
            if (CMP(element, &vector->array[index]) == 0)                                          \
            {                                                                                      \
                return index;                                                                      \
            }                                                                                      \
            else if (CMP(element, &vector->array[index]) > 0)                                      \
            {                                                                                      \
                head = index + 1;                                                                  \
            }                                                                                      \
            else                                                                                   \
            {                                                                                      \
                tail = index - 1;                                                                  \
            }                                                                                      \
        }                                                                                          \
        return -1;                                                                                 \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_sort(cArray_##T* vector)                                       \
    {                                                                                              \
        if (vector->size <= 1)                                                                     \
            return;                                                                                \
                                                                                                   \
        for (int i = 0; i < vector->size - 1; i++)                                                 \
        {                                                                                          \
            for (int j = 0; j < vector->size - i - 1; j++)                                         \
            {                                                                                      \
                if (CMP(&vector->array[j + 1], &vector->array[j]) < 0)                             \
                {                                                                                  \
                    T tmp;                                                                         \
                    CPY(&tmp, &vector->array[j]);                                                  \
                    CPY(&vector->array[j], &vector->array[j + 1]);                                 \
                    CPY(&vector->array[j + 1], &tmp);                                              \
                }                                                                                  \
            }                                                                                      \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_enqueue(cArray_##T* vector, const T* element)                  \
    {                                                                                              \
        if (vector->size >= vector->capacity)                                                      \
            return false;                                                                          \
        CPY(&vector->array[(vector->head + vector->size) % vector->capacity], element);            \
        vector->size++;                                                                            \
        return true;                                                                               \
    }                                                                                              \
                                                                                                   \
    static inline bool cArray_##T##_dequeue(cArray_##T* vector, T* out)                            \
    {                                                                                              \
        if (vector->size <= 0)                                                                     \
            return false;                                                                          \
        if (out)                                                                                   \
            CPY(out, &vector->array[vector->head]);                                                \
        vector->head = (vector->head + 1) % vector->capacity;                                      \
        vector->size--;                                                                            \
        return true;                                                                               \
    }

#define CARRAY_PRIMITIVE_CPY(T)                                                                    \
    static inline void T##_cpy(T* a, const T* b)                                                   \
    {                                                                                              \
        *a = *b;                                                                                   \
    }

#define CARRAY_PRIMITIVE_CMP(T)                                                                    \
    static inline int T##_cmp(const T* a, const T* b)                                              \
    {                                                                                              \
        return ((*a > *b) - (*a < *b));                                                            \
    }

#define CARRAY_GENERATE_PRIMITIVE(T)                                                               \
    CARRAY_PRIMITIVE_CPY(T)                                                                        \
    CARRAY_PRIMITIVE_CMP(T)                                                                        \
    CARRAY_GENERATE(T, T##_cpy, T##_cmp)

/* Create a cArray of type T and T buffer[capacity] statically, the user must CARRAY_GENERATE(T,
 * CPY, CMP) before creating the cArray */
#define CARRAY_CREATE(name, T, capacity)                                                           \
    T name##_buf[capacity];                                                                        \
    cArray_##T name;                                                                               \
    cArray_##T##_init_from_buffer(&name, name##_buf, capacity);

#ifdef __cplusplus
}
#endif

#endif // CSTL_ARRAY_H