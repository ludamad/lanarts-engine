/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2BlockAllocator
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "Box2D/Common/b2BlockAllocator.h"


/** b2BlockAllocator::b2BlockAllocator()
 * vendor/Box2D/Box2D/Common/b2BlockAllocator.h:38
 */
static int b2BlockAllocator_b2BlockAllocator(lua_State *L) {
  try {
    b2BlockAllocator *retval__ = new b2BlockAllocator();
    dub_pushudata(L, retval__, "b2.BlockAllocator", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "b2BlockAllocator: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "b2BlockAllocator: Unknown exception");
  }
  return dub_error(L);
}

/** b2BlockAllocator::~b2BlockAllocator()
 * vendor/Box2D/Box2D/Common/b2BlockAllocator.h:39
 */
static int b2BlockAllocator__b2BlockAllocator(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub_checksdata_d(L, 1, "b2.BlockAllocator"));
    if (userdata->gc) {
      b2BlockAllocator *self = (b2BlockAllocator *)userdata->ptr;
      delete self;
    }
    userdata->gc = false;
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "~b2BlockAllocator: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "~b2BlockAllocator: Unknown exception");
  }
  return dub_error(L);
}

/** void * b2BlockAllocator::Allocate(int32 size)
 * vendor/Box2D/Box2D/Common/b2BlockAllocator.h:42
 */
static int b2BlockAllocator_Allocate(lua_State *L) {
  try {
    b2BlockAllocator *self = *((b2BlockAllocator **)dub_checksdata(L, 1, "b2.BlockAllocator"));
    int32 size = dub_checkint(L, 2);
    self->Allocate(size);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Allocate: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Allocate: Unknown exception");
  }
  return dub_error(L);
}

/** void b2BlockAllocator::Free(void *p, int32 size)
 * vendor/Box2D/Box2D/Common/b2BlockAllocator.h:45
 */
static int b2BlockAllocator_Free(lua_State *L) {
  try {
    b2BlockAllocator *self = *((b2BlockAllocator **)dub_checksdata(L, 1, "b2.BlockAllocator"));
    void *p = *((void **)dub_checksdata(L, 2, "void"));
    int32 size = dub_checkint(L, 3);
    self->Free(p, size);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Free: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Free: Unknown exception");
  }
  return dub_error(L);
}

/** void b2BlockAllocator::Clear()
 * vendor/Box2D/Box2D/Common/b2BlockAllocator.h:47
 */
static int b2BlockAllocator_Clear(lua_State *L) {
  try {
    b2BlockAllocator *self = *((b2BlockAllocator **)dub_checksdata(L, 1, "b2.BlockAllocator"));
    self->Clear();
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Clear: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Clear: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int b2BlockAllocator___tostring(lua_State *L) {
  b2BlockAllocator *self = *((b2BlockAllocator **)dub_checksdata_n(L, 1, "b2.BlockAllocator"));
  lua_pushfstring(L, "b2.BlockAllocator: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2BlockAllocator_member_methods[] = {
  { "new"          , b2BlockAllocator_b2BlockAllocator },
  { "__gc"         , b2BlockAllocator__b2BlockAllocator },
  { "Allocate"     , b2BlockAllocator_Allocate },
  { "Free"         , b2BlockAllocator_Free },
  { "Clear"        , b2BlockAllocator_Clear },
  { "__tostring"   , b2BlockAllocator___tostring },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_b2_BlockAllocator(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.BlockAllocator");
  // <mt>

  // register member methods
  luaL_register(L, NULL, b2BlockAllocator_member_methods);
  // save meta-table in b2
  dub_register(L, "b2", "BlockAllocator", "BlockAllocator");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
