#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include "GameView.h"

LuaValue lua_gameviewmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "GameView");
	LuaValue methods = luameta_constants(meta);

	luameta_gc<GameView>(meta);

	return meta;
}

static GameView new_gameview(int width, int height) {
	return GameView(width, height);
}

int luaopen_GameView(lua_State *L) {
	luawrap::install_userdata_type<GameView, &lua_gameviewmetatable>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_gameview);
	module.push();
	return 1;
}
