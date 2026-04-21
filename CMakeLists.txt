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

# =========================
# Executable (test)
# =========================
add_executable(test_malloc
    tests/test_heap.c
    ${SOURCES}
)

target_compile_options(test_malloc PRIVATE
    -Wall
    -Wextra
    -g
)

# =========================
# OPTIONAL: Library version
# =========================
# Uncomment if you want to use this as a library
#
# add_library(my_malloc_lib
#     ${SOURCES}
# )
#
# target_include_directories(my_malloc_lib PUBLIC include)
#
# target_compile_options(my_malloc_lib PRIVATE
#     -Wall
#     -Wextra
#     -g
# )

# =========================
# OPTIONAL: Test linked with library
# =========================
# add_executable(test_malloc tests/test_heap.c)
# target_link_libraries(test_malloc my_malloc_lib)

# =========================
# OPTIONAL: AddressSanitizer
# =========================
# target_compile_options(test_malloc PRIVATE -fsanitize=address)
# target_link_options(test_malloc PRIVATE -fsanitize=address)