#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>
#include <luawrap/macros.h>

#include "BoolGridRef.h"

using namespace luawrap;

static int get_size(lua_State* L) {
    BoolGridRef* ref = get<BoolGridRef*>(L, 1);
    lua_pushinteger(L, (*ref)->width());
    lua_pushinteger(L, (*ref)->height());
    return 2;
}

static BoolGridRef _clone(const BoolGridRef& ref) {
    return BoolGridRef(new Grid<bool>(*ref));
}
static void copy(const BoolGridRef& ref1, BoolGridRef& ref2) {
    *ref2 = *ref1;
}

/* Retrieve data into a preallocated Lua table */
static int lget_row(lua_State* L) {
    BoolGridRef grid = luawrap::get<BoolGridRef>(L, 1);
    // Note, Lua indexing corrections are applied
    int x1 = luaL_checkinteger(L, 3) - 1;
    int x2 = luaL_checkinteger(L, 4);
    int y = luaL_checkinteger(L, 5) - 1;
    // What to use outside of map bounds?
    bool fill = lua_toboolean(L, 6);
    int w = grid->width(), h = grid->height();
    Pos pos(x1, y);
    int i = 1;
    for (; pos.x < x2; pos.x++) {
        if (pos.y < 0 || pos.y >= h || pos.x < 0 || pos.x >= w) {
            lua_pushboolean(L, fill);
        } else {
            lua_pushboolean(L, (*grid)[pos]);
        }
        lua_rawseti(L, 2, i);
        i++;
    }
    return 0;
}

LuaValue lua_boolgridmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "BoolGrid");
	LuaValue methods = luameta_constants(meta);

	methods["get_size"].bind_function(get_size);
	methods["clone"].bind_function(_clone);
    methods["copy"].bind_function(copy);
    methods["get_row"].bind_function(lget_row);

    LUAWRAP_SET_TYPE(BoolGridRef);

    LUAWRAP_METHOD(methods, set, (*OBJ)[Pos(get<int>(L, 2) - 1, get<int>(L, 3) - 1)] = get<bool>(L, 4));
    LUAWRAP_GETTER(methods, get, (bool)(*OBJ)[Pos(get<int>(L, 2) - 1, get<int>(L, 3) - 1)]);

	luameta_gc<BoolGridRef>(meta);

	return meta;
}

static BoolGridRef new_boolgrid(int width, int height, bool solidity) {
	return BoolGridRef(new Grid<bool>(Size(width, height), solidity));
}

int luaopen_BoolGrid(lua_State *L) {
	luawrap::install_userdata_type<BoolGridRef, &lua_boolgridmetatable>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_boolgrid);
	luameta_push(L, &lua_boolgridmetatable);
    module["metatable"].pop();
	module.push();
	return 1;
}
