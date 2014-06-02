/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2PolygonShape
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"


/** ~b2PolygonShape()
 * 
 */
static int b2PolygonShape__b2PolygonShape(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub_checksdata_d(L, 1, "b2.PolygonShape"));
    if (userdata->gc) {
      b2PolygonShape *self = (b2PolygonShape *)userdata->ptr;
      delete self;
    }
    userdata->gc = false;
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "~b2PolygonShape: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "~b2PolygonShape: Unknown exception");
  }
  return dub_error(L);
}

/** Set attributes (key, value)
 * 
 */
static int b2PolygonShape__set_(lua_State *L) {

  b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata_n(L, 1, "b2.PolygonShape"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub_hash(key, 10);
  switch(key_h) {
    case 8: {
      if (DUB_ASSERT_KEY(key, "m_centroid")) break;
      self->m_centroid = **((b2Vec2 **)dub_checksdata_n(L, 3, "b2.Vec2"));
      return 0;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "m_count")) break;
      self->m_count = luaL_checkint(L, 3);
      return 0;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "m_type")) break;
      self->m_type = (b2Shape::Type)luaL_checkint(L, 3);
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "m_radius")) break;
      self->m_radius = luaL_checknumber(L, 3);
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
static int b2PolygonShape__get_(lua_State *L) {

  b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata_n(L, 1, "b2.PolygonShape", true));
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
  int key_h = dub_hash(key, 10);
  switch(key_h) {
    case 8: {
      if (DUB_ASSERT_KEY(key, "m_centroid")) break;
      dub_pushudata(L, &self->m_centroid, "b2.Vec2", false);
      return 1;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "m_count")) break;
      lua_pushnumber(L, self->m_count);
      return 1;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "m_type")) break;
      lua_pushnumber(L, self->m_type);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "m_radius")) break;
      lua_pushnumber(L, self->m_radius);
      return 1;
    }
  }
  return 0;
}

/** Cast (class_name)
 * 
 */
static int b2PolygonShape__cast_(lua_State *L) {

  b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata_n(L, 1, "b2.PolygonShape"));
  const char *key = luaL_checkstring(L, 2);
  void **retval__ = (void**)lua_newuserdata(L, sizeof(void*));
  int key_h = dub_hash(key, 2);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "b2.Shape")) break;
      *retval__ = static_cast<b2Shape *>(self);
      return 1;
    }
  }
  return 0;
}

/** Read m_vertices(size_t i)
 * 
 */
static int b2PolygonShape_m_vertices(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    int top__ = lua_gettop(L);
    if (top__ >= 3) {
      size_t i = dub_checkint(L, 2);
      b2Vec2 *v = *((b2Vec2 **)dub_checksdata(L, 3, "b2.Vec2"));
      if (!i || i > b2_maxPolygonVertices) return 0;
      self->m_vertices[i-1] = *v;
      return 0;
    } else {
      size_t i = dub_checkint(L, 2);
      if (!i || i > b2_maxPolygonVertices) return 0;
      dub_pushudata(L, new b2Vec2(self->m_vertices[i-1]), "b2.Vec2", true);
      return 1;
    }
  } catch (std::exception &e) {
    lua_pushfstring(L, "m_vertices: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "m_vertices: Unknown exception");
  }
  return dub_error(L);
}

/** Read m_normals(size_t i)
 * 
 */
static int b2PolygonShape_m_normals(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    int top__ = lua_gettop(L);
    if (top__ >= 3) {
      size_t i = dub_checkint(L, 2);
      b2Vec2 *v = *((b2Vec2 **)dub_checksdata(L, 3, "b2.Vec2"));
      if (!i || i > b2_maxPolygonVertices) return 0;
      self->m_normals[i-1] = *v;
      return 0;
    } else {
      size_t i = dub_checkint(L, 2);
      if (!i || i > b2_maxPolygonVertices) return 0;
      dub_pushudata(L, new b2Vec2(self->m_normals[i-1]), "b2.Vec2", true);
      return 1;
    }
  } catch (std::exception &e) {
    lua_pushfstring(L, "m_normals: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "m_normals: Unknown exception");
  }
  return dub_error(L);
}

/** b2PolygonShape::b2PolygonShape()
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:31
 */
static int b2PolygonShape_b2PolygonShape(lua_State *L) {
  try {
    b2PolygonShape *retval__ = new b2PolygonShape();
    dub_pushudata(L, retval__, "b2.PolygonShape", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "b2PolygonShape: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "b2PolygonShape: Unknown exception");
  }
  return dub_error(L);
}

/** b2Shape * b2PolygonShape::Clone(b2BlockAllocator *allocator) const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:34
 */
static int b2PolygonShape_Clone(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    b2BlockAllocator *allocator = *((b2BlockAllocator **)dub_checksdata(L, 2, "b2.BlockAllocator"));
    b2Shape *retval__ = self->Clone(allocator);
    if (!retval__) return 0;
    dub_pushudata(L, retval__, "b2.Shape", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Clone: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Clone: Unknown exception");
  }
  return dub_error(L);
}

/** int32 b2PolygonShape::GetChildCount() const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:37
 */
static int b2PolygonShape_GetChildCount(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    lua_pushnumber(L, self->GetChildCount());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetChildCount: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetChildCount: Unknown exception");
  }
  return dub_error(L);
}

/** void b2PolygonShape::Set(const b2Vec2 *points, int32 count)
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:44
 */
static int b2PolygonShape_Set(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    b2Vec2 *points = *((b2Vec2 **)dub_checksdata(L, 2, "b2.Vec2"));
    int32 count = dub_checkint(L, 3);
    self->Set(points, count);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Set: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Set: Unknown exception");
  }
  return dub_error(L);
}

/** void b2PolygonShape::SetAsBox(float32 hx, float32 hy)
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:49
 */
static int b2PolygonShape_SetAsBox(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    int top__ = lua_gettop(L);
    if (top__ >= 5) {
      float32 hx = dub_checknumber(L, 2);
      float32 hy = dub_checknumber(L, 3);
      b2Vec2 *center = *((b2Vec2 **)dub_checksdata(L, 4, "b2.Vec2"));
      float32 angle = dub_checknumber(L, 5);
      self->SetAsBox(hx, hy, *center, angle);
      return 0;
    } else {
      float32 hx = dub_checknumber(L, 2);
      float32 hy = dub_checknumber(L, 3);
      self->SetAsBox(hx, hy);
      return 0;
    }
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetAsBox: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetAsBox: Unknown exception");
  }
  return dub_error(L);
}

/** bool b2PolygonShape::TestPoint(const b2Transform &transform, const b2Vec2 &p) const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:59
 */
static int b2PolygonShape_TestPoint(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    b2Transform *transform = *((b2Transform **)dub_checksdata(L, 2, "b2.Transform"));
    b2Vec2 *p = *((b2Vec2 **)dub_checksdata(L, 3, "b2.Vec2"));
    lua_pushboolean(L, self->TestPoint(*transform, *p));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "TestPoint: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "TestPoint: Unknown exception");
  }
  return dub_error(L);
}

/** bool b2PolygonShape::RayCast(b2RayCastOutput *output, const b2RayCastInput &input, const b2Transform &transform, int32 childIndex) const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:63
 */
static int b2PolygonShape_RayCast(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    b2RayCastOutput *output = *((b2RayCastOutput **)dub_checksdata(L, 2, "b2.RayCastOutput"));
    b2RayCastInput *input = *((b2RayCastInput **)dub_checksdata(L, 3, "b2.RayCastInput"));
    b2Transform *transform = *((b2Transform **)dub_checksdata(L, 4, "b2.Transform"));
    int32 childIndex = dub_checkint(L, 5);
    lua_pushboolean(L, self->RayCast(output, *input, *transform, childIndex));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "RayCast: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "RayCast: Unknown exception");
  }
  return dub_error(L);
}

/** void b2PolygonShape::ComputeAABB(b2AABB *aabb, const b2Transform &transform, int32 childIndex) const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:66
 */
static int b2PolygonShape_ComputeAABB(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    b2AABB *aabb = *((b2AABB **)dub_checksdata(L, 2, "b2.AABB"));
    b2Transform *transform = *((b2Transform **)dub_checksdata(L, 3, "b2.Transform"));
    int32 childIndex = dub_checkint(L, 4);
    self->ComputeAABB(aabb, *transform, childIndex);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ComputeAABB: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ComputeAABB: Unknown exception");
  }
  return dub_error(L);
}

/** void b2PolygonShape::ComputeMass(b2MassData *massData, float32 density) const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:69
 */
static int b2PolygonShape_ComputeMass(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    b2MassData *massData = *((b2MassData **)dub_checksdata(L, 2, "b2.MassData"));
    float32 density = dub_checknumber(L, 3);
    self->ComputeMass(massData, density);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ComputeMass: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ComputeMass: Unknown exception");
  }
  return dub_error(L);
}

/** int32 b2PolygonShape::GetVertexCount() const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:72
 */
static int b2PolygonShape_GetVertexCount(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    lua_pushnumber(L, self->GetVertexCount());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetVertexCount: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetVertexCount: Unknown exception");
  }
  return dub_error(L);
}

/** const b2Vec2 & b2PolygonShape::GetVertex(int32 index) const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:75
 */
static int b2PolygonShape_GetVertex(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    int32 index = dub_checkint(L, 2);
    dub_pushudata(L, const_cast<b2Vec2*>(&self->GetVertex(index)), "b2.Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetVertex: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetVertex: Unknown exception");
  }
  return dub_error(L);
}

/** bool b2PolygonShape::Validate() const
 * vendor/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h:79
 */
static int b2PolygonShape_Validate(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    lua_pushboolean(L, self->Validate());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Validate: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Validate: Unknown exception");
  }
  return dub_error(L);
}

/** b2Shape::Type b2Shape::GetType() const
 * vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:62
 */
static int b2PolygonShape_GetType(lua_State *L) {
  try {
    b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata(L, 1, "b2.PolygonShape"));
    lua_pushnumber(L, self->GetType());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetType: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetType: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int b2PolygonShape___tostring(lua_State *L) {
  b2PolygonShape *self = *((b2PolygonShape **)dub_checksdata_n(L, 1, "b2.PolygonShape"));
  lua_pushfstring(L, "b2.PolygonShape: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2PolygonShape_member_methods[] = {
  { "__gc"         , b2PolygonShape__b2PolygonShape },
  { "__newindex"   , b2PolygonShape__set_ },
  { "__index"      , b2PolygonShape__get_ },
  { "_cast_"       , b2PolygonShape__cast_ },
  { "m_vertices"   , b2PolygonShape_m_vertices },
  { "m_normals"    , b2PolygonShape_m_normals },
  { "new"          , b2PolygonShape_b2PolygonShape },
  { "Clone"        , b2PolygonShape_Clone },
  { "GetChildCount", b2PolygonShape_GetChildCount },
  { "Set"          , b2PolygonShape_Set   },
  { "SetAsBox"     , b2PolygonShape_SetAsBox },
  { "TestPoint"    , b2PolygonShape_TestPoint },
  { "RayCast"      , b2PolygonShape_RayCast },
  { "ComputeAABB"  , b2PolygonShape_ComputeAABB },
  { "ComputeMass"  , b2PolygonShape_ComputeMass },
  { "GetVertexCount", b2PolygonShape_GetVertexCount },
  { "GetVertex"    , b2PolygonShape_GetVertex },
  { "Validate"     , b2PolygonShape_Validate },
  { "GetType"      , b2PolygonShape_GetType },
  { "__tostring"   , b2PolygonShape___tostring },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_b2_PolygonShape(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.PolygonShape");
  // <mt>

  // register member methods
  luaL_register(L, NULL, b2PolygonShape_member_methods);
  // save meta-table in b2
  dub_register(L, "b2", "PolygonShape", "PolygonShape");
  // <mt>
  lua_pop(L, 1);
  return 0;
}