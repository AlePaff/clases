# Simple grep

La siguiente aplicación recibe un archivo y una palabra a buscar. Luego lee linea por linea y si la palabra se encuentra dentro de la linea leida, imprime la linea y el número de linea.

## Compilación

Crear una carpeta `build` y ejecutar

~~~{.bash}
cd build
cmake ..
make
make install
~~~

## Ejecución

Para la versión de python ejecutar

~~~{.bash}
python3 ./simple_grep.py <archivo> <expr>
~~~

Para la versión de C

~~~{.bash}
./simple-grep <archivo> <expr>
~~~

Para la versión híbrida

~~~{.bash}
python3 ./simple_grep_opt.py <archivo> <expr>
~~~

### Profile

Para hacer un profile de la versión de python ejecutar

~~~
python3 -m cProfile ./simple_grep.py <archivo> <expr>
~~~

Se recomienda usar archivos de tamaño considerable para subir el tiempo de procesamiento.

