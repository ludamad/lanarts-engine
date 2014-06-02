/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2TOIInput
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "Box2D/Collision/b2TimeOfImpact.h"


/** Set attributes (key, value)
 * 
 */
static int b2TOIInput__set_(lua_State *L) {

  b2TOIInput *self = *((b2TOIInput **)dub_checksdata_n(L, 1, "b2.TOIInput"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub_hash(key, 8);
  switch(key_h) {
    case 3: {
      if (DUB_ASSERT_KEY(key, "proxyA")) break;
      self->proxyA = **((b2DistanceProxy **)dub_checksdata_n(L, 3, "b2.DistanceProxy"));
      return 0;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "proxyB")) break;
      self->proxyB = **((b2DistanceProxy **)dub_checksdata_n(L, 3, "b2.DistanceProxy"));
      return 0;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "sweepA")) break;
      self->sweepA = **((b2Sweep **)dub_checksdata_n(L, 3, "b2.Sweep"));
      return 0;
    }
    case 6: {
      if (DUB_ASSERT_KEY(key, "sweepB")) break;
      self->sweepB = **((b2Sweep **)dub_checksdata_n(L, 3, "b2.Sweep"));
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "tMax")) break;
      self->tMax = luaL_checknumber(L, 3);
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
static int b2TOIInput__get_(lua_State *L) {

  b2TOIInput *self = *((b2TOIInput **)dub_checksdata_n(L, 1, "b2.TOIInput", true));
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
  int key_h = dub_hash(key, 8);
  switch(key_h) {
    case 3: {
      if (DUB_ASSERT_KEY(key, "proxyA")) break;
      dub_pushudata(L, &self->proxyA, "b2.DistanceProxy", false);
      return 1;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "proxyB")) break;
      dub_pushudata(L, &self->proxyB, "b2.DistanceProxy", false);
      return 1;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "sweepA")) break;
      dub_pushudata(L, &self->sweepA, "b2.Sweep", false);
      return 1;
    }
    case 6: {
      if (DUB_ASSERT_KEY(key, "sweepB")) break;
      dub_pushudata(L, &self->sweepB, "b2.Sweep", false);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "tMax")) break;
      lua_pushnumber(L, self->tMax);
      return 1;
    }
  }
  return 0;
}

/** b2TOIInput()
 * 
 */
static int b2TOIInput_b2TOIInput(lua_State *L) {
  try {
    b2TOIInput *retval__ = new b2TOIInput();
    dub_pushudata(L, retval__, "b2.TOIInput", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "b2TOIInput: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "b2TOIInput: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int b2TOIInput___tostring(lua_State *L) {
  b2TOIInput *self = *((b2TOIInput **)dub_checksdata_n(L, 1, "b2.TOIInput"));
  lua_pushfstring(L, "b2.TOIInput: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2TOIInput_member_methods[] = {
  { "__newindex"   , b2TOIInput__set_     },
  { "__index"      , b2TOIInput__get_     },
  { "new"          , b2TOIInput_b2TOIInput },
  { "__tostring"   , b2TOIInput___tostring },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_b2_TOIInput(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.TOIInput");
  // <mt>

  // register member methods
  luaL_register(L, NULL, b2TOIInput_member_methods);
  // save meta-table in b2
  dub_register(L, "b2", "TOIInput", "TOIInput");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
