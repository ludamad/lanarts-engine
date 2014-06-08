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

LuaValue lua_boolgridmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "BoolGrid");
	LuaValue methods = luameta_constants(meta);

	methods["get_size"].bind_function(get_size);

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
	module.push();
	return 1;
}
