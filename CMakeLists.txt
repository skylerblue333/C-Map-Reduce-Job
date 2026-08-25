cmake_minimum_required(VERSION 3.16)
project(sky_word_reducer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(app src/main.c)
add_executable(test_app tests/test_main.c)

target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_options(test_app PRIVATE -Wall -Wextra -Wpedantic -Werror)

enable_testing()
add_test(NAME word_reducer_contract COMMAND test_app)
set_tests_properties(word_reducer_contract PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
