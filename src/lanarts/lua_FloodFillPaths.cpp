#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include <ldungeon_gen/Map.h>

#include "BoolGridRef.h"
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

static int set_map(lua_State* L) {
    FloodFillPaths& paths = *get<FloodFillPaths*>(L, 1);
    ldungeon_gen::MapPtr map = get<ldungeon_gen::MapPtr>(L, 2);
    BoolGridRef sight_map;
    if (lua_gettop(L) >= 3) {
        sight_map = *get<BoolGridRef*>(L, 3);
    }
    paths.set_map(map, sight_map);
    return 0;
}

static BBox bounds(FloodFillPaths& paths) {
    return paths.location();
}

LuaValue lua_floodfillmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "FloodFillPaths");
	LuaValue methods = luameta_constants(meta);

	methods["interpolated_direction"].bind_function(interpolated_direction);
    methods["update"].bind_function(update);
    methods["set_map"].bind_function(set_map);
    methods["bounds"].bind_function(bounds);

	luameta_gc<FloodFillPaths>(meta);

	return meta;
}

static FloodFillPaths new_floodfill() {
	return FloodFillPaths();
}

int luaopen_FloodFillPaths(lua_State *L) {
	luawrap::install_userdata_type<FloodFillPaths, &lua_floodfillmetatable>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_floodfill);
	module.push();
	return 1;
}
