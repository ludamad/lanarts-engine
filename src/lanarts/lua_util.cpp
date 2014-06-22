#include <ldungeon_gen/Map.h>
#include <luawrap/luawrap.h>

#include "BoolGridRef.h"

using namespace ldungeon_gen;

static int extract_solidity_and_seethrough_maps(lua_State* L) {
    MapPtr map = luawrap::get<MapPtr>(L, 1);
    Size size(map->size());
    BoolGridRef solidity(new Grid<bool>(size));
    BoolGridRef seethrough(new Grid<bool>(size));
    for (int y = 0; y < size.h; y++) {
        for (int x = 0; x < size.w; x++) {
            Square& sqr = (*map)[Pos(x,y)];
            (*solidity)[Pos(x,y)] = sqr.matches_flags(FLAG_SOLID);
            (*seethrough)[Pos(x,y)] = sqr.matches_flags(FLAG_SEETHROUGH);
        }
    }

    luawrap::push(L, solidity);
    luawrap::push(L, seethrough);
    return 2;
}

int luaopen_core_util(lua_State *L) {
    LuaValue module = LuaValue::newtable(L);
    module["extract_solidity_and_seethrough_maps"].bind_function(extract_solidity_and_seethrough_maps);
    module.push();
    return 1;
}
