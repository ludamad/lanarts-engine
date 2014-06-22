#include <cassert>
#include <cmath>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include "GameTiles.h"

static bool radius_test(const ldungeon_gen::MapPtr& map, double x, double y, int rad) {
    return GameTiles(map).radius_test(Pos(lrint(x), lrint(y)), rad);
}

static bool line_test(const ldungeon_gen::MapPtr& map, double x1, double y1, double x2, double y2) {
    return GameTiles(map).line_test(Pos(lrint(x1), lrint(y1)), Pos(x2, y2));
}

LuaValue lua_gametilesmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "GameTiles");
	LuaValue methods = luameta_constants(meta);

	methods["radius_test"].bind_function(radius_test);
	methods["line_test"].bind_function(line_test);

	luameta_gc<GameTiles>(meta);

	return meta;
}

int luaopen_GameTiles(lua_State *L) {
	luawrap::install_userdata_type<GameTiles, &lua_gametilesmetatable>();
	LuaValue module = LuaValue::newtable(L);
	module["radius_test"].bind_function(radius_test);
	module["line_test"].bind_function(line_test);
//	module["create"].bind_function(new_game_tiles);
	module.push();
	return 1;
}
