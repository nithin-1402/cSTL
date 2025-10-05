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
#include <stdlib.h>

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
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_map(cArray_##T* vector, void (*func)(T*))                      \
    {                                                                                              \
        for (int i = 0; i < vector->size; i++)                                                     \
        {                                                                                          \
            func(&vector->array[i]);                                                               \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_filter(cArray_##T* vector, bool (*predicate)(T*))              \
    {                                                                                              \
        int j = 0;                                                                                 \
        for (int i = 0; i < vector->size; i++)                                                     \
        {                                                                                          \
            if (predicate(&vector->array[i]))                                                      \
            {                                                                                      \
                if (i != j)                                                                        \
                    CPY(&vector->array[j], &vector->array[i]);                                     \
                j++;                                                                               \
            }                                                                                      \
        }                                                                                          \
        vector->size = j;                                                                          \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_swap(T* a, T* b)                                               \
    {                                                                                              \
        T temp;                                                                                    \
        CPY(&temp, b);                                                                             \
        CPY(b, a);                                                                                 \
        CPY(a, &temp);                                                                             \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_reverse(cArray_##T* vector, int start, int end)                \
    {                                                                                              \
        if ((start < 0) || (end >= vector->size) || (start >= end))                                \
            return;                                                                                \
        while (start < end)                                                                        \
        {                                                                                          \
            cArray_##T##_swap(&vector->array[start], &vector->array[end]);                         \
            start++;                                                                               \
            end--;                                                                                 \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_rotate_left(cArray_##T* vector, int n)                         \
    {                                                                                              \
        if ((n < 0) || (vector->size <= 0))                                                        \
            return;                                                                                \
        n %= vector->size;                                                                         \
        if (n == 0)                                                                                \
            return;                                                                                \
        cArray_##T##_reverse(vector, 0, n - 1);                                                    \
        cArray_##T##_reverse(vector, n, vector->size - 1);                                         \
        cArray_##T##_reverse(vector, 0, vector->size - 1);                                         \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_rotate_right(cArray_##T* vector, int n)                        \
    {                                                                                              \
        if ((n < 0) || (vector->size <= 0))                                                        \
            return;                                                                                \
        n %= vector->size;                                                                         \
        if (n == 0)                                                                                \
            return;                                                                                \
        cArray_##T##_reverse(vector, 0, vector->size - n - 1);                                     \
        cArray_##T##_reverse(vector, vector->size - n, vector->size - 1);                          \
        cArray_##T##_reverse(vector, 0, vector->size - 1);                                         \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_merge_sort_recursive(                                          \
        cArray_##T* vector, T* temp, const int left, const int right)                              \
    {                                                                                              \
        /* Base case */                                                                            \
        if (left >= right)                                                                         \
            return;                                                                                \
        /* Recursively split the left and right halves until base case is reached */               \
        int mid = left + ((right - left) / 2);                                                     \
        cArray_##T##_merge_sort_recursive(vector, temp, left, mid);                                \
        cArray_##T##_merge_sort_recursive(vector, temp, mid + 1, right);                           \
                                                                                                   \
        /* We now have sorted left and right half arrays, merge them into a single sorted array */ \
        int i = left, j = mid + 1, k = left;                                                       \
        while ((i <= mid) && (j <= right))                                                         \
        {                                                                                          \
            if (CMP(&vector->array[i], &vector->array[j]) <= 0)                                    \
                CPY(&temp[k++ - left], &vector->array[i++]);                                       \
            else                                                                                   \
                CPY(&temp[k++ - left], &vector->array[j++]);                                       \
        }                                                                                          \
        /* Copy leftovers */                                                                       \
        while (i <= mid)                                                                           \
            CPY(&temp[k++ - left], &vector->array[i++]);                                           \
        while (j <= right)                                                                         \
            CPY(&temp[k++ - left], &vector->array[j++]);                                           \
                                                                                                   \
        /* Copy the merged array to our original array */                                          \
        for (i = left; i <= right; i++)                                                            \
            CPY(&vector->array[i], &temp[i - left]);                                               \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_merge_sort(cArray_##T* vector, const int start, const int end) \
    {                                                                                              \
        if ((start < 0) || (end >= vector->size) || (start >= end))                                \
            return;                                                                                \
        T* temp = (T*) malloc((end - start + 1) * sizeof(T));                                      \
        if (! temp)                                                                                \
            return;                                                                                \
        cArray_##T##_merge_sort_recursive(vector, temp, start, end);                               \
        free(temp);                                                                                \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_insertion_sort(                                                \
        cArray_##T* vector, const int start, const int end)                                        \
    {                                                                                              \
        if ((start < 0) || (end >= vector->size) || (start >= end))                                \
            return;                                                                                \
                                                                                                   \
        for (int i = start + 1; i <= end; i++)                                                     \
        {                                                                                          \
            /* Everything behind key is already sorted */                                          \
            T key;                                                                                 \
            CPY(&key, &vector->array[i]);                                                          \
            /* Push the key back to its correct position (until element > key) */                  \
            int j = i - 1;                                                                         \
            while ((j >= start) && (CMP(&key, &vector->array[j]) < 0))                             \
            {                                                                                      \
                CPY(&vector->array[j + 1], &vector->array[j]);                                     \
                j--;                                                                               \
            }                                                                                      \
            CPY(&vector->array[j + 1], &key);                                                      \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    static inline void cArray_##T##_quick_sort(cArray_##T* vector, int start, int end)             \
    {                                                                                              \
        if ((start < 0) || (end >= vector->size) || (start >= end))                                \
            return;                                                                                \
        /* Tail recursion - iteratively recurse from the smallest to the largest partition */      \
        while (start < end)                                                                        \
        {                                                                                          \
            /* Pick pivot to be the middle element */                                              \
            int mid = start + ((end - start) / 2);                                                 \
                                                                                                   \
            /* Ensure start <= mid <= end */                                                       \
            if (CMP(&vector->array[start], &vector->array[mid]) > 0)                               \
                cArray_##T##_swap(&vector->array[start], &vector->array[mid]);                     \
            if (CMP(&vector->array[start], &vector->array[end]) > 0)                               \
                cArray_##T##_swap(&vector->array[start], &vector->array[end]);                     \
            if (CMP(&vector->array[mid], &vector->array[end]) > 0)                                 \
                cArray_##T##_swap(&vector->array[end], &vector->array[mid]);                       \
                                                                                                   \
            /* Move pivot to the start for Hoare partition */                                      \
            cArray_##T##_swap(&vector->array[start], &vector->array[mid]);                         \
            T pivot;                                                                               \
            CPY(&pivot, &vector->array[start]);                                                    \
                                                                                                   \
            /* Hoare Partition Loop */                                                             \
            int i = start - 1, j = end + 1;                                                        \
            while (true)                                                                           \
            {                                                                                      \
                do                                                                                 \
                {                                                                                  \
                    i++;                                                                           \
                } while (CMP(&vector->array[i], &pivot) < 0);                                      \
                do                                                                                 \
                {                                                                                  \
                    j--;                                                                           \
                } while (CMP(&vector->array[j], &pivot) > 0);                                      \
                if (i >= j)                                                                        \
                    break;                                                                         \
                cArray_##T##_swap(&vector->array[i], &vector->array[j]);                           \
            }                                                                                      \
            /* Find the smallest partition and recurse */                                          \
            if ((j - start) >= (end - j - 1))                                                      \
            {                                                                                      \
                cArray_##T##_quick_sort(vector, start, j);                                         \
                start = j + 1;                                                                     \
            }                                                                                      \
            else                                                                                   \
            {                                                                                      \
                cArray_##T##_quick_sort(vector, j + 1, end);                                       \
                end = j;                                                                           \
            }                                                                                      \
        }                                                                                          \
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
