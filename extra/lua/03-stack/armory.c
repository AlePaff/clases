// Lua está pensado para trabajar con C, por lo cuál
// la biblioteca nos pide que nuestras funciones sean compatibles
// con la C, desactivando el name mangling
#ifdef __cplusplus
  // Este header es básicamente una inclusión de los 3 de abajo
  // pero protegido con extern "C"
  #include "lua.hpp"
#else
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
#endif

/**
 * Esta función leerá la variable "version" almacenada en un script de .lua
 */
int getVersion(lua_State* L);

int main(int argc, char* argv[]) {
  int result;
  if (argc == 2) {
    const char* filename = argv[1]; 
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    int result;
    printf("Ejecutando luaL_dofile\n");
    // Ejecuto el script con la configuración guardada 
    result = luaL_dofile(L, filename);
    if (result == 0) {
      result = getVersion(L);
    }
    lua_close(L);
  } else {
    return 1;
  }
  return result;
}

int getVersion(lua_State* L) {
  // Chequeo el tamaño del stack de variables del motor de lua
  int stackSize = lua_gettop(L);
  printf("Tamaño del stack: %d\n", stackSize);
  printf("Ejecutando getglobal\n");
  // Agrego al stack la variable global "version"
  lua_getglobal(L, "version");
  // Verifico que efectivamente creció el stack
  stackSize = lua_gettop(L);
  printf("Tamaño del stack post getglobal: %d\n", stackSize);
  // 1 es la posición en el stack con la versión que pedí
  // Me fijo si la variable que levanté es numérica
  int isNumber = lua_isnumber(L, 1);
  if (isNumber) {
    lua_Number version;
    version = lua_tonumber(L, 1);
    printf("La version obtenida es numérica %f\n", version);
  } else {
    // Asumo que es un string
    const char* versionStr;
    unsigned int strLen;
    versionStr = lua_tolstring(L, 1, &strLen);
    printf("La version obtenida no es numerica, es un string: %s\n", versionStr);
    printf("strLen: %d\n", strLen);
  }
  // Limpio el stack
  stackSize = lua_gettop(L);
  printf("Tamaño previo al pop: %d\n", stackSize);
  lua_pop(L, 1);
  // Verifico que efectivamente decrementó su tamaño
  stackSize = lua_gettop(L);
  printf("Tamaño final del stack: %d\n", stackSize);
  return 0;
}