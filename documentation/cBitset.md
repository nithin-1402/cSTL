# cBitset — Continuous Memory Bitset for C

`cBitset` is a **header-only, statically-backed bitset container** for C. It allows you to efficiently manipulate individual bits in a user-provided memory buffer (**no malloc required**).

It is suitable for **flags, bitfields, masks, and other space-efficient boolean arrays**, while providing safe access with runtime bounds checks.

## How it works

A `cBitset` stores bits in a **contiguous memory buffer of bytes**. The user provides the buffer, and the library manages the mapping of bit indices to provide a higher-level bitset API.
**Note**: The user must ensure that the buffer contains the minimum size to store the number of bits needed.

```c
cBitset bits;
uint8_t buffer[2];  // 16 bits → 2 bytes
cBitset_init_from_buffer(&bits, buffer, 16);
```

## Helper Macros

The minimum number of bytes (size of a `uint8_t` array) required to store `N` bits is given my the macro `CBITSET_SIZE(N)`  
So you can then write this without worrying about the size -
```c
cBitset bits;
uint8_t buffer[CBITSET_SIZE(10)];
cBitset_init_from_buffer(&bits, buffer, 10);
```
Alternatively, you can use `CBITSET_CREATE` to declare a bitset and its buffer a single line:
```c
CBITSET_CREATE(my_bits, 32)  // creates 32-bit bitset
```

This expands to:

```c
uint8_t my_bits_buf[CBITSET_SIZE(32)];
cBitset my_bits;
cBitset_init_from_buffer(&my_bits, my_bits_buf, 32);
```

---

## API Reference

| Function / Macro                                   | Return Type | Description                                              |
| -------------------------------------------------- | ----------- | -------------------------------------------------------- |
| `cBitset_init_from_buffer(bits, buffer, num_bits)` | `void`      | Initialize bitset from user-provided buffer and zero it. |
| `CBITSET_SIZE(num_bits)`                           | `size_t`    | Returns minimum number of bytes needed for `num_bits`.   |
| `cBitset_clear_all(bits)`                          | `void`      | Set all bits to `0`.                                     |
| `cBitset_set_all(bits)`                            | `void`      | Set all bits to `1`.                                     |
| `cBitset_readbit(bits, n)`                         | `bool`      | Read bit at index `n`. Returns `false` if out of bounds. |
| `cBitset_setbit(bits, n)`                          | `void`      | Set bit at index `n` to `1`. No-op if out of bounds.     |
| `cBitset_clearbit(bits, n)`                        | `void`      | Clear bit at index `n` to `0`. No-op if out of bounds.   |
| `cBitset_togglebit(bits, n)`                       | `void`      | Flip bit at index `n`. No-op if out of bounds.           |

For examples, check out the `examples/` folder
