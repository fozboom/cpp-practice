cmake_minimum_required(VERSION 3.18)

set(TASK_NAME big-integer-tests)
set(RUN_NAME big-integer-run)

project(BigInteger)
add_executable(${TASK_NAME} src/BigInteger.cpp tests/tests.cpp)
add_executable(${RUN_NAME} src/BigInteger.cpp main.cpp)

set_target_properties(${TEST_NAME} PROPERTIES
        CXX_STANDARD 20
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
include_directories(${PROJECT_SOURCE_DIR}/include/BigInteger)
enable_testing()


add_test(${TASK_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${TASK_NAME})
target_link_libraries(${TASK_NAME} Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})
