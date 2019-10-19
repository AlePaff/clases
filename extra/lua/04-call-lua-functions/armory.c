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
#include <string.h>
#include <stdio.h>

/**
 * Esta función leerá la variable "version" almacenada en un script de .lua
 */
int getDamage(lua_State* L, const char* weaponName, int numberHits);

int main(int argc, char* argv[]) {
  int result;
  if (argc == 3) {
    const char* armory_path = argv[1]; 
    const char* calculator_path = argv[2];
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    int result;
    result = luaL_dofile(L, armory_path);
    result = luaL_dofile(L, calculator_path);
    if (result == 0) {
      result = getDamage(L, "sword", 2);
    }
    lua_close(L);
  } else {
    printf("Uso: %s armory.lua calculator.lua\n", argv[0]);
    return 1;
  }
  return result;
}

int getDamage(lua_State* L, const char* weaponName, int numberHits) {
  // Chequeo el tamaño del stack de variables del motor de lua
  int stackSize = lua_gettop(L);
  printf("Tamaño del stack: %d\n", stackSize);
  // Agrego al stack la función a llamar
  lua_getglobal(L, "getDamage");
  // Agrego al stack los parámetros de la función a llamar
  lua_pushlstring(L, weaponName, strlen(weaponName));
  lua_pushnumber(L, numberHits);
  // Llamo a la función
  // lua_call(L, numParamsEntrada, numParamsSalida)
  // La función recibe 2 parámetros y devuelve 1
  lua_call(L, 2, 1);
  int damage = lua_tonumber(L, 1);
  printf("Se realizaron %d golpes con el arma %s: daño total: %d\n",
    numberHits, weaponName, damage);
  stackSize = lua_gettop(L);
  printf("Tamaño del stack post pushes: %d\n", stackSize);
  // Limpio el stack
  lua_pop(L, 1);
  // Verifico que efectivamente decrementó su tamaño
  stackSize = lua_gettop(L);
  printf("Tamaño final del stack: %d\n", stackSize);
  return 0;
}