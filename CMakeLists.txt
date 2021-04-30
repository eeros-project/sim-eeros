cmake_minimum_required(VERSION 3.5.1)

project(sim-eeros)

set(CMAKE_CXX_STANDARD 14)


set(RECOMMENDED_EEROS_VERSION 1.1.0.0)


## Load CMake modules library at specified version
set(LOAD_CMAKE_MODULES_LIB TRUE CACHE BOOL "TRUE if the cmake-modules library should be loaded.")

if(LOAD_CMAKE_MODULES_LIB)
  include(cmake/CMakeModulesLibLoader.cmake)
  load_cmake_modules_lib(https://github.com/andreaskunz/cmake-modules.git)
endif()

include(CMakeModulesLib)

if(CMAKE_BUILD_TYPE MATCHES "Debug|DEBUG")
  logger_on()
endif()

if(LOAD_CMAKE_MODULES_LIB)
  checkout_cmake_modules_lib_version(a50add2)
endif()


## Fetch the version information from git tag
include(VersioningHelpers)
setLibraryVersion()


# Find EEROS
setVersionToFind("EEROS" "REQUIRED_EEROS_VERSION" ${RECOMMENDED_EEROS_VERSION} ${REQUIRED_EEROS_VERSION})
find_package(EEROS ${VERSION_TO_FIND} EXACT)
checkIfModuleFound("EEROS" "REQUIRED_EEROS_VERSION")


include_directories(${ADDITIONAL_INCLUDE_DIRS})
link_directories(${ADDITIONAL_LINK_DIRS})

include_directories(${EEROS_INCLUDE_DIR})
link_directories(${EEROS_LIB_DIR})


add_subdirectory(lib)


createPackageFiles(sim-eerosConfig.cmake.in include/ lib/)


INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/SimDevice.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/SimBehaviour.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/SimChannel.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/DigIn.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/include/DigOut.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/AnalogIn.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/AnalogOut.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Reflect.hpp
DESTINATION include/sim-eeros)

