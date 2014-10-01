/**
 * GameInstSet.cpp:
 *  Collection class that keeps track of game objects and assigns instance-id's.
 *  Releases reference to destroyed objects at end of step.
 *  Use instance IDs to refer to objects that may or may not still be alive.
 *  Use GameInstRef to objects that -must- be kept undeleted.
 *  The object may still be removed from the game world.
 */

#include <cstring>
#include <cstdio>
#include <typeinfo>

#include <lcommon/SerializeBuffer.h>
#include <lcommon/math_util.h>
#include <lcommon/perf_timer.h>

#include "GameInstSet.h"
#include "hashset_util.h"
#include "common.h"

static bool valid_inst(const GameInst& inst) {
    return inst.fill_state == GameInst::FILLED;
}

GameInstSet::GameInstSet(int w, int h, int capacity) {
    grid_w = w / REGION_SIZE + 1, grid_h = h / REGION_SIZE + 1;
    next_id = 1;
    unit_amnt = 0;
    unit_capacity = capacity;
    unit_set.resize(unit_capacity);
    unit_grid.resize(grid_w * grid_h);
}
struct GameInstSetFunctions { //Helper class
    typedef GameInstSet::InstanceState V;
    static bool isNull(const V& v) {
        return v.inst.fill_state == GameInst::EMPTY;
    }
    static bool isRemoved(const V& v) {
        return v.inst.fill_state == GameInst::TOMBSTONE;
    }
    static void remove(V& v) {
        v.inst.fill_state = GameInst::TOMBSTONE;
    }
    static bool equal(const V& v1, int obj_id) {
        return valid_inst(v1.inst) && v1.inst.id == obj_id;
    }
    static bool equal(const V& v1, GameInst& inst) {
        return v1.inst.id == inst.id;
    }
    static bool equal(const V& v1, const V& v2) {
        return v1.inst.id == v2.inst.id;
    }
    static size_t hash(const V& v) {
        return (size_t) v.inst.id;
    }

    static size_t hash(const GameInst& inst) {
        return (size_t) inst.id;
    }
    static size_t hash(obj_id id) {
        return (size_t) id;
    }
};

void GameInstSet::update_statepointer_for_reallocate_(
        InstanceState** stateptr) {
    if (*stateptr) {
        InstanceState* prev = *stateptr;
        *stateptr = tset_find<GameInstSetFunctions>((*stateptr)->inst.id,
                &unit_set[0], unit_capacity);
        LANARTS_ASSERT(*stateptr != NULL);
    }
}

void GameInstSet::update_instancelist_for_reallocate_(
        InstanceLinkedList& list) {
    update_statepointer_for_reallocate_(&list.start_of_list);
    update_statepointer_for_reallocate_(&list.end_of_list);
}

void GameInstSet::reallocate_internal_data() {
    unit_capacity *= 2;
    std::vector<InstanceState> new_set(unit_capacity);

    tset_add_all<GameInstSetFunctions>(&unit_set[0], unit_set.size(),
            &new_set[0], new_set.size());
    unit_set.swap(new_set);

    //Fix pointers for grid
    for (int i = 0; i < unit_capacity; i++) {
        if (unit_set[i].inst.fill_state == GameInst::FILLED) {
            update_statepointer_for_reallocate_(&unit_set[i].prev_in_grid);
            update_statepointer_for_reallocate_(&unit_set[i].next_in_grid);
        }
    }

    for (int i = 0; i < grid_w * grid_h; i++) {
        update_instancelist_for_reallocate_(unit_grid[i]);
    }
}
static int get_xyind(const PosF& c, int grid_w) {
    return (lrint(c.y) / GameInstSet::REGION_SIZE) * grid_w
            + lrint(c.x) / GameInstSet::REGION_SIZE;
}

void GameInstSet::__remove_instance(InstanceState* state) {
    GameInst& inst = state->inst;
    InstanceLinkedList& list = unit_grid[get_xyind(
            Pos(inst.last_x, inst.last_y), grid_w)];

    remove_from_collisionlist(state, list);

    this->unit_amnt--;
    inst.fill_state = GameInst::TOMBSTONE;
}
void GameInstSet::remove_instance(obj_id id) {
    InstanceState* state = tset_find<GameInstSetFunctions>(id, &unit_set[0],
            unit_capacity);
    __remove_instance(state);
}

void GameInstSet::serialize(SerializeBuffer& serializer) {
//	serializer.write_int(grid_w);
//	serializer.write_int(grid_h);
//
//	serializer.write_int(size());
//	serializer.write_int(next_id);
//	DepthMap::const_iterator it = depthlist_map.end();
//	std::vector<GameInst&> instances;
//	for (int ind = 0; it != depthlist_map.begin();) {
//		--it;
//		InstanceState* state = it->second.start_of_list;
//		while (state) {
//			serializer.write(state->inst);
//			state = state->next_same_depth;
//		}
//	}
}

void GameInstSet::deserialize(SerializeBuffer& serializer) {
//	serializer.read_int(grid_w);
//	serializer.read_int(grid_h);
//
//	//Resize and clear
//	unit_grid.resize(grid_w * grid_h);
//	clear();
//
//	int amnt;
//	serializer.read_int(amnt);
//	serializer.read_int(next_id);
//
//	std::vector<GameInst&> instances;
//	for (int i = 0; i < amnt; i++) {
//		InstType type;
//		int id;
//		serializer.read_int(type);
//		serializer.read_int(id);
//		GameInst& inst = get_instance(id);
//		bool has_inst = inst != NULL;
//		if (!has_inst) {
//			inst = from_inst_type(type);
//			inst.deserialize(gs, serializer);
//			inst.last_x = inst.x;
//			inst.last_y = inst.y;
//			inst.id = id;
//			add_instance(inst, inst.id);
//			instances.push_back(inst);
//		} else {
//			safe_deserialize(inst, gs, serializer);
//		}
////		if (gs->game_settings().network_debug_mode) {
//		bool seq = serializer_equals_read(serializer, inst.integrity_hash());
//		if (!seq) {
//			lanarts_system_quit();
//			abort();
//		}
////		}
//	}
}

bool GameInstSet::within_bounds_check(const PosF& c) {
    return !(c.x < 0 || c.y < 0 || c.x >= grid_w * REGION_SIZE
            || c.y >= grid_h * REGION_SIZE);
}

obj_id GameInstSet::add_instance(double x, double y, double radius,
        double target_radius, bool solid, obj_id id) {
    if (tset_should_resize(unit_amnt, unit_capacity))
        this->reallocate_internal_data();

    PosF c(x, y);

    //Will be set to the current state object in 'add'
    InstanceState* state = &unit_set[0];

    GameInst inst;
    inst.fill_state = GameInst::FILLED;
    inst.x = x, inst.y = y;
    inst.last_x = x, inst.last_y = y;
    inst.radius = radius, inst.target_radius = target_radius;
    inst.solid = solid;
    inst.id = id != 0 ? id : (next_id++);

    //Add an object with the assumption that this object does not currently exist (_noequal)
    if (tset_add_noequal<GameInstSetFunctions>(inst, state, unit_capacity)) {
        unit_amnt++;
    }

    if (true || inst.solid) {
        LANARTS_ASSERT(within_bounds_check(c));
        InstanceLinkedList& unit_list = unit_grid[get_xyind(c, grid_w)];
        add_to_collisionlist(state, unit_list);
    }

    return inst.id;
}

void GameInstSet::update() {
    for (int i = 0; i < unit_capacity; i++) {
        GameInst& inst = unit_set[i].inst;
        if (valid_inst(inst)) {
            update_instance_for_step(&unit_set[i], inst);
        }
    }
}

GameInst* GameInstSet::get_instance(obj_id id) const {
    InstanceState* is = tset_find<GameInstSetFunctions>(id, &unit_set[0],
            unit_capacity);
    if (is) {
        return &is->inst;
    }
    return NULL;
}

std::vector<GameInst> GameInstSet::to_vector() const {
    std::vector<GameInst> ret(size());

    int next_id = 0;
    for (int i = 0; i < unit_set.size(); i++) {
        const GameInst& gi = unit_set[i].inst;
        if (gi.fill_state == GameInst::FILLED) {
            ret[next_id++] = gi;
        }
    }
    return ret;
}

unsigned int GameInstSet::hash() const {
    unsigned int hash = 0xbabdabe;
    std::vector<GameInst> as_vector = to_vector();
    for (int i = 0; i < as_vector.size(); i++) {
        GameInst& inst = as_vector[i];
        hash ^= int(inst.x * 31337);
        hash ^= int(inst.y * 1537);
        hash ^= hash * 31337; //Ad hoc hashing yay
    }
    return hash;
}

void GameInstSet::adjust_instance_state_ptr(GameInstSet::InstanceState** ptr,
        GameInstSet& to) {
    GameInstSet::InstanceState* to_start = &to.unit_set[0];
    GameInstSet::InstanceState* from_start = &unit_set[0];
    *ptr = (*ptr - from_start) + to_start;
}

void GameInstSet::copy_to(GameInstSet& inst_set) {
    inst_set.next_id = next_id;
    inst_set.unit_amnt = unit_amnt;
    inst_set.unit_capacity = unit_capacity;

    inst_set.unit_set = unit_set;
    inst_set.unit_grid = unit_grid;

    for (int i = 0; i < unit_set.size(); i++) {
        InstanceState& state = inst_set.unit_set[i];
        adjust_instance_state_ptr(&state.next_in_grid, inst_set);
        adjust_instance_state_ptr(&state.prev_in_grid, inst_set);
    }

    for (int i = 0; i < inst_set.unit_grid.size(); i++) {
        adjust_instance_state_ptr(&inst_set.unit_grid[i].start_of_list,
                inst_set);
        adjust_instance_state_ptr(&inst_set.unit_grid[i].end_of_list, inst_set);
    }
}

int GameInstSet::object_radius_test(GameInst* obj, GameInst* objs, int obj_cap,
        double x, double y, double radius) {
    double rad = radius == -1 ? obj->target_radius : radius;
    x = x == -1 ? obj->x : x;
    y = y == -1 ? obj->y : y;

    // Find the region we are situated in:
    int cx = lrint(x) / REGION_SIZE, cy = lrint(y) / REGION_SIZE;
    int minx = squish(cx - 1, 0, grid_w), miny = squish(cy - 1, 0, grid_h);
    int maxx = squish(cx + 1, 0, grid_w-1), maxy = squish(cy + 1, 0, grid_h-1);

    int obj_n = 0;

    for (int yy = miny; yy <= maxy; yy++) {
        int index = yy * grid_w + minx;
        for (int xx = minx; xx <= maxx; xx++) {
            InstanceLinkedList& unit_list = unit_grid[index++];
            InstanceState* ptr = unit_list.start_of_list;
            InstanceState* eptr = unit_list.end_of_list;
            while (ptr != NULL) {
                GameInst& inst = ptr->inst;
                if (obj == NULL || obj->id != inst.id) {
                    double radsqr = (inst.target_radius + rad)
                            * (inst.target_radius + rad);
                    double dx = inst.x - x, dy = inst.y - y;
                    double dsqr = dx * dx + dy * dy;
                    //want to test sqrt(dsqr) < orad+rad
                    //therefore we test dsqr < (orad+rad)*(orad+rad)
                    if (dsqr < radsqr && inst.solid) {
                        if (obj_cap == 0)
                            return 1;
                        objs[obj_n] = inst;
                        obj_n++;
                        if (obj_n >= obj_cap)
                            return obj_n;
                    }
                }
                if (ptr == eptr) {
                    LANARTS_ASSERT(ptr->next_in_grid == NULL);
                    break;
                }
                ptr = ptr->next_in_grid;
            }
        }
    }
    return obj_n;
}

std::vector<GameInst> GameInstSet::object_rectangle_test(BBox rect,
        GameInst* tester) {
    int mingrid_x = rect.x1 / REGION_SIZE, mingrid_y = rect.y1 / REGION_SIZE;
    int maxgrid_x = rect.x2 / REGION_SIZE, maxgrid_y = rect.y2 / REGION_SIZE;
    int minx = squish(mingrid_x, 0, grid_w), miny = squish(mingrid_y, 0,
            grid_h);
    int maxx = squish(maxgrid_x, 0, grid_w), maxy = squish(maxgrid_y, 0,
            grid_h);

    std::vector<GameInst> instances;
    for (int yy = miny; yy <= maxy; yy++) {
        int index = yy * grid_w + minx;
        for (int xx = minx; xx <= maxx; xx++) {
            InstanceLinkedList& unit_list = unit_grid[index++];
            InstanceState* ptr = unit_list.start_of_list;
            if (!ptr)
                continue;

            while (ptr) {
                GameInst& inst = ptr->inst;
                if (tester == NULL || tester->id != inst.id) {
                    if (circle_rectangle_test(Pos(inst.x, inst.y),
                            inst.target_radius, rect)) {
                        instances.push_back(inst);
                    }
                }
                ptr = ptr->next_in_grid;
            }
        }
    }
    return instances;
}

void GameInstSet::clear() {
    next_id = 1;
    unit_amnt = 0;
    memset(&unit_set[0], 0, unit_capacity * sizeof(InstanceState));
    memset(&unit_grid[0], 0, grid_w * grid_h * sizeof(InstanceLinkedList));
}

//TODO: Make collisionlist entry positions deterministic -or- make collision functions always return the same object
//this will be important when copying over state updates in client side prediction
void GameInstSet::__update_collision_position(InstanceState* state,
        const PosF& p1, const PosF& p2) {
    GameInst& inst = state->inst;

    int old_bucket = get_xyind(p1, grid_w), new_bucket = get_xyind(p2, grid_w);
    if (old_bucket != new_bucket) {
        //remove from previous unit grid lookup
        remove_from_collisionlist(state, unit_grid[old_bucket]);
        //add to next unit lookup
        add_to_collisionlist(state, unit_grid[new_bucket]);
    }
}

void GameInstSet::update_instance_for_step(InstanceState* state,
        GameInst& inst) {
    perf_timer_begin(FUNCNAME);
    if (true || inst.solid) {
        Pos last_pos(inst.last_x, inst.last_y), new_pos(inst.x, inst.y);
        LANARTS_ASSERT(within_bounds_check(last_pos));
        LANARTS_ASSERT(within_bounds_check(new_pos));
        __update_collision_position(state, last_pos, new_pos);
    }
    inst.last_x = inst.x, inst.last_y = inst.y;
}

void GameInstSet::add_to_collisionlist(InstanceState* inst,
        InstanceLinkedList& list) {
//	LANARTS_ASSERT(inst.inst.solid);
    inst->next_in_grid = NULL;
    if (list.start_of_list == NULL) {
        inst->prev_in_grid = NULL;
        list.start_of_list = inst;
        list.end_of_list = inst;

    } else {
        inst->prev_in_grid = list.end_of_list;
        list.end_of_list->next_in_grid = inst;
        list.end_of_list = inst;
    }
}

bool GameInstSet::check_copy_integrity(const GameInstSet & inst_set) const {
//	std::vector<GameInst&> v1 = this->to_vector(), v2 = inst_set.to_vector();
//	int size = v1.size();
//	if (next_id != inst_set.next_id)
//		return false;
//	if (size != v2.size())
//		return false;
//
//	for (int i = 0; i < size; i++) {
//		GameInst& i1 = v1[i], *i2 = v2[i];
//		if (i1->id != i2->id)
//			return false;
//		if (i1->last_x != i2->last_x)
//			return false;
//
//		if (i1->last_y != i2->last_y)
//			return false;
//
//		if (i1->x != i2->x)
//			return false;
//
//		if (i1->y != i2->y)
//			return false;
//	}
    return true;
}

void GameInstSet::remove_from_collisionlist(InstanceState* inst,
        InstanceLinkedList& list) {
    InstanceState* next = inst->next_in_grid;
    InstanceState* prev = inst->prev_in_grid;
    if (prev == NULL)
        list.start_of_list = next;
    else
        prev->next_in_grid = next;
    if (next == NULL)
        list.end_of_list = prev;
    else
        next->prev_in_grid = prev;
}
