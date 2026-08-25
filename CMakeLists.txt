cmake_minimum_required(VERSION 3.16)
project(SkyMapReduce C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(sky_map_reduce STATIC src/map_reduce.c)
target_include_directories(sky_map_reduce PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(sky_map_reduce PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(sky_map_reduce_cli src/main.c)
target_link_libraries(sky_map_reduce_cli PRIVATE sky_map_reduce)
target_compile_options(sky_map_reduce_cli PRIVATE -Wall -Wextra -Wpedantic -Werror)

add_executable(test_map_reduce tests/test_main.c)
target_link_libraries(test_map_reduce PRIVATE sky_map_reduce)
target_compile_options(test_map_reduce PRIVATE -Wall -Wextra -Wpedantic -Werror)

enable_testing()
add_test(NAME map_reduce_tests COMMAND test_map_reduce)
