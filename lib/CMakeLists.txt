include_directories(../include/)

set(SIMEEROS_SRCS SimDevice.cpp DigIn.cpp DigOut.cpp)

add_library(simeeros SHARED ${SIMEEROS_SRCS})
add_library(simeeros_static ${SIMEEROS_SRCS})

target_link_libraries(simeeros eeros)
target_link_libraries(simeeros_static eeros)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/libsimeeros.so ${CMAKE_CURRENT_BINARY_DIR}/libsimeeros_static.a DESTINATION lib)
