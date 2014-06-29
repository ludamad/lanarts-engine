/*
 * lua_serialize_buffer.cpp:
 *  Implements wrapping for 'SerializeBuffer' in lua.
 */

#include <luawrap/luawrap.h>
#include <luawrap/macros.h>

#include "luaserialize.h"
#include "SerializeBuffer.h"

static int sb_write_object(lua_State* L) {
    int n_args = lua_gettop(L);
    if (n_args != 2) {
        return luaL_error(L, "Two arguments expected, got %d!", n_args);
    }
    luaserialize_encode(L, luawrap::get<SerializeBuffer&>(L, 1), 2);
    return 0;
}

static int sb_read_object(lua_State* L) {
    int n_args = lua_gettop(L);
    if (n_args != 1) {
        return luaL_error(L, "One argument expected, got %d!", n_args);
    }
    luaserialize_decode(L, luawrap::get<SerializeBuffer&>(L, 1));
    return 1;
}

static int sb_tostring(lua_State* L) {
    SerializeBuffer* sb = luawrap::get<SerializeBuffer*>(L, 1);
    lua_pushlstring(L, sb->data(), sb->size());
    return 1;
}

LuaValue lua_serializebuffermetatable(lua_State* L) {
	LUAWRAP_SET_TYPE(SerializeBuffer&);

	LuaValue meta = luameta_new(L, "SerializeBuffer");
	LuaValue methods = luameta_constants(meta);
	LuaValue getters = luameta_getters(meta);

	methods["write"].bind_function(sb_write_object);
    methods["read"].bind_function(sb_read_object);
    methods["tostring"].bind_function(sb_tostring);

    LUAWRAP_METHOD(methods, clear, OBJ.clear());
    LUAWRAP_METHOD(methods, write_byte, OBJ.write_byte(lua_tointeger(L, 2)));
	LUAWRAP_METHOD(methods, write_int, OBJ.write_int(lua_tointeger(L, 2)));
	LUAWRAP_METHOD(methods, write_double, OBJ.write_double(lua_tonumber(L, 2)));
	LUAWRAP_METHOD(methods, write_raw,
			size_t size;
			const char* str = lua_tolstring(L, 2, &size);
			OBJ.write_raw(str, size)
	);
	LUAWRAP_METHOD(methods, move_read_position, OBJ.move_read_position(lua_tointeger(L, 2)));

    LUAWRAP_GETTER(methods, can_read, OBJ.can_read());
	LUAWRAP_GETTER(methods, read_byte, OBJ.read_byte());
	LUAWRAP_GETTER(methods, read_int, OBJ.read_int());
	LUAWRAP_GETTER(methods, read_double, OBJ.read_double());
	LUAWRAP_METHOD(methods, read_raw,
			int size = lua_tointeger(L, 2);
			char* buf = (char*)malloc(size);
			OBJ.read_raw(buf, size);
			lua_pushlstring(L, buf, size);
			free(buf)
	);

    LUAWRAP_GETTER(methods, size, OBJ.size());

	LUAWRAP_GETTER(methods, read_position, OBJ.read_position());
	LUAWRAP_METHOD(getters, raw_buffer, lua_pushlstring(L, OBJ.data(), OBJ.size()));

	luameta_gc<SerializeBuffer>(meta);

	return meta;
}

static int serializebuffer_create(lua_State* L) {
	bool noarg = lua_isnoneornil(L, 1);
	void* data = lua_newuserdata(L, sizeof(SerializeBuffer));
	luameta_push(L, &lua_serializebuffermetatable);
	lua_setmetatable(L,-2);

	if (noarg) {
		new ((SerializeBuffer*)data) SerializeBuffer();
	} else if (lua_isstring(L, 1)){
        new ((SerializeBuffer*)data) SerializeBuffer();
        size_t size;
        const char* msg = lua_tolstring(L, 1, &size);
        ((SerializeBuffer*)data)->write_raw(msg, size);
	} else {
		LuaStackValue args(L, 1);
		if (!args["output_file"].isnil()) {
			const char* filename = args["output_file"].to_str();
			new ((SerializeBuffer*)data) SerializeBuffer(fopen(filename, "wb"), SerializeBuffer::OUTPUT, true);
		} else if (!args["input_file"].isnil()) {
			const char* filename = args["input_file"].to_str();
			new ((SerializeBuffer*)data) SerializeBuffer(fopen(filename, "rb"), SerializeBuffer::INPUT, true);
		}
	}
	return 1;
}

int luaopen_SerializeBuffer(lua_State *L) {
	luawrap::install_userdata_type<SerializeBuffer, &lua_serializebuffermetatable>();

	LuaValue type(L);
	type.newtable();
	type["create"].bind_function(serializebuffer_create);
	type.push();

	return 1;
}
