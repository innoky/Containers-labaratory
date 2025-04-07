cmake_minimum_required(VERSION 3.10)
project(Lab2Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(lab2
    src/main.cpp
)

# ======== ТЕСТЫ ДЛЯ MUTABLE ==========
add_executable(tests
    tests/catch_amalgamated.cpp     
    tests/test_array.cpp
    tests/test_list.cpp
)
target_include_directories(tests PRIVATE include tests)

# ======== ТЕСТЫ ДЛЯ IMMUTABLE ==========
add_executable(immutable_tests
    tests/catch_amalgamated.cpp
    tests/test_immutable_array.cpp
    tests/test_immutable_list.cpp
)
target_include_directories(immutable_tests PRIVATE include tests)

# ======== ТЕСТЫ ВСЕГО ==========
add_executable(big_all_tests
    tests/catch_amalgamated.cpp
    tests/test_all.cpp
)

target_include_directories(big_all_tests PRIVATE include tests)

# ========== UI ==========
