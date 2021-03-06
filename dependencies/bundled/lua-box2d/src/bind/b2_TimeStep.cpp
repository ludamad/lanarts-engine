/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2TimeStep
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "Box2D/Dynamics/b2TimeStep.h"


/** Set attributes (key, value)
 * 
 */
static int b2TimeStep__set_(lua_State *L) {

  b2TimeStep *self = *((b2TimeStep **)dub_checksdata_n(L, 1, "b2.TimeStep"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub_hash(key, 9);
  switch(key_h) {
    case 6: {
      if (DUB_ASSERT_KEY(key, "dt")) break;
      self->dt = luaL_checknumber(L, 3);
      return 0;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "inv_dt")) break;
      self->inv_dt = luaL_checknumber(L, 3);
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "dtRatio")) break;
      self->dtRatio = luaL_checknumber(L, 3);
      return 0;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "velocityIterations")) break;
      self->velocityIterations = luaL_checkint(L, 3);
      return 0;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "positionIterations")) break;
      self->positionIterations = luaL_checkint(L, 3);
      return 0;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "warmStarting")) break;
      self->warmStarting = luaL_checkboolean(L, 3);
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
static int b2TimeStep__get_(lua_State *L) {

  b2TimeStep *self = *((b2TimeStep **)dub_checksdata_n(L, 1, "b2.TimeStep", true));
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
  int key_h = dub_hash(key, 9);
  switch(key_h) {
    case 6: {
      if (DUB_ASSERT_KEY(key, "dt")) break;
      lua_pushnumber(L, self->dt);
      return 1;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "inv_dt")) break;
      lua_pushnumber(L, self->inv_dt);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "dtRatio")) break;
      lua_pushnumber(L, self->dtRatio);
      return 1;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "velocityIterations")) break;
      lua_pushnumber(L, self->velocityIterations);
      return 1;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "positionIterations")) break;
      lua_pushnumber(L, self->positionIterations);
      return 1;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "warmStarting")) break;
      lua_pushboolean(L, self->warmStarting);
      return 1;
    }
  }
  return 0;
}

/** b2TimeStep()
 * 
 */
static int b2TimeStep_b2TimeStep(lua_State *L) {
  try {
    b2TimeStep *retval__ = new b2TimeStep();
    dub_pushudata(L, retval__, "b2.TimeStep", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "b2TimeStep: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "b2TimeStep: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int b2TimeStep___tostring(lua_State *L) {
  b2TimeStep *self = *((b2TimeStep **)dub_checksdata_n(L, 1, "b2.TimeStep"));
  lua_pushfstring(L, "b2.TimeStep: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2TimeStep_member_methods[] = {
  { "__newindex"   , b2TimeStep__set_     },
  { "__index"      , b2TimeStep__get_     },
  { "new"          , b2TimeStep_b2TimeStep },
  { "__tostring"   , b2TimeStep___tostring },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_b2_TimeStep(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.TimeStep");
  // <mt>

  // register member methods
  luaL_register(L, NULL, b2TimeStep_member_methods);
  // save meta-table in b2
  dub_register(L, "b2", "TimeStep", "TimeStep");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
