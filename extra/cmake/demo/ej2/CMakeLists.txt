# Raiz del proyecto
cmake_minimum_required(VERSION 2.4)
project(cmake-install)

add_executable(ej2 main.cpp)

# Agrego directiva de instalación y le defino el path donde va a vivir el archivo instalado
install(TARGETS ej2 DESTINATION ~/installed/ej2)