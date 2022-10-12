cmake_minimum_required(VERSION 3.22)


if (${CMAKE_VERSION} VERSION_LESS 3.24)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.24)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# The languages are C, CXX, Fortran, ASM, CUDA, CSharp, SWIFT
project(LiquidGrowth VERSION 1.0
                     DESCRIPTION "Here is a description"
                     LANGUAGES CXX)  

# this adds other subdirectory by searching for the CMakeLists. 
# add_subdirectory(lib_src)
# add_subdirectory(lib_includes)
# add_subdirectory(lib_tests)







add_library(lib_liquid_growth
src/shiny.cc
src/vase.cc
src/collection.cc
)
target_include_directories(lib_liquid_growth PUBLIC includes)


add_library(test_liquid_growth
tests/catch.cc
tests/tests.cc
)

# target_include_directories(lib_liquid_growth PRIVATE ${src})

target_include_directories(test_liquid_growth PUBLIC tests includes)






add_executable(liquid_growth src/main.cc) # only the main.cc

target_link_libraries(liquid_growth lib_liquid_growth test_liquid_growth)

# install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
# install(FILES "src/main.cc" DESTINATION src) 