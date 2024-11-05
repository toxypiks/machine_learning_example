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

target_link_libraries(gates m)
