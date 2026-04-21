# Custom Memory Allocator (C)

Implementation of a custom `malloc`/`free` in C using an implicit free list.

## Features

- malloc / free
- block coalescing
- first-fit allocation strategy
- 16-byte alignment

## Build

```bash
mkdir build
cd build
cmake ..
make
./test_malloc
