#include <lua.hpp>

#include <ldungeon_gen/lua_ldungeon.h>
#include <luawrap/luawrap.h>

int luaopen_BoolGrid(lua_State* L);
int luaopen_FloodFillPaths(lua_State* L);
int luaopen_GameInstSet(lua_State* L);
int luaopen_RVOWorld(lua_State* L);
int luaopen_GameTiles(lua_State* L);
int luaopen_GameView(lua_State* L);
int luaopen_core_util(lua_State* L);
int luaopen_FieldOfView(lua_State *L);

static void lua_extend(lua_State* L, lua_CFunction func, const char* module_name) {
    lua_getfield(L, LUA_GLOBALSINDEX, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, func);
    lua_setfield(L, -2, module_name);
}

void lua_lanarts_core_bindings(lua_State* L) {
    lua_extend(L, luaopen_BoolGrid, "BoolGrid");
    lua_extend(L, luaopen_FloodFillPaths, "core.FloodFillPaths");
    lua_extend(L, luaopen_GameInstSet, "core.GameInstSet");
    lua_extend(L, luaopen_RVOWorld, "core.RVOWorld");
    lua_extend(L, luaopen_GameTiles, "core.GameTiles");
    lua_extend(L, luaopen_GameView, "core.GameView");
    lua_extend(L, luaopen_FieldOfView, "core.FieldOfView");
    lua_extend(L, luaopen_core_util, "core.util");


    LuaValue module = LuaValue::newtable(L);
    luawrap::globals(L)["package"]["loaded"]["core.TileMap"] = module;

    ldungeon_gen::lua_register_ldungeon(module, /*Register lcommon: */ true);
}
