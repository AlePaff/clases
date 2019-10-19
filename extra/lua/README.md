# Lua

## Instalación

~~~{.bash}
sudo apt install lua5.3 liblua5.3-dev
~~~

* *lua5.3*: Intérprete de linea de comandos

* *liblua5.3-dev*: Biblioteca para desarrollar en C y C++

## Acerca del lenguaje

Lua es un lenguaje *interpretado*, muy usado en la industria de videojuegos, pero también en otras areas de informática (ver el sitio del lenguaje para más información).

Su principal característica es la simplicidad del lenguaje, que trae aparejado bajo overhead en la ejecución de rutinas y poco espacio extra en el binario que lo interpreta.

## Ejemplos

Los ejemplos están divididos en las siguientes carpetas:

* **00-hello**: Hola mundo en Lua. Compuesto por un programa muy sencillo en C que recibe la ruta a un archivo *.lua* y lo ejecuta. Si no se le pasa ningún archivo, ejecuta un comando de Lua con la función luaL_dostring.

* **01-tables**: Ejemplos varios con tablas. Este ejemplo está pensado para ser ejecutado por el interprete de Lua.

* **02-functions**: Ejemplos de algunas características particulares de las funciones en Lua, como las funciones variádicas y funciones anónimas. Este ejemplo está pensado para ser ejecutado por el interprete de Lua.


