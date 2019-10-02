include_directories(../include/)

set(SIMEEROS_SRCS SimDevice.cpp DigIn.cpp DigOut.cpp AnalogIn.cpp AnalogOut.cpp)

add_library(simeeros SHARED ${SIMEEROS_SRCS})
add_library(simeeros_static ${SIMEEROS_SRCS})


target_link_libraries(simeeros eeros)
set_target_properties(simeeros PROPERTIES VERSION ${LIBRARY_VERSION})

target_link_libraries(simeeros_static eeros)

INSTALL(TARGETS simeeros simeeros_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

