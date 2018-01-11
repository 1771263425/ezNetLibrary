cmake_minimum_required (VERSION 2.8)
project(test2)
#add_compile_options(-std=c++11)
include_directories(
    .
)
SET(CXX_SRCS 
${CMAKE_SOURCE_DIR}/main.cpp 
${CMAKE_SOURCE_DIR}/Socket.cpp 
${CMAKE_SOURCE_DIR}/UdpClient.cpp
${CMAKE_SOURCE_DIR}/TcpClient.cpp
)
message(${CXX_SRCS})
add_executable(test2 ${CXX_SRCS})

if (CMAKE_SYSTEM_NAME MATCHES "Linux")  
target_link_libraries ("${PROJECT_NAME}" "pthread" "speex" "portaudio" "rt" "m" "asound")
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")  
target_link_libraries ("${PROJECT_NAME}"  "ws2_32.lib" )   
else ()  
  MESSAGE(STATUS "unknown platform: ${CMAKE_SYSTEM_NAME}")  
endif (CMAKE_SYSTEM_NAME MATCHES "Linux")  