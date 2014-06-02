/*
 * map_check.h:
 *  Various algorithms for querying a map.
 */

#include <cstdio>
#include <cstdlib>

#include "map_check.h"
#include "bsp.hpp"

namespace ldungeon_gen {

	bool rectangle_matches(Map& map, const BBox& bbox, Selector selector) {
		return rectangle_matches(map, bbox, selector, 0, Selector());
	}

	bool rectangle_matches(Map& map, const BBox& bbox, Selector fill_selector,
			int perimeter, Selector perimeter_selector) {
		const BBox map_bounds(Pos(0, 0), map.size());
		BBox perm_bbox = bbox.grow(perimeter).resized_within(map_bounds);

		int rowstart = perm_bbox.y1 * map.width();
		for (int y = perm_bbox.y1; y < perm_bbox.y2; y++) {

			int idx = rowstart + perm_bbox.x1;
			for (int x = perm_bbox.x1; x < perm_bbox.x2; x++) {
				if (perimeter == 0 || bbox.contains(x, y)) {
					/* Inside the box */
					if (!map.raw_get(idx).matches(fill_selector)) {
						return false;
					}
				} else {
					/* On the perimeter*/
					if (!map.raw_get(idx).matches(perimeter_selector)) {
						return false;
					}
				}
				idx++;
			}
			rowstart += map.width();
		}

		return true;
	}
	AreaQueryBase::~AreaQueryBase() {

	}

	RectangleQuery::RectangleQuery(Selector fill_selector) :
			fill_selector(fill_selector), perimeter(0) {
	}

	RectangleQuery::RectangleQuery(Selector fill_selector, int perimeter,
			Selector perimeter_selector) :
			fill_selector(fill_selector), perimeter(perimeter), perimeter_selector(
					perimeter_selector) {
	}

	bool RectangleQuery::matches(MapPtr map, group_t parent_group_id,
			const BBox& rect) {
		return rectangle_matches(*map, rect, fill_selector, perimeter, perimeter_selector);
	}

	bool find_random_square(MTwist& randomizer, MapPtr map, const BBox& bbox,
			Selector selector, Pos& xy, int max_attempts) {
		for (int i = 0; i < max_attempts; i++) {
			int w = bbox.width(), h = bbox.height();
			int x = bbox.x1 + randomizer.rand(w), y = bbox.y1 + randomizer.rand(h);
			if ((*map)[Pos(x,y)].matches(selector)) {
				xy = Pos(x,y);
				return true;
			}
		}
		return false;
	}
}
