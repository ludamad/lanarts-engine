/*
 * LuaLazyValue.cpp:
 *  Lazy-resolved lua expression.
 */

#include "LuaLazyValue.h"

LuaLazyValue::LuaLazyValue(const std::string& expr) :
		_expression(expr) {
}

LuaLazyValue::LuaLazyValue(const LuaValue& value) :
		_value(value) {
}

LuaLazyValue::LuaLazyValue() {
}

LuaLazyValue::~LuaLazyValue() {
}

LuaValue& LuaLazyValue::get(lua_State* L) {
	initialize(L);
	return _value;
}

void LuaLazyValue::initialize(lua_State* L) {
	if (_value.empty()) {
		_value = luawrap::eval(L, _expression);
		_expression = std::string(); // free string
	}
}

bool LuaLazyValue::empty() const {
	return _expression.empty() && _value.empty();
}

bool LuaLazyValue::is_initialized() const {
	return !_value.empty();
}
