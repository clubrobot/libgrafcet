cmake_minimum_required(VERSION 4.2)
project(grafcet)

set(GRAFCET_MAX_NODE_PARENTS 10 CACHE STRING "Max parents per node")
set(GRAFCET_MAX_NODE_CHILDREN 10 CACHE STRING "Max children per node")
set(GRAFCET_MAX_QUEUE_SIZE 10 CACHE STRING "Max queue size")
add_library(grafcet STATIC src/StateMachine.cpp src/Static.cpp)
target_include_directories(grafcet PUBLIC include)
target_compile_features(grafcet PUBLIC cxx_std_23)

if(GRAFCET_TEST)
    add_executable(grafcet_test test/test.cpp
        src/StateMachine.cpp
        src/Static.cpp
    )
    target_include_directories(grafcet_test PUBLIC include)
    target_compile_features(grafcet_test PUBLIC cxx_std_23)
endif()

target_include_directories(grafcet PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)
