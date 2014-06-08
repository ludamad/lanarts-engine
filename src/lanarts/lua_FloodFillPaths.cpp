#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include "FloodFillPaths.h"

using namespace luawrap;

static int interpolated_direction(lua_State* L) {
    FloodFillPaths& paths = *get<FloodFillPaths*>(L, 1);
    BBox bbox(lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), lua_tointeger(L, 5));
    double speed = lua_tonumber(L, 6);

    PosF result = paths.interpolated_direction(bbox, speed);

    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);
    return 2;
}

static void update(FloodFillPaths& paths, double x, double y, int radius) {
    paths.fill_paths_in_radius(Pos(x, y), radius);
}

LuaValue lua_floodfillmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "FloodFillPaths");
	LuaValue methods = luameta_constants(meta);

	methods["interpolated_direction"].bind_function(interpolated_direction);
	methods["update"].bind_function(update);

	luameta_gc<FloodFillPaths>(meta);

	return meta;
}

static FloodFillPaths new_floodfill(BoolGridRef& solidity) {
	return FloodFillPaths(solidity);
}

int luaopen_FloodFillPaths(lua_State *L) {
	luawrap::install_userdata_type<FloodFillPaths, &lua_floodfillmetatable>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_floodfill);
	module.push();
	return 1;
}
