cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(my_malloc C)

set(CMAKE_C_STANDARD 11)

# Include directory
include_directories(include)

# Source files
set(SOURCES
    src/allocator.c
    src/block.c
    src/heap.c
)

# Executable (test)
add_executable(test_malloc
    tests/test_heap.c
    ${SOURCES}
)

# Warnings (jak -Wall -Wextra)
target_compile_options(test_malloc PRIVATE
    -Wall
    -Wextra
    -g
)

# Address sanitizer (opcjonalnie mega polecane)
# odkomentuj jak chcesz debugować pamięć
#target_compile_options(test_malloc PRIVATE -fsanitize=address)
#target_link_options(test_malloc PRIVATE -fsanitize=address)