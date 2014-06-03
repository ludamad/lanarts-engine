#include <stdlib.h>
#include <lua.hpp>

#include <ldungeon_gen/lua_ldungeon.h>
#include <luawrap/luawrap.h>

extern "C" {
// From dependency lua-yaml:
int luayaml_module(lua_State* L);
// From dependency lpeg:
int luaopen_lpeg(lua_State* L);
// From dependency linenoise:
int luaopen_linenoise(lua_State* L);
// From dependency luv:
int luaopen_luv(lua_State* L);
// For ENet bindings:
int luaopen_enet(lua_State* L);
// For Box2D bindings:
int luaopen_b2_vendor(lua_State* L);
}

extern "C" {
#include <luajit.h>
}

// LuaJIT only: Catch C++ exceptions and convert them to Lua error messages.
static int luajit_wrap_exceptions(lua_State *L, lua_CFunction f) {
    try {
        return f(L);  // Call wrapped function and return result.
    } catch (const char *s) {  // Catch and convert exceptions.
        lua_pushstring(L, s);
    } catch (const std::exception& e) {
        lua_pushstring(L, e.what());
    }
    return lua_error(L);  // Rethrow as a Lua error.
}

static void lua_vm_configure(lua_State* L) {
    lua_pushlightuserdata(L, (void *)luajit_wrap_exceptions);
    luaJIT_setmode(L, -1, LUAJIT_MODE_WRAPCFUNC|LUAJIT_MODE_ON);
    lua_pop(L, 1);
}

static void lua_extend(lua_State* L, lua_CFunction func, const char* module_name) {
	lua_getfield(L, LUA_GLOBALSINDEX, "package");
	lua_getfield(L, -1, "preload");
	lua_pushcfunction(L, func);
	lua_setfield(L, -2, module_name);
}

void LanartsMOAILuaExtHook(lua_State* L) {
    // LuaJIT configuration
    lua_vm_configure(L);

	lua_extend(L, luayaml_module, "yaml");
	lua_extend(L, luaopen_lpeg, "lpeg");
	lua_extend(L, luaopen_linenoise, "linenoise");
	lua_extend(L, luaopen_luv, "luv");
        lua_extend(L, luaopen_enet, "enet");
	lua_extend(L, luaopen_b2_vendor, "box2d");

	LuaValue module = LuaValue::newtable(L);
	luawrap::globals(L)["package"]["loaded"]["lanarts.mapgen"] = module;

	ldungeon_gen::lua_register_ldungeon(module, /*Register lcommon: */ true);

}
