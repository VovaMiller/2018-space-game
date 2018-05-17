#pragma once
#include <json.hpp>
#include <DiggerOffline/Color.h>
#include <string>

class GameSettings {
public:
	GameSettings(const std::string& settings_file);

	bool failed() const;
	int get_window_width() const;
	int get_window_height() const;
    float get_sounds_volume() const;
	const std::string& get_game_name() const;
	const std::string& get_default_text_font() const;
	int get_default_text_size() const;
	const Color& get_default_text_color() const;
private:
	bool failed_;
	int window_width_;
	int window_height_;
    float sounds_volume_;
	std::string game_name_;
	std::string default_text_font_;
	int default_text_size_;
	Color default_text_color_;
};
