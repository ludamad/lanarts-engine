#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include "fov/fov.h"
#include "GameTiles.h"

using namespace ldungeon_gen;
using namespace luawrap;

static void calculate(fov& fov, int ptx, int pty) {
    return fov.calculate(ptx, pty);
}
//static bool within_fov(fov& fov, int grid_x, int grid_y) {
//    return fov.within_fov(grid_x, grid_y);
//}

static void update_seen_map(fov& fov, const BoolGridRef& seen) {
    fov.update_seen_map(seen);
}
static bool within_fov(fov& fov, const BBox& bbox) {
    return fov.within_fov(bbox);
}
static BBox tiles_covered(fov& fov) {
    return fov.tiles_covered();
}

LuaValue lua_fov(lua_State* L) {
	LuaValue meta = luameta_new(L, "FieldOfView");
	LuaValue methods = luameta_constants(meta);

	methods["calculate"].bind_function(calculate);
	methods["within_fov"].bind_function(within_fov);
	methods["tiles_covered"].bind_function(tiles_covered);
	methods["update_seen_map"].bind_function(update_seen_map);

	luameta_gc<fov>(meta);

	return meta;
}

static int new_fvo(lua_State* L) {
    void* valptr = luameta_newuserdata(L, lua_fov, sizeof(fov));
    MapPtr map = get<MapPtr>(L, 1);
    int radius = get<int>(L, 2);
    new (valptr) fov(map, radius);
    return 1;
}

int luaopen_FieldOfView(lua_State *L) {
	luawrap::install_userdata_type<fov, &lua_fov>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_fvo);
	module.push();
	return 1;
}
