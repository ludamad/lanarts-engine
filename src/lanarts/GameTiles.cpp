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

GameTiles::GameTiles(const BoolGridRef& solidity, const BoolGridRef& seen, const BoolGridRef& seethrough) :
    _solidity(solidity),
    _seen(seen),
    _seethrough(seethrough) {
    LANARTS_ASSERT(solidity->size() == seen->size() && seen->size() == seethrough->size());
}

GameTiles::~GameTiles() {
}

bool GameTiles::was_seen(const Pos& xy) {
	return (*_seen)[xy];
}

void GameTiles::set_seethrough(const Pos& xy, bool seethrough) {
	(*_seethrough)[xy] = seethrough;
}

void GameTiles::set_solid(const Pos& xy, bool solid) {
	(*_solidity)[xy] = solid;
}

bool GameTiles::is_solid(const Pos& xy) {
	return (*_solidity)[xy];
}

bool GameTiles::is_seethrough(const Pos& xy) {
	return (*_seethrough)[xy];
}

void GameTiles::clear() {
	_solidity->fill(false);
	_seen->fill(false);
	_seethrough->fill(false);
}

void GameTiles::mark_all_seen() {
	_seen->fill(true);
}

void GameTiles::copy_to(GameTiles & t) const {
	t._solidity = _solidity;
}

void GameTiles::serialize(SerializeBuffer& serializer) {
	serializer.write(size());
	serializer.write_container(_solidity->_internal_vector());
	serializer.write_container(_seen->_internal_vector());
	serializer.write_container(_seethrough->_internal_vector());
}

bool GameTiles::line_test(const Pos& from_xy, const Pos& to_xy, bool issolid, int ttype,
		Pos* hitloc) {
	Size size = this->size();

	TCOD_bresenham_data_t line_data;
	Pos tile_from = from_xy.divided(TILE_SIZE), tile_to = to_xy.divided(TILE_SIZE);
	TCOD_line_init_mt(tile_from.x, tile_from.y, tile_to.x, tile_to.y, &line_data);

	// Iterate for each (x,y) in the line
	int x,y;
	while (!TCOD_line_step_mt(&x, &y, &line_data)) {
		int idx = y * size.w + x;

		bool solidity_match = _solidity->raw_get(idx) == issolid;

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

bool GameTiles::radius_test(const Pos& xy, int rad, bool issolid, int ttype,
		Pos* hitloc) {
	int distsqr = (TILE_SIZE / 2 + rad), radsqr = rad * rad;
	distsqr *= distsqr; //sqr it

	Size size = this->size();

	int x = xy.x, y = xy.y;

	int mingrid_x = (x - rad) / TILE_SIZE, mingrid_y = (y - rad) / TILE_SIZE;
	int maxgrid_x = (x + rad) / TILE_SIZE, maxgrid_y = (y + rad) / TILE_SIZE;
	int minx = squish(mingrid_x, 0, size.w), miny = squish(mingrid_y, 0, size.h);
	int maxx = squish(maxgrid_x, 0, size.w), maxy = squish(maxgrid_y, 0, size.h);

	for (int yy = miny; yy <= maxy; yy++) {
		for (int xx = minx; xx <= maxx; xx++) {
			int idx = yy * size.w + xx;

			bool solidity_match = _solidity->raw_get(idx) == issolid;

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

void GameTiles::deserialize(SerializeBuffer& serializer) {
	Size newsize;
	serializer.read(newsize);

	_solidity->resize(newsize);
	_seen->resize(newsize);
	_seethrough->resize(newsize);

	serializer.read_container(_solidity->_internal_vector());
	serializer.read_container(_seen->_internal_vector());
	serializer.read_container(_seethrough->_internal_vector());
}

BoolGridRef GameTiles::solidity_map() const {
	return _solidity;
}


BoolGridRef GameTiles::previously_seen_map() const {
	return _seen;
}


BoolGridRef GameTiles::seethrough_map() const {
	return _seethrough;
}
