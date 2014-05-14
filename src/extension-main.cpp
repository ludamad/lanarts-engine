#include <stdlib.h>
#include <lua.hpp>

extern "C" {
// From dependency lua-yaml:
int luayaml_module(lua_State* L);
// From dependency lpeg:
int luaopen_lpeg(lua_State* L);
}

static void lua_extend(lua_State* L, lua_CFunction func, const char* module_name) {
	lua_getfield(L, LUA_GLOBALSINDEX, "package");
	lua_getfield(L, -1, "preload");
	lua_pushcfunction(L, func);
	lua_setfield(L, -2, module_name);
}

void LanartsMOAILuaExtHook(lua_State* L) {
	lua_extend(L, luayaml_module, "yaml");
	lua_extend(L, luaopen_lpeg, "lpeg");
}
