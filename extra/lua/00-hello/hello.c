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

int main(int argc, char* argv[]) {
  // Instancio una máquina de Lua
  lua_State *L = luaL_newstate();
  // Cargo bibliotecas
  luaL_openlibs(L);
  int result;
  if (argc == 2) {
    printf("Ejecutando luaL_dofile\n");
    result = luaL_dofile(L, argv[1]);
  } else {
    printf("Ejecutando luaL_dostring\n");
    result = luaL_dostring(L, "print(\"Hello Lua\")");
  }
  lua_close(L);
  return result;
}
