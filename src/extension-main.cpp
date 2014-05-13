#include <stdlib.h>
#include <lua.hpp>

extern "C" {
// From dependency lua-yaml:
int luayaml_module(lua_State *L);
}

void LanartsMOAILuaExtHook(lua_State* L) {
   lua_getfield(L, LUA_GLOBALSINDEX, "package");
   lua_getfield(L, -1, "preload");
   lua_pushcfunction(L, luayaml_module);
   lua_setfield(L, -2, "yaml");
}
