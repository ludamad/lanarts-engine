#include <lua.hpp>

int luaopen_BoolGrid(lua_State* L);
int luaopen_FloodFillPaths(lua_State* L);
int luaopen_GameInstSet(lua_State* L);
int luaopen_RVOWorld(lua_State* L);
int luaopen_GameTiles(lua_State* L);
int luaopen_GameView(lua_State* L);
int luaopen_lanarts_util(lua_State* L);
int luaopen_FieldOfView(lua_State *L);

static void lua_extend(lua_State* L, lua_CFunction func, const char* module_name) {
    lua_getfield(L, LUA_GLOBALSINDEX, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, func);
    lua_setfield(L, -2, module_name);
}

void lua_lanarts_bindings(lua_State* L) {
    lua_extend(L, luaopen_BoolGrid, "BoolGrid");
    lua_extend(L, luaopen_FloodFillPaths, "lanarts.FloodFillPaths");
    lua_extend(L, luaopen_GameInstSet, "lanarts.GameInstSet");
    lua_extend(L, luaopen_RVOWorld, "lanarts.RVOWorld");
    lua_extend(L, luaopen_GameTiles, "lanarts.GameTiles");
    lua_extend(L, luaopen_GameView, "lanarts.GameView");
    lua_extend(L, luaopen_FieldOfView, "lanarts.FieldOfView");
    lua_extend(L, luaopen_lanarts_util, "lanarts.util");
}
