#include <cassert>
#include <cstdlib>
#include <SDL.h>
#include <string>

#include <luawrap/luawrap.h>

static int GetModState() {
    return (int)SDL_GetModState();
}

static bool IsLCTRLDown() {
    return SDLK_LCTRL & (int)SDL_GetModState();
}

static bool IsRCTRLDown() {
    return SDLK_RCTRL & (int)SDL_GetModState();
}

static std::string GetClipboardText() {
    const char* text = SDL_GetClipboardText();
    std::string copy = text;
    free((void*)text);
    return copy;
}

int luaopen_SDL(lua_State *L) {
    LuaValue module = LuaValue::newtable(L);
    module["GetModState"].bind_function(GetModState);
    module["IsLCTRLDown"].bind_function(IsLCTRLDown);
    module["IsRCTRLDown"].bind_function(IsRCTRLDown);
    module["GetClipboardText"].bind_function(GetClipboardText);
    module.push();
    return 1;
}
