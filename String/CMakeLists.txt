cmake_minimum_required(VERSION 3.16)

set(TEST_NAME string-tests)
set(RUN_NAME string-run)

project(String)

add_executable(${TEST_NAME} src/String.cpp ./tests/tests.cpp)
add_executable(${RUN_NAME} src/String.cpp main.cpp)

set_target_properties(${TEST_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

add_compile_options(-pedantic -Werror -Wextra -std=c++20)
add_link_options(-pedantic -Werror -Wextra -std=c++20)


string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
if (build_type STREQUAL san)
    add_compile_options(-fsanitize=address -fsanitize=undefined)
    add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()


target_link_libraries(${TEST_NAME} Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
include_directories(${PROJECT_SOURCE_DIR}/include/string)

add_test(${TEST_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME})

