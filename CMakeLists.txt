cmake_minimum_required(VERSION 2.6)
project(sim-eeros)

## Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(EEROS REQUIRED)
include_directories(${EEROS_INCLUDE_DIR})
link_directories(${EEROS_LIB_DIR})

include_directories(${ADDITIONAL_INCLUDE_DIRS})
link_directories(${ADDITIONAL_LINK_DIRS})

add_subdirectory(lib)
add_subdirectory(test)

INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/SimDevice.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/SimDigIn.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/include/SimDigOut.hpp
DESTINATION include)