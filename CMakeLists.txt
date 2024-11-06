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

target_link_libraries(gates m)

target_link_libraries(xor m)
