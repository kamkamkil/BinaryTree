cmake_minimum_required(VERSION 3.0.0)
project(DataStructures VERSION 1.0.0)

add_library(BinaryTree INTERFACE)
target_include_directories(BinaryTree INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/BinaryTree>
)

add_library(treeSet INTERFACE)
target_include_directories(BinaryTree INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/treeSet>
)

add_executable(main main.cpp)
target_link_libraries(main BinaryTree)

add_executable(testBST test/testBST.cpp )
target_link_libraries(testBST BinaryTree)

add_executable(testSet test/testSet_.cpp src/treeSet.hpp)


