#include <cstdlib>
#include <lua.hpp>

#include "lanarts/opengl/gl_extensions.h"
#include <luawrap/luawrap.h>
#include <lcommon/strformat.h>

#include <stdexcept>

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
//int luaopen_b2_vendor(lua_State* L);
}

int luaopen_SDL(lua_State *L);
int luaopen_ldraw(lua_State *L);
int luaopen_SerializeBuffer(lua_State *L);

extern "C" {
#include <luajit.h>
}

// For luajit GDB helpers, and the shutdown hook:
lua_State* globalL = NULL;
std::string _luatrace() {
    luawrap::globals(globalL)["debug"]["traceback"].push();
    return luawrap::call<std::string>(globalL);
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

void lua_lanarts_core_bindings(lua_State* L);

void LanartsShutdownHook() {
    lua_State* L = globalL;
    luawrap::globals(L)["__lanarts_shutdown_hook"].push();
    if (!lua_isnil(L, -1)) {
        lua_call(L, 0, 0);
    }
}

static bool __HOOK_INITED = false;
void SetLanartsShutdownHook(LuaValue hook) {
    luawrap::globals(hook.luastate())["__lanarts_shutdown_hook"] = hook;
    if (!__HOOK_INITED) {
        atexit(LanartsShutdownHook);
        __HOOK_INITED = true;
    }
}

void LanartsMOAILuaExtHook(lua_State* L) {
    globalL = L;

    // LuaJIT configuration
    lua_vm_configure(L);

    // OpenGL configuration bindings
    luawrap::globals(L)["gl_set_vsync"].bind_function(gl_set_vsync);
    luawrap::globals(L)["string"]["pack"].bind_function(str_pack);
    luawrap::globals(L)["SetLanartsShutdownHook"].bind_function(SetLanartsShutdownHook);

	lua_extend(L, luayaml_module, "yaml");
	lua_extend(L, luaopen_lpeg, "lpeg");
	lua_extend(L, luaopen_linenoise, "linenoise");
	lua_extend(L, luaopen_luv, "luv");
    lua_extend(L, luaopen_enet, "enet");
    lua_extend(L, luaopen_SDL, "sdl");
    lua_extend(L, luaopen_ldraw, "lanarts.draw");
    lua_extend(L, luaopen_SerializeBuffer, "DataBuffer");

//	lua_extend(L, luaopen_b2_vendor, "box2d");

	lua_lanarts_core_bindings(L);
}
