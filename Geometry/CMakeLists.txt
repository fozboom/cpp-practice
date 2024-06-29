cmake_minimum_required(VERSION 3.18)

project(Geometry)

set(TEST_NAME geometry-tests)
set(RUN_NAME geometry-run)
set(CMAKE_CXX_STANDARD 20)

add_executable(${RUN_NAME}
        main.cpp
        src/Vector.cpp
        include/Vector/Vector.hpp
        include/IShape/IShape.hpp
        include/Point/Point.hpp
        src/Point.cpp
        include/Segment/Segment.hpp
        src/Segment.cpp)
add_executable(${TEST_NAME}
        tests/tests.cpp
        src/Vector.cpp
        include/Vector/Vector.hpp
        include/IShape/IShape.hpp
        include/Point/Point.hpp
        include/Segment/Segment.hpp
)



string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
if (build_type STREQUAL san)
    add_compile_options(-fsanitize=address -fsanitize=undefined)
    add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

add_compile_options(-pedantic -Werror -Wextra -std=c++20)
add_link_options(-pedantic -Werror -Wextra -std=c++20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include/Vector)
include_directories(${PROJECT_SOURCE_DIR}/include/IShape)
include_directories(${PROJECT_SOURCE_DIR}/include/Point)
include_directories(${PROJECT_SOURCE_DIR}/include/Segment)
enable_testing()

add_test(${TEST_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME})

target_link_libraries(${TEST_NAME} Threads::Threads ${GTEST_LIBRARIES} ${GMOCK_BOTH_LIBRARIES})


