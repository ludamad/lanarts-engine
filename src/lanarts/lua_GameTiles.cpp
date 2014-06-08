#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include "GameTiles.h"

static bool radius_test(GameTiles& tiles, const Pos& xy, int rad) {
    return tiles.radius_test(xy, rad);
}

static bool line_test(GameTiles& tiles, const Pos& from_xy, const Pos& to_xy) {
    return tiles.line_test(from_xy, to_xy);
}

LuaValue lua_gametilesmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "GameTiles");
	LuaValue methods = luameta_constants(meta);

	methods["radius_test"].bind_function(radius_test);
	methods["line_test"].bind_function(line_test);

	luameta_gc<GameTiles>(meta);

	return meta;
}

static GameTiles new_game_tiles(BoolGridRef& solidity, BoolGridRef& seen, BoolGridRef& seethrough) {
	return GameTiles(solidity, seen, seethrough);
}

int luaopen_GameTiles(lua_State *L) {
	luawrap::install_userdata_type<GameTiles, &lua_gametilesmetatable>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_game_tiles);
	module.push();
	return 1;
}
