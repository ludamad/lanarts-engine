#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include "fov/fov.h"
#include "GameTiles.h"

using namespace ldungeon_gen;
using namespace luawrap;

static void calculate(fov& fov, MapPtr& map, int ptx, int pty) {
    return fov.calculate(map, ptx, pty);
}
static bool within_fov(fov& fov, int grid_x, int grid_y) {
    return fov.within_fov(grid_x - 1, grid_y - 1);
}
static void resize(fov& fov, int radius) {
    return fov.resize(radius);
}

static bool fov_rectangle_visible(fov& fov, BBox rect) {
    int w = rect.width(), h = rect.height();
    int mingrid_x = rect.x1 / 32, mingrid_y = rect.y1 / 32;
    int maxgrid_x = rect.x2 / 32, maxgrid_y = rect.y2 / 32;
    return fov.within_fov(BBox(mingrid_x, mingrid_y, maxgrid_x, maxgrid_y));
}

static bool fov_circle_visible(fov& fov, int x, int y, int radius) {
    return fov_rectangle_visible(fov,
        BBox(Pos(x,y) - Pos(radius, radius), Size(radius * 2, radius * 2))
    );
}

static void update_seen_map(fov& fov, const BoolGridRef& seen) {
    fov.update_seen_map(seen);
}
//static bool within_fov(fov& fov, const BBox& bbox) {
//    return fov.within_fov(bbox);
//}
static BBox tiles_covered(fov& fov) {
    BBox bbox = fov.tiles_covered();
    // Lua correction
    return BBox(bbox.x1 + 1, bbox.y1 + 1, bbox.x2 + 1, bbox.y2 + 1);
}

LuaValue lua_fov(lua_State* L) {
	LuaValue meta = luameta_new(L, "FieldOfView");
	LuaValue methods = luameta_constants(meta);

	methods["calculate"].bind_function(calculate);
	methods["resize"].bind_function(resize);
	methods["within_fov"].bind_function(within_fov);
	methods["tiles_covered"].bind_function(tiles_covered);
	methods["circle_visible"].bind_function(fov_circle_visible);
	methods["update_seen_map"].bind_function(update_seen_map);

	luameta_gc<fov>(meta);

	return meta;
}

static int new_fvo(lua_State* L) {
    void* valptr = luameta_newuserdata(L, lua_fov, sizeof(fov));
    int radius = get<int>(L, 1);
    new (valptr) fov(radius);
    return 1;
}

int luaopen_FieldOfView(lua_State *L) {
	luawrap::install_userdata_type<fov, &lua_fov>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_fvo);
    luameta_push(L, &lua_fov);
    module["metatable"].pop();
	module.push();
	return 1;
}
