/*
 * TextField.h:
 *  Interface component for entering text.
 *  This includes stuff like entering name before play, etc.
 */

#ifndef TEXTFIELD_H_
#define TEXTFIELD_H_

#include <string>

#include <lcommon/Timer.h>

class GameState;

class TextField {
public:
	TextField(int max_length, const std::string& default_text = std::string());

	void set_text(const std::string& txt) {
		_text = txt;
	}
    const std::string& text() const {
        return _text;
    }

    void handle_key_up(int keycode, int keymod);
    bool handle_key_down(int keycode, int keymod);

    bool empty() const {
    	return _text.empty();
    }
    void step();
    void clear();
    void clear_keystate();
	int max_length() const {
		return _max_length;
	}
private:
	void _handle_backspace();

	bool _has_repeat_cooldown();
	void _reset_repeat_cooldown(int cooldownms);
	int _current_key;
	int _current_mod;

	std::string _text;
	int _max_length;
	int _repeat_cooldown;
	Timer _repeat_timer;
};

#endif /* TEXTFIELD_H_ */
