cmake_minimum_required(VERSION 3.16)
project(machine_learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(MACHINE_LEARNING
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
  )

set(GATES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/gates.c
  )

set(XOR
  ${CMAKE_CURRENT_SOURCE_DIR}/src/xor.c
  )

set(XOR_WITH_MATRICES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/xor_with_matrices.c
  )

set(NN_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/nn.c
  )

add_executable(machine_learning)
target_sources(machine_learning
 PRIVATE
  ${MACHINE_LEARNING}
  )

add_executable(gates)
target_sources(gates
 PRIVATE
  ${GATES}
  )

add_executable(xor)
target_sources(xor
 PRIVATE
  ${XOR}
  )

add_executable(nn_src)
target_sources(nn_src
 PRIVATE
  ${NN_SRC}
  )

add_executable(xor_with_matrices)
target_sources(xor_with_matrices
 PRIVATE
  ${XOR_WITH_MATRICES}
  )

add_library(nn SHARED)
target_sources(nn
 PRIVATE
  ${NN_SRC}
  )

target_link_libraries(gates m)
target_link_libraries(xor m)
target_link_libraries(xor_with_matrices m)
target_link_libraries(nn_src m)
