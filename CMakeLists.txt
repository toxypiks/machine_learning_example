cmake_minimum_required(VERSION 3.16)
project(machine_learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(raylib)

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

set(ADDER
  ${CMAKE_CURRENT_SOURCE_DIR}/src/adder.c
  )

set(DUMP_NN_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dump_nn.c
  )

set(OLIVE_C_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/olive.c
  )

set(RAYLIB_NN_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/raylib_nn.c
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

add_executable(adder)
target_sources(adder
 PRIVATE
  ${ADDER}
  )

add_executable(xor_with_matrices)
target_sources(xor_with_matrices
 PRIVATE
  ${XOR_WITH_MATRICES}
  )

add_executable(dump_nn)
target_sources(dump_nn
 PRIVATE
  ${DUMP_NN_SRC}
  )

add_executable(raylib_nn)
target_sources(raylib_nn
 PRIVATE
  ${RAYLIB_NN_SRC}
  )

add_library(olive_c)
target_sources(olive_c
 PRIVATE
  ${OLIVE_C_SRC}
  )

add_library(nn SHARED)
target_sources(nn
 PRIVATE
  ${NN_SRC}
  )

target_include_directories(raylib_nn
 PRIVATE
  ${raylib_INCLUDE_DIRS}
  )

target_link_libraries(raylib_nn
  ${raylib_LIBRARIES}
  )

target_include_directories(adder
 PRIVATE
  ${raylib_INCLUDE_DIRS}
  )

target_link_libraries(adder
  ${raylib_LIBRARIES}
)

target_link_libraries(gates m)
target_link_libraries(xor m)
target_link_libraries(xor_with_matrices m)
target_link_libraries(nn_src m)
target_link_libraries(adder m)
target_link_libraries(dump_nn m)
