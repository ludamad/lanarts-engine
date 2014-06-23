/*
 * lua_colour_tests.cpp:
 *  Test colour bindings in lua
 */

#include <lua.hpp>

#include <lcommon/unittest.h>

#include <luawrap/testutils.h>
#include <luawrap/LuaValue.h>
#include <luawrap/functions.h>

#include "Colour.h"

#include "lua_ldraw.h"

SUITE(lua_colour_tests) {
	static void colour_func(const Colour& range) {
		CHECK(range == Colour(1,2,3,255));
	}

	TEST(lua_colour_bind_test) {
		TestLuaState L;

		LuaValue globals = luawrap::globals(L);

		ldraw::lua_register_ldraw(L, globals);

		globals["colour_func"] = luawrap::function(L, colour_func);
		{
			const char* code = "colour_func({1,2,3,255})\n";
			lua_assert_valid_dostring(L, code);
		}
		{
			const char* code = "colour_func({1,2,3})\n";
			lua_assert_valid_dostring(L, code);
		}
		{
			const char* code = "colour_func({1,2})\n";
			lua_assert_invalid_dostring(L, code);
		}
		{
			const char* code = "colour_func({1,2,3,255,255})\n";
			lua_assert_invalid_dostring(L, code);
		}
		L.finish_check();
	}
}
