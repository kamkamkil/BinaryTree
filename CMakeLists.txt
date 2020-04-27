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

add_library(map INTERFACE)
target_include_directories(BinaryTree INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/map>
)

add_library(graph INTERFACE)
target_include_directories(graph INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/graph>
)
target_compile_features (graph
  INTERFACE
    cxx_std_17
)
add_executable(main main.cpp)
target_link_libraries(main BinaryTree)

add_executable(testBST test/testBST.cpp )
target_link_libraries(testBST BinaryTree)

add_executable(testSet test/testSet.cpp )
target_link_libraries(testBST treeSet)

add_executable(testSetZajecia1 test/testSetZajecia1.cpp )
target_link_libraries(testSetZajecia1  treeSet)

add_executable(testSetZajecia2 test/testSetZajecia2.cpp )
target_link_libraries(testSetZajecia2  treeSet)

add_executable(testMap test/testMap.cpp)
target_link_libraries(testMap map)

add_executable(testMapZajecia test/testMapZajecia.cpp)
target_link_libraries(testMapZajecia map)

add_executable(testGraph test/testGraph.cpp)
target_link_libraries(testGraph graph)