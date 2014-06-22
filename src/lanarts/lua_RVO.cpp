#include <cassert>

#define LUAWRAP_LONG_FUNCTIONS
#include <luawrap/luawrap.h>

#include <rvo2/RVO.h>

using namespace RVO;

static int add_instance(RVOSimulator& sim,
        double x,
        double y,
        double radius, double maxSpeed) {

    const int MAX_NEIGHBOURS = 10;
    const float TIME_HORIZON = 2.0f, TIME_STEP = 1.0f;
    const float neighbour_dist = radius * 2;

    return sim.addAgent(Vector2(x, y), neighbour_dist, MAX_NEIGHBOURS,
            TIME_HORIZON, TIME_STEP, radius, maxSpeed);
}

static void remove_instance(RVOSimulator& sim, int id) {
    sim.removeAgent(id);
}

static void update_instance(RVOSimulator& sim,
        int id, double x, double y,
        double radius, double maxSpeed,
        double vx, double vy) {
    sim.setAgentPosition(id, Vector2(x,y));
    sim.setAgentRadius(id, radius);
    sim.setAgentMaxSpeed(id, maxSpeed);
    sim.setAgentPrefVelocity(id, Vector2(vx, vy));
}

static void change_instance_id(RVOSimulator& sim,
        int id, int new_id) {
    sim.changeAgentNo(id, new_id);
}

static int get_velocity(lua_State* L) {
    RVOSimulator* sim = luawrap::get<RVOSimulator*>(L, 1);
    Vector2 velocity = sim->getAgentVelocity(lua_tointeger(L, 2));
    lua_pushnumber(L, velocity.x());
    lua_pushnumber(L, velocity.y());
    return 2;
}

static void step(RVOSimulator& sim) {
    sim.doStep();
}

LuaValue lua_rvoworldmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "RVOWorld");
	LuaValue methods = luameta_constants(meta);

	methods["add_instance"].bind_function(add_instance);
	methods["remove_instance"].bind_function(remove_instance);
	methods["update_instance"].bind_function(update_instance);
	methods["get_velocity"].bind_function(get_velocity);
	methods["change_instance_id"].bind_function(change_instance_id);
	methods["step"].bind_function(step);

	luameta_gc<RVOSimulator>(meta);

	return meta;
}

static int new_rvo_world(lua_State* L) {
    void* valptr = luameta_newuserdata(L, lua_rvoworldmetatable, sizeof(RVOSimulator));
    new (valptr) RVOSimulator();
    return 1;
}

int luaopen_RVOWorld(lua_State *L) {
	luawrap::install_userdata_type<RVOSimulator, &lua_rvoworldmetatable>();
	LuaValue module = LuaValue::newtable(L);
	module["create"].bind_function(new_rvo_world);
	module.push();
	return 1;
}
