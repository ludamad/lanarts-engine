/*
 * fov.h:
 *  Represents a field of view
 */

#ifndef FOV_H_
#define FOV_H_

#include <lcommon/geometry.h>
#include <ldungeon_gen/Map.h>

#include "impl/permissive-fov-cpp.h"

#include "../BoolGridRef.h"

class fov {
public:
	fov(const ldungeon_gen::MapPtr& map, int radius);
	~fov();
	void calculate(int ptx, int pty);
	bool within_fov(int grid_x, int grid_y);
	bool within_fov(const BBox& bbox);
	void matches(int sqr_x, int sqr_y, char* sub_sqrs);
	void update_seen_map(const BoolGridRef& seen);
	BBox tiles_covered() {
		BBox bbox(ptx - radius, pty - radius, ptx + radius, pty + radius);
		return bbox.resized_within(BBox(Pos(), map->size()));
	}

	fov* clone() const;
private:
	bool raw_within_fov(int grid_x, int grid_y);
	bool has_been_calculated;
	char* sight_mask;
	ldungeon_gen::MapPtr map;
	int radius, diameter;
	int sx, sy;
	int ptx, pty;
	permissive::maskT m;
public:
	//do-not-use
	int isBlocked(short destX, short destY);
	void visit(short destX, short destY);
};
const int VISION_SUBSQRS = 1;
#endif /* FOV_H_ */
