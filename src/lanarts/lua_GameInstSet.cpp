#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include "GameInstSet.h"

static void copy(GameInstSet* from, GameInstSet* to) {
    from->copy_to(*to);
}

static obj_id add_instance(GameInstSet* set, double x, double y, double radius,
        double target_radius, bool solid) {
    return set->add_instance(x, y, radius, target_radius, solid);
}

static void update_instance(LuaStackValue value, obj_id id, double x, double y, double radius,
        double target_radius, bool solid) {

    GameInstSet* inst_set = value.as<GameInstSet*>();
    GameInst* inst = inst_set->get_instance(id);
    if (inst == NULL) {
        luaL_error(value.luastate(), "Object with id '%d' does not exist!", id);
        return;
    }
    inst->x = x;
    inst->y = y;
    inst->radius = radius;
    inst->target_radius = target_radius;
    inst->solid = solid;
}

static int get_instance(lua_State* L) {
    GameInstSet* inst_set = luawrap::get<GameInstSet*>(L, 1);
    obj_id id = lua_tointeger(L, 2);
    GameInst* inst = inst_set->get_instance(id);
    if (inst == NULL) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushnumber(L, inst->x);
    lua_pushnumber(L, inst->y);
    lua_pushnumber(L, inst->radius);
    lua_pushnumber(L, inst->target_radius);
    lua_pushboolean(L, inst->solid);
    return 5;
}
static void remove_instance(GameInstSet* set, obj_id id) {
    set->remove_instance(id);
}

static void step(GameInstSet* set) {
    set->update();
}
// object_radius_test(inst_set, obj_id, x?, y?, radius?)
static int object_radius_test(lua_State* L) {
    int n_args = lua_gettop(L);

    GameInstSet* set = luawrap::get<GameInstSet*>(L, 1);
    obj_id id = lua_tointeger(L, 2);

    // Optional arguments, override object properties:
    double x = n_args >= 3 ? lua_tonumber(L, 3) : -1;
    double y = n_args >= 4 ? lua_tonumber(L, 4) : -1;
    double rad = n_args >= 5 ? lua_tonumber(L, 5) : -1;

    obj_id collided_id = set->object_radius_test(id, x, y, rad);
    if (collided_id == 0) {
        lua_pushnil(L);
    } else {
        lua_pushinteger(L, collided_id);
    }

    return 1;
}

const int MAX_RESULTS = 256;

// Copy into a given list
// object_radius_query(set, id, out results, opt x, opt y, opt rad)
static int object_radius_query(lua_State* L) {
    int n_args = lua_gettop(L);

    GameInstSet* set = luawrap::get<GameInstSet*>(L, 1);
    obj_id id = lua_tointeger(L, 2);

    // Parameter 3 is the table to read results into
    // Optional arguments, override object properties:
    double x = n_args >= 4 ? lua_tonumber(L, 4) : -1;
    double y = n_args >= 5 ? lua_tonumber(L, 5) : -1;
    double rad = n_args >= 6 ? lua_tonumber(L, 6) : -1;

    GameInst results[MAX_RESULTS];
    int amount = set->object_radius_test(set->get_instance(id), results, MAX_RESULTS, x, y, rad);
    for (int i = 1; i <= amount; i++) {
        lua_pushinteger(L, results[i-1].id);
        // Write into the result table
        lua_rawseti(L, 3, i);
    }

    return 0;
}

LuaValue lua_gameinstsetmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "GameInstSet");
	LuaValue methods = luameta_constants(meta);

	methods["add_instance"].bind_function(add_instance);
	methods["get_instance"].bind_function(get_instance);
	methods["update_instance"].bind_function(update_instance);
	methods["remove_instance"].bind_function(remove_instance);
	methods["copy"].bind_function(copy);
	methods["step"].bind_function(step);
	methods["object_radius_test"].bind_function(object_radius_test);
	methods["object_radius_query"].bind_function(object_radius_query);

	luameta_gc<GameInstSet>(meta);

	return meta;
}

static int new_game_inst_set(lua_State* L) {
    void* valptr = luameta_newuserdata(L, lua_gameinstsetmetatable, sizeof(GameInstSet));
    new (valptr) GameInstSet(luawrap::get<int>(L, 1), luawrap::get<int>(L, 2));
    return 1;
}

int luaopen_GameInstSet(lua_State *L) {
	luawrap::install_userdata_type<GameInstSet, &lua_gameinstsetmetatable>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_game_inst_set);
	module.push();
	return 1;
}
