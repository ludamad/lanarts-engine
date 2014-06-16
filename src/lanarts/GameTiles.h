/*
 * GameTiles.h:
 *   Handles drawing of the tiles of the game, drawing of the fog-of-war,
 *   storage of tile information for a level. Stores if a tile has already
 *   been seen.
 */

#ifndef GAMETILES_H_
#define GAMETILES_H_

#include <cstring>
#include <vector>

#include <lcommon/Grid.h>

#include "common.h"

#include <ldungeon_gen/Map.h>
#include "BoolGridRef.h"

struct Pos;

// TODO: This shouldn't be a class anymore

class GameTiles {
public:
	GameTiles(const ldungeon_gen::MapPtr& map) : map(map) {
	}
	~GameTiles();

	bool radius_test(const Pos& xy, int rad, Pos* hitloc = NULL);
	bool line_test(const Pos& from_xy, const Pos& to_xy, Pos* hitloc = NULL);

private:

	ldungeon_gen::MapPtr map;
};

#endif /* GAMETILES_H_ */
