#include <luawrap/luawrap.h>

#include <SDL.h>

#include "TextField.h"

static void textfield_step(TextField& textfield) {
	textfield.step();
}

static void textfield_clear(TextField& textfield) {
	textfield.clear();
}

static void textfield_clear_keystate(TextField& textfield) {
	textfield.clear_keystate();
}

static void textfield_handle_key_up(TextField& textfield, int keycode, int keymod) {
    textfield.handle_key_up(keycode, keymod);
}

static bool textfield_handle_key_down(TextField& textfield, int keycode, int keymod) {
    return textfield.handle_key_down(keycode, keymod);
}

static int lua_newtextinput(lua_State* L) {
	const char* text = lua_gettop(L) >= 2 ? lua_tostring(L, 2) : "";
	luawrap::push(L, TextField(lua_tointeger(L, 1), text));
	return 1;
}

static std::string textfield_get_text(const LuaStackValue& obj, const LuaStackValue& key) {
	return obj.as<TextField*>()->text();
}

static void textfield_set_text(const LuaStackValue& obj, const LuaStackValue& key, const std::string& val) {
	obj.as<TextField*>()->set_text(val);
}

static int textfield_get_max_length(const LuaStackValue& obj, const LuaStackValue& key) {
	return obj.as<TextField*>()->max_length();
}

LuaValue lua_textfieldmetatable(lua_State* L) {
	LuaValue meta = luameta_new(L, "TextField");

	LuaValue methods = luameta_constants(meta);
	LuaValue getters = luameta_getters(meta);
	LuaValue setters = luameta_setters(meta);

	getters["text"].bind_function(textfield_get_text);
	setters["text"].bind_function(textfield_set_text);
	getters["max_length"].bind_function(textfield_get_max_length);
	methods["step"].bind_function(textfield_step);
	methods["handle_key_up"].bind_function(textfield_handle_key_up);
	methods["handle_key_down"].bind_function(textfield_handle_key_down);
	methods["clear"].bind_function(textfield_clear);
	methods["clear_keystate"].bind_function(textfield_clear_keystate);

	luameta_gc<TextField>(meta);

	return meta;
}

int luaopen_TextField(lua_State* L) {
	LuaValue textfield = LuaValue::newtable(L);
	textfield["create"].bind_function(lua_newtextinput);
	luawrap::install_userdata_type<TextField, &lua_textfieldmetatable>();
	textfield.push();
	return 1;
}
