#include <cassert>
#include <SDL.h>

#include <luawrap/luawrap.h>

static int GetModState() {
    return (int)SDL_GetModState();
}

int luaopen_SDL(lua_State *L) {
    LuaValue module = LuaValue::newtable(L);
    module["GetModState"].bind_function(GetModState);
    module.push();
    return 1;
}
