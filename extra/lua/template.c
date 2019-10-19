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

#ifdef __cplusplus
extern "C"{
#endif
#ifdef __cplusplus
}
#endif

