/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2SolverData
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "Box2D/Dynamics/b2TimeStep.h"


/** Set attributes (key, value)
 * 
 */
static int b2SolverData__set_(lua_State *L) {

  b2SolverData *self = *((b2SolverData **)dub_checksdata_n(L, 1, "b2.SolverData"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub_hash(key, 4);
  switch(key_h) {
    case 0: {
      if (DUB_ASSERT_KEY(key, "step")) break;
      self->step = **((b2TimeStep **)dub_checksdata_n(L, 3, "b2.TimeStep"));
      return 0;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "positions")) break;
      dub_protect(L, 1, 3, "positions");
      self->positions = *((b2Position **)dub_checksdata_n(L, 3, "b2.Position"));
      return 0;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "velocities")) break;
      dub_protect(L, 1, 3, "velocities");
      self->velocities = *((b2Velocity **)dub_checksdata_n(L, 3, "b2.Velocity"));
      return 0;
    }
  }
  if (lua_istable(L, 1)) {
    lua_rawset(L, 1);
  } else {
    luaL_error(L, KEY_EXCEPTION_MSG, key);
  }
  return 0;
}

/** Get attributes (key)
 * 
 */
static int b2SolverData__get_(lua_State *L) {

  b2SolverData *self = *((b2SolverData **)dub_checksdata_n(L, 1, "b2.SolverData", true));
  const char *key = luaL_checkstring(L, 2);
  // <self> "key" <mt>
  // rawget(mt, key)
  lua_pushvalue(L, 2);
  // <self> "key" <mt> "key"
  lua_rawget(L, -2);
  if (!lua_isnil(L, -1)) {
    // Found method.
    return 1;
  } else {
    // Not in mt = attribute access.
    lua_pop(L, 2);
  }
  int key_h = dub_hash(key, 4);
  switch(key_h) {
    case 0: {
      if (DUB_ASSERT_KEY(key, "step")) break;
      dub_pushudata(L, &self->step, "b2.TimeStep", false);
      return 1;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "positions")) break;
      b2Position *retval__ = self->positions;
      if (!retval__) return 0;
      dub_pushudata(L, retval__, "b2.Position", false);
      return 1;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "velocities")) break;
      b2Velocity *retval__ = self->velocities;
      if (!retval__) return 0;
      dub_pushudata(L, retval__, "b2.Velocity", false);
      return 1;
    }
  }
  return 0;
}

/** b2SolverData()
 * 
 */
static int b2SolverData_b2SolverData(lua_State *L) {
  try {
    b2SolverData *retval__ = new b2SolverData();
    dub_pushudata(L, retval__, "b2.SolverData", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "b2SolverData: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "b2SolverData: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int b2SolverData___tostring(lua_State *L) {
  b2SolverData *self = *((b2SolverData **)dub_checksdata_n(L, 1, "b2.SolverData"));
  lua_pushfstring(L, "b2.SolverData: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2SolverData_member_methods[] = {
  { "__newindex"   , b2SolverData__set_   },
  { "__index"      , b2SolverData__get_   },
  { "new"          , b2SolverData_b2SolverData },
  { "__tostring"   , b2SolverData___tostring },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_b2_SolverData(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.SolverData");
  // <mt>

  // register member methods
  luaL_register(L, NULL, b2SolverData_member_methods);
  // save meta-table in b2
  dub_register(L, "b2", "SolverData", "SolverData");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
