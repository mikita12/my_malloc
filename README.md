# Custom Memory Allocator (C)

Implementacja własnego malloc/free w C (implicit free list).

## Features

- malloc / free
- coalescing (łączenie bloków)
- first-fit
- alignment (16 bytes)

## Build

```bash
mkdir build
cd build
cmake ..
make
./test_malloc
