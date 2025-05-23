cmake_minimum_required(VERSION 2.8)

project(sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(APPLE)
  message("Estoy en OSX")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2")
endif()

add_subdirectory(libs)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)

add_executable (sdl-hello
  src/mainSdlHello.cpp  
)

add_executable (sdl-events
  src/mainSdlEvents.cpp
  src/Player.cpp
)

add_executable (sdl-alpha-blending
  src/mainSdlAlphaBlending.cpp
)


target_link_libraries(sdl-hello sdldemo SDL2 SDL2_image)
target_link_libraries(sdl-events sdldemo SDL2 SDL2_image)
target_link_libraries(sdl-alpha-blending sdldemo SDL2 SDL2_image)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
