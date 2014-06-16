/*
 * GameTiles.cpp:
 *   Handles drawing of the tiles of the game, drawing of the fog-of-war,
 *   storage of tile information for a level. Stores if a tile has already
 *   been seen.
 */

#include <cstring>

#include <lcommon/SerializeBuffer.h>
#include <lcommon/math_util.h>

#include "bresenham.h"

#include "GameTiles.h"

const int TILE_SIZE = 32;

GameTiles::~GameTiles() {
}

bool GameTiles::line_test(const Pos& from_xy, const Pos& to_xy, Pos* hitloc) {
	Size size = map->size();

	TCOD_bresenham_data_t line_data;
	Pos tile_from = from_xy.divided(TILE_SIZE), tile_to = to_xy.divided(TILE_SIZE);
	TCOD_line_init_mt(tile_from.x, tile_from.y, tile_to.x, tile_to.y, &line_data);

	// Iterate for each (x,y) in the line
	int x,y;
	while (!TCOD_line_step_mt(&x, &y, &line_data)) {
		int idx = y * size.w + x;

		bool solidity_match = map->raw_get(idx).matches_flags(ldungeon_gen::FLAG_SOLID);

		if (solidity_match) {
			BBox tilebox(Pos(x * TILE_SIZE, y * TILE_SIZE), Size(TILE_SIZE, TILE_SIZE));
			if (rectangle_line_test(tilebox, from_xy, to_xy)) {
				if (hitloc)
					*hitloc = Pos(x, y);
				return true;
			}
		}

	}
	return false;
}

bool GameTiles::radius_test(const Pos& xy, int rad, Pos* hitloc) {
	int distsqr = (TILE_SIZE / 2 + rad), radsqr = rad * rad;
	distsqr *= distsqr; //sqr it

	Size size = map->size();

	int x = xy.x, y = xy.y;

	int mingrid_x = (x - rad) / TILE_SIZE, mingrid_y = (y - rad) / TILE_SIZE;
	int maxgrid_x = (x + rad) / TILE_SIZE, maxgrid_y = (y + rad) / TILE_SIZE;
	int minx = squish(mingrid_x, 0, size.w), miny = squish(mingrid_y, 0, size.h);
	int maxx = squish(maxgrid_x, 0, size.w), maxy = squish(maxgrid_y, 0, size.h);

	for (int yy = miny; yy <= maxy; yy++) {
		for (int xx = minx; xx <= maxx; xx++) {
			int idx = yy * size.w + xx;

			bool solidity_match = map->raw_get(idx).matches_flags(ldungeon_gen::FLAG_SOLID);

			if (solidity_match) {
				BBox tilebox(Pos(xx * TILE_SIZE, yy * TILE_SIZE), Size(TILE_SIZE, TILE_SIZE));
				Pos dist = tilebox.center() - xy;
				double ddist = dist.x * dist.x + dist.y * dist.y;
				if (ddist < distsqr || circle_rectangle_test(xy, rad, tilebox)) {
					if (hitloc)
						*hitloc = Pos(xx, yy);
					return true;
				}
			}
		}
	}
	return false;
}
