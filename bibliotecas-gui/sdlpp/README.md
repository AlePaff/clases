# Demo de SDL

Para compilar es necesario instalar `libsdl2-dev` y `libsdl2-image-dev`. Se recomienda el uso de CMake

## Compilar con CMake

Crear una carpeta vacía (ej: build) e invocar a CMake pasando como argumento el directorio donde está CMakeLists.txt

~~~{.bash}
mkdir build
cd build
cmake ..
make
~~~

## Ejecución

### Hello SDL

Carga una imagen y la muestra en pantalla durante 3 segundos

Ejecutar escribiendo `./sdlpp-hello`

### Eventos básicos

Carga una animación y la muestra en pantalla. Desplaza la imagen, animandolá por el canvas al presionar las teclas
direccionales

Ejecutar escribiendo `./sdlpp-events`

