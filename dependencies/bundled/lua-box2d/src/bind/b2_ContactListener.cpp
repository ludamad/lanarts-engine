/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2ContactListener
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"


/** b2ContactListener()
 * 
 */
static int b2ContactListener_b2ContactListener(lua_State *L) {
  try {
    b2ContactListener *retval__ = new b2ContactListener();
    dub_pushudata(L, retval__, "b2.ContactListener", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "b2ContactListener: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "b2ContactListener: Unknown exception");
  }
  return dub_error(L);
}

/** virtual b2ContactListener::~b2ContactListener()
 * vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:84
 */
static int b2ContactListener__b2ContactListener(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub_checksdata_d(L, 1, "b2.ContactListener"));
    if (userdata->gc) {
      b2ContactListener *self = (b2ContactListener *)userdata->ptr;
      delete self;
    }
    userdata->gc = false;
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "~b2ContactListener: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "~b2ContactListener: Unknown exception");
  }
  return dub_error(L);
}

/** virtual void b2ContactListener::BeginContact(b2Contact *contact)
 * vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:87
 */
static int b2ContactListener_BeginContact(lua_State *L) {
  try {
    b2ContactListener *self = *((b2ContactListener **)dub_checksdata(L, 1, "b2.ContactListener"));
    b2Contact *contact = *((b2Contact **)dub_checksdata(L, 2, "Contact"));
    self->BeginContact(contact);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "BeginContact: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "BeginContact: Unknown exception");
  }
  return dub_error(L);
}

/** virtual void b2ContactListener::EndContact(b2Contact *contact)
 * vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:90
 */
static int b2ContactListener_EndContact(lua_State *L) {
  try {
    b2ContactListener *self = *((b2ContactListener **)dub_checksdata(L, 1, "b2.ContactListener"));
    b2Contact *contact = *((b2Contact **)dub_checksdata(L, 2, "Contact"));
    self->EndContact(contact);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "EndContact: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "EndContact: Unknown exception");
  }
  return dub_error(L);
}

/** virtual void b2ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
 * vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:103
 */
static int b2ContactListener_PreSolve(lua_State *L) {
  try {
    b2ContactListener *self = *((b2ContactListener **)dub_checksdata(L, 1, "b2.ContactListener"));
    b2Contact *contact = *((b2Contact **)dub_checksdata(L, 2, "Contact"));
    b2Manifold *oldManifold = *((b2Manifold **)dub_checksdata(L, 3, "b2.Manifold"));
    self->PreSolve(contact, oldManifold);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "PreSolve: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "PreSolve: Unknown exception");
  }
  return dub_error(L);
}

/** virtual void b2ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
 * vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:115
 */
static int b2ContactListener_PostSolve(lua_State *L) {
  try {
    b2ContactListener *self = *((b2ContactListener **)dub_checksdata(L, 1, "b2.ContactListener"));
    b2Contact *contact = *((b2Contact **)dub_checksdata(L, 2, "Contact"));
    b2ContactImpulse *impulse = *((b2ContactImpulse **)dub_checksdata(L, 3, "b2.ContactImpulse"));
    self->PostSolve(contact, impulse);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "PostSolve: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "PostSolve: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int b2ContactListener___tostring(lua_State *L) {
  b2ContactListener *self = *((b2ContactListener **)dub_checksdata_n(L, 1, "b2.ContactListener"));
  lua_pushfstring(L, "b2.ContactListener: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2ContactListener_member_methods[] = {
  { "new"          , b2ContactListener_b2ContactListener },
  { "__gc"         , b2ContactListener__b2ContactListener },
  { "BeginContact" , b2ContactListener_BeginContact },
  { "EndContact"   , b2ContactListener_EndContact },
  { "PreSolve"     , b2ContactListener_PreSolve },
  { "PostSolve"    , b2ContactListener_PostSolve },
  { "__tostring"   , b2ContactListener___tostring },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_b2_ContactListener(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.ContactListener");
  // <mt>

  // register member methods
  luaL_register(L, NULL, b2ContactListener_member_methods);
  // save meta-table in b2
  dub_register(L, "b2", "ContactListener", "ContactListener");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
