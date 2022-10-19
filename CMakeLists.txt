cmake_minimum_required(VERSION 3.24)


if (${CMAKE_VERSION} VERSION_LESS 3.24)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.24)
endif()



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_MODULE_PATH cmake)


# The languages are C, CXX, Fortran, ASM, CUDA, CSharp, SWIFT
project(LiquidGrowth VERSION 1.0
                     DESCRIPTION "Here is a description"
                     LANGUAGES CXX)  


FIND_PACKAGE(Boost)   # if boost not found, maybe "brew install Boost"
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

# FIND_PACKAGE(FileSystemConfig.cmake)


# this adds other subdirectory by searching for the CMakeLists. 
# add_subdirectory(lib_src)
# add_subdirectory(lib_includes)
# add_subdirectory(lib_tests)



add_library(lib_liquid_growth
src/shiny.cc
src/vase.cc
src/collection.cc
)
target_include_directories(lib_liquid_growth PUBLIC includes storage)



# find_package(Filesystem REQUIRED)
# target_link_libraries(lib_liquid_growth PRIVATE Filesystem::Filesystem)



add_library(test_liquid_growth
tests/catch.cc
tests/tests.cc
)
target_include_directories(test_liquid_growth PUBLIC tests includes storage)

# target_link_libraries(test_liquid_growth PUBLIC)

# set(CMAKE_CXX_FLAGS "-std=c++14 -lstdc++fs" )
add_executable(liquid_growth src/main.cc)
# find_library(FOO_LIB stdc++fs)

target_link_libraries(liquid_growth PUBLIC lib_liquid_growth test_liquid_growth stdc++fs)
# target_link_libraries(liquid_growth PUBLIC "${FOO_LIB}")
# target_include_directories(liquid_growth PUBLIC storage)
# target_link_libraries(${ } stdc++fs)

