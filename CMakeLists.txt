cmake_minimum_required(VERSION 3.10)
project(test1)

set(CMAKE_CXX_STANDARD 11)

#add_executable(test1 main.cpp eight.cpp test1.cpp tsp.cpp eight_grid.cpp newcode1.cpp)

#add_executable(test1 newcode1.cpp)


#add_executable(test1 boj/b1001.cpp)

#add_executable(test1 eight_grid.cpp uglynumbers.cpp)
#add_executable(test1 BigInteger.cpp)
add_subdirectory(boj)
add_subdirectory(leetcode)
#add_executable(test1 test_reference.cpp)
#add_executable(test1 uncode.cpp)
add_executable(test1 leetcode/t4.cpp)
target_link_libraries(test1 BigDecimal)
