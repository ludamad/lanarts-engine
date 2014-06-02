/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2GearJointDef
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "Box2D/Dynamics/Joints/b2GearJoint.h"


/** ~b2GearJointDef()
 * 
 */
static int b2GearJointDef__b2GearJointDef(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub_checksdata_d(L, 1, "b2.GearJointDef"));
    if (userdata->gc) {
      b2GearJointDef *self = (b2GearJointDef *)userdata->ptr;
      delete self;
    }
    userdata->gc = false;
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "~b2GearJointDef: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "~b2GearJointDef: Unknown exception");
  }
  return dub_error(L);
}

/** Set attributes (key, value)
 * 
 */
static int b2GearJointDef__set_(lua_State *L) {

  b2GearJointDef *self = *((b2GearJointDef **)dub_checksdata_n(L, 1, "b2.GearJointDef"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub_hash(key, 20);
  switch(key_h) {
    case 11: {
      if (DUB_ASSERT_KEY(key, "joint1")) break;
      dub_protect(L, 1, 3, "joint1");
      self->joint1 = *((b2Joint **)dub_checksdata_n(L, 3, "b2.Joint"));
      return 0;
    }
    case 12: {
      if (DUB_ASSERT_KEY(key, "joint2")) break;
      dub_protect(L, 1, 3, "joint2");
      self->joint2 = *((b2Joint **)dub_checksdata_n(L, 3, "b2.Joint"));
      return 0;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "ratio")) break;
      self->ratio = luaL_checknumber(L, 3);
      return 0;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "type")) break;
      self->type = (b2JointType)luaL_checkint(L, 3);
      return 0;
    }
    case 9: {
      if (DUB_ASSERT_KEY(key, "userData")) break;
      dub_protect(L, 1, 3, "userData");
      self->userData = *((void **)dub_checksdata_n(L, 3, "void"));
      return 0;
    }
    case 19: {
      if (DUB_ASSERT_KEY(key, "bodyA")) break;
      dub_protect(L, 1, 3, "bodyA");
      self->bodyA = *((b2Body **)dub_checksdata_n(L, 3, "b2.Body"));
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "bodyB")) break;
      dub_protect(L, 1, 3, "bodyB");
      self->bodyB = *((b2Body **)dub_checksdata_n(L, 3, "b2.Body"));
      return 0;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "collideConnected")) break;
      self->collideConnected = luaL_checkboolean(L, 3);
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
static int b2GearJointDef__get_(lua_State *L) {

  b2GearJointDef *self = *((b2GearJointDef **)dub_checksdata_n(L, 1, "b2.GearJointDef", true));
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
  int key_h = dub_hash(key, 20);
  switch(key_h) {
    case 11: {
      if (DUB_ASSERT_KEY(key, "joint1")) break;
      b2Joint *retval__ = self->joint1;
      if (!retval__) return 0;
      dub_pushudata(L, retval__, "b2.Joint", false);
      return 1;
    }
    case 12: {
      if (DUB_ASSERT_KEY(key, "joint2")) break;
      b2Joint *retval__ = self->joint2;
      if (!retval__) return 0;
      dub_pushudata(L, retval__, "b2.Joint", false);
      return 1;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "ratio")) break;
      lua_pushnumber(L, self->ratio);
      return 1;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "type")) break;
      lua_pushnumber(L, self->type);
      return 1;
    }
    case 9: {
      if (DUB_ASSERT_KEY(key, "userData")) break;
      void *retval__ = self->userData;
      if (!retval__) return 0;
      dub_pushudata(L, retval__, "void", false);
      return 1;
    }
    case 19: {
      if (DUB_ASSERT_KEY(key, "bodyA")) break;
      b2Body *retval__ = self->bodyA;
      if (!retval__) return 0;
      dub_pushudata(L, retval__, "b2.Body", false);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "bodyB")) break;
      b2Body *retval__ = self->bodyB;
      if (!retval__) return 0;
      dub_pushudata(L, retval__, "b2.Body", false);
      return 1;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "collideConnected")) break;
      lua_pushboolean(L, self->collideConnected);
      return 1;
    }
  }
  return 0;
}

/** Cast (class_name)
 * 
 */
static int b2GearJointDef__cast_(lua_State *L) {

  b2GearJointDef *self = *((b2GearJointDef **)dub_checksdata_n(L, 1, "b2.GearJointDef"));
  const char *key = luaL_checkstring(L, 2);
  void **retval__ = (void**)lua_newuserdata(L, sizeof(void*));
  int key_h = dub_hash(key, 2);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "b2.JointDef")) break;
      *retval__ = static_cast<b2JointDef *>(self);
      return 1;
    }
  }
  return 0;
}

/** b2GearJointDef::b2GearJointDef()
 * vendor/Box2D/Box2D/Dynamics/Joints/b2GearJoint.h:29
 */
static int b2GearJointDef_b2GearJointDef(lua_State *L) {
  try {
    b2GearJointDef *retval__ = new b2GearJointDef();
    dub_pushudata(L, retval__, "b2.GearJointDef", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "b2GearJointDef: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "b2GearJointDef: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int b2GearJointDef___tostring(lua_State *L) {
  b2GearJointDef *self = *((b2GearJointDef **)dub_checksdata_n(L, 1, "b2.GearJointDef"));
  lua_pushfstring(L, "b2.GearJointDef: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2GearJointDef_member_methods[] = {
  { "__gc"         , b2GearJointDef__b2GearJointDef },
  { "__newindex"   , b2GearJointDef__set_ },
  { "__index"      , b2GearJointDef__get_ },
  { "_cast_"       , b2GearJointDef__cast_ },
  { "new"          , b2GearJointDef_b2GearJointDef },
  { "__tostring"   , b2GearJointDef___tostring },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_b2_GearJointDef(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.GearJointDef");
  // <mt>

  // register member methods
  luaL_register(L, NULL, b2GearJointDef_member_methods);
  // save meta-table in b2
  dub_register(L, "b2", "GearJointDef", "GearJointDef");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
