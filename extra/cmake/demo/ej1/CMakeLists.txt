# Raiz del proyecto
cmake_minimum_required(VERSION 2.4)
project(cmake-demo)

# Incluyo un cmake que define una biblioteca
add_subdirectory(lib)
# Incluyo la carpeta lib como include directory
include_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(ej1 main.cpp)

# Linkeo la biblioteca con nuestro programa
target_link_libraries(ej1 mylib)