/*
 * lua_ldraw.h:
 *  Bindings for the ldraw library in lua.
 */

#ifndef LDRAW_LUA_LDRAW_H_
#define LDRAW_LUA_LDRAW_H_

struct lua_State;
class LuaValue;

int luaopen_ldraw(lua_State* L);

#endif /* LDRAW_LUA_LDRAW_H_ */
