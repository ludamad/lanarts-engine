/**
 * GameInstSet.h:
 *  Collection class that keeps track of game objects and assigns instance-id's.
 *  Releases reference to destroyed objects at end of step.
 *  Use instance IDs to refer to objects that may or may not still be alive.
 *  Use GameInstRef to objects that -must- be kept undeleted.
 *  The object may still be removed from the game world.
 */

#ifndef GAMEINSTSET_H_
#define GAMEINSTSET_H_

#include <cstring>
#include <cstdlib>
#include <vector>

#include <map>

#include <lcommon/geometry.h>

class SerializeBuffer;

typedef int obj_id;

// This object is defined solely for the purposes of
// reading from & modifying in a GameInstSet.
struct GameInst {
    // The different fill states:
    enum {
        EMPTY = 0, // Necessary, see memset below
        FILLED,
        TOMBSTONE
    };
    obj_id id;
    int depth;
    double x, y;
    double last_x, last_y;
    double radius, target_radius;
    bool solid;
    // Solely for GameInstSet inner workings:
    char fill_state;
    GameInst() {
        // TODO?: Technically redundant with memset below
        id = 0;
        depth = 0;
        x = y = 0;
        last_x = last_y = 0;
        radius = target_radius = 0;
        solid = false;
        fill_state = EMPTY;
    }
};

class GameInstSet {
public:
	enum {
	    //cell is REGION_SIZE by REGION_SIZE
		DEFAULT_CAPACITY = 64, REGION_SIZE = 96
	};
	GameInstSet(int w, int h, int capacity = DEFAULT_CAPACITY);

	//The main part of the API:
	/*Add an instance, optionally specifying its id*/
	obj_id add_instance(double x, double y,  double radius, double target_radius, bool solid, obj_id id = 0);
	void remove_instance(obj_id id);
	void update();

	//Returns NULL if no unit found
	GameInst* get_instance(obj_id id) const;

	int object_radius_test(GameInst* obj, GameInst* objs = NULL,
	        int obj_cap = 0, int x = -1, int y = -1, int radius = -1);

	obj_id object_radius_test(obj_id id, int x = -1, int y = -1, int radius = -1) {
	    GameInst result[1];
	    int amount = object_radius_test(get_instance(id), result, 1, x, y, radius);
	    if (amount == 0) {
	        return 0;
	    }
	    return result[0].id;
	}
//	int object_square_test(GameInst** objs = NULL, int obj_cap =
//			0, const Pos& pos, col_filterf f = NULL);

	//Used to synchronize game-id's across network play where objects are created on some systems but not all
	void skip_next_id() {
		next_id++;
	}
	//Allocate all instances to one vector, traversed according to depth order
	std::vector<GameInst> to_vector() const;
	size_t size() const {
		return unit_amnt;
	}
	//Return a semi-unique hash of the instances contained in the structure
	unsigned int hash() const;
	bool check_copy_integrity(const GameInstSet& inst_set) const;

	void copy_to(GameInstSet& inst_set) const;

	std::vector<GameInst> object_rectangle_test(BBox rect, GameInst* tester = NULL);
	void clear();

	void serialize(SerializeBuffer& serializer);
	void deserialize(SerializeBuffer& serializer);
private:

	//Internal Structures:
	//Encapsulates instances and the data needed to perform collision lookups by area
	struct InstanceState {
		GameInst inst;
		//These pointers are invalidated upon hashmap reallocation
		InstanceState* next_in_grid, *prev_in_grid;
		InstanceState* next_same_depth, *prev_same_depth;
		InstanceState() {
			memset(this, 0, sizeof(InstanceState));
		}
		//Used in settools.h
		void operator=(const GameInst& inst) {
			this->inst = inst;
			next_in_grid = NULL;
			prev_in_grid = NULL;
			next_same_depth = NULL;
			prev_same_depth = NULL;
		}
	};

	//List of instances with the same rendering depth
	struct InstanceLinkedList {
		InstanceState* start_of_list, *end_of_list;
		InstanceLinkedList() :
				start_of_list(NULL), end_of_list(NULL) {
		}
	};

	typedef std::map<int, InstanceLinkedList> DepthMap;

	/* Internal Data */

	// Map to the first object of a certain depth
	DepthMap depthlist_map;

	// Hashset portion
	int next_id, unit_amnt, unit_capacity;
	std::vector<InstanceState> unit_set;

	// Grid portion
	int grid_w, grid_h;
	//Holds units IDs, 0 if empty
	std::vector<InstanceLinkedList> unit_grid;

	// Internal structure upkeep functions
	void __remove_instance(InstanceState* state);
	void __update_collision_position(InstanceState* state, const Pos& p1, const Pos& p2);
	void reallocate_internal_data();
	void update_statepointer_for_reallocate_(InstanceState** stateptr);
	void update_depthlist_for_reallocate_(InstanceLinkedList& list);

	void update_instance_for_step(InstanceState* state, GameInst& inst);

	void add_to_depthlist(InstanceState* state, InstanceLinkedList& list);
	void remove_from_depthlist(InstanceState* inst, InstanceLinkedList& list);

	void add_to_collisionlist(InstanceState* inst, InstanceLinkedList& list);
	void remove_from_collisionlist(InstanceState* inst,
			InstanceLinkedList& list);

	/* Integrity check */
	bool within_bounds_check(const Pos& c);

	//Used to allow access to internal data/functions for our hash set implementation utility class
	friend class GameInstSetFunctions;
};

#endif /* GAMEINSTSET_H_ */
