cmake_minimum_required(VERSION 3.0.0)
project(DataStructures VERSION 1.0.0)

add_library(BinaryTree INTERFACE)
target_include_directories(BinaryTree INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/BinaryTree>
)

add_executable(main main.cpp)
target_link_libraries(main BinaryTree)

add_executable(test test/test.cpp )
target_link_libraries(test BinaryTree)

