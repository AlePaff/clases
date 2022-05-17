project(qt-sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(APPLE)
    message("Estoy en OSX")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2")
endif()

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
add_subdirectory(lib/libSDL2pp)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets)

qt5_wrap_ui(UIS_HEADERS
  ui/mainWindow.ui
)

message("Headers generados: ${UIS_HEADERS}")
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (sdl-standalone
        src/mainSDL.cpp
        src/Animation.cpp
        src/Animation.h
        src/Gameloop.cpp
        src/Player.cpp
        src/Player.h
)

add_executable (qt-standalone
    src/mainQt.cpp
    src/MainWindow.cpp
    ${UIS_HEADERS}
)

add_executable (qt-plus-sdl
    src/mainQtSDL.cpp
    src/MainWindow.cpp
    src/Animation.cpp
    src/Animation.h
    src/Gameloop.cpp
        src/Player.cpp
    src/Player.h
    ${UIS_HEADERS}
)

target_link_libraries(qt-standalone Qt5::Widgets)
target_link_libraries(sdl-standalone ${SDL2PP_LIBRARIES})
target_link_libraries(qt-plus-sdl Qt5::Widgets ${SDL2PP_LIBRARIES})

FILE(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
