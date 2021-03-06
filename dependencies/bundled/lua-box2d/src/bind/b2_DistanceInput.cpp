/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2DistanceInput
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "Box2D/Collision/b2Distance.h"


/** Set attributes (key, value)
 * 
 */
static int b2DistanceInput__set_(lua_State *L) {

  b2DistanceInput *self = *((b2DistanceInput **)dub_checksdata_n(L, 1, "b2.DistanceInput"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub_hash(key, 6);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "proxyA")) break;
      self->proxyA = **((b2DistanceProxy **)dub_checksdata_n(L, 3, "b2.DistanceProxy"));
      return 0;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "proxyB")) break;
      self->proxyB = **((b2DistanceProxy **)dub_checksdata_n(L, 3, "b2.DistanceProxy"));
      return 0;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "transformA")) break;
      self->transformA = **((b2Transform **)dub_checksdata_n(L, 3, "b2.Transform"));
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "transformB")) break;
      self->transformB = **((b2Transform **)dub_checksdata_n(L, 3, "b2.Transform"));
      return 0;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "useRadii")) break;
      self->useRadii = luaL_checkboolean(L, 3);
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
static int b2DistanceInput__get_(lua_State *L) {

  b2DistanceInput *self = *((b2DistanceInput **)dub_checksdata_n(L, 1, "b2.DistanceInput", true));
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
  int key_h = dub_hash(key, 6);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "proxyA")) break;
      dub_pushudata(L, &self->proxyA, "b2.DistanceProxy", false);
      return 1;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "proxyB")) break;
      dub_pushudata(L, &self->proxyB, "b2.DistanceProxy", false);
      return 1;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "transformA")) break;
      dub_pushudata(L, &self->transformA, "b2.Transform", false);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "transformB")) break;
      dub_pushudata(L, &self->transformB, "b2.Transform", false);
      return 1;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "useRadii")) break;
      lua_pushboolean(L, self->useRadii);
      return 1;
    }
  }
  return 0;
}

/** b2DistanceInput()
 * 
 */
static int b2DistanceInput_b2DistanceInput(lua_State *L) {
  try {
    b2DistanceInput *retval__ = new b2DistanceInput();
    dub_pushudata(L, retval__, "b2.DistanceInput", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "b2DistanceInput: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "b2DistanceInput: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int b2DistanceInput___tostring(lua_State *L) {
  b2DistanceInput *self = *((b2DistanceInput **)dub_checksdata_n(L, 1, "b2.DistanceInput"));
  lua_pushfstring(L, "b2.DistanceInput: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2DistanceInput_member_methods[] = {
  { "__newindex"   , b2DistanceInput__set_ },
  { "__index"      , b2DistanceInput__get_ },
  { "new"          , b2DistanceInput_b2DistanceInput },
  { "__tostring"   , b2DistanceInput___tostring },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_b2_DistanceInput(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.DistanceInput");
  // <mt>

  // register member methods
  luaL_register(L, NULL, b2DistanceInput_member_methods);
  // save meta-table in b2
  dub_register(L, "b2", "DistanceInput", "DistanceInput");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
