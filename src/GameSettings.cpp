#include <DiggerOffline/GameSettings.h>
#include <fstream>


GameSettings::GameSettings(const std::string& settings_file) : failed_(true) {
	// Чтение настроек.
	nlohmann::json settings;
	std::ifstream ifs(settings_file);
	if (!ifs.is_open()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Can't open \"" << settings_file << "\"" << std::endl;
		return;
	}
	ifs >> settings;
	ifs.close();

	// Проверка наличия данных.
	std::vector<std::string> fields = {
		"window_width",
		"window_height",
		"sounds_volume",
		"game_name",
		"default_text_font",
		"default_text_size",
		"default_text_color"
	};
	for (std::vector<std::string>::iterator it = fields.begin(); it != fields.end(); ++it)
		if (settings.find(*it) == settings.end())
			return;
	
	// Запоминание данных.
	window_width_ = settings["window_width"];
	window_height_ = settings["window_height"];
    sounds_volume_ = settings["sounds_volume"].get<float>();
	game_name_ = settings["game_name"].get<std::string>();
	default_text_font_ = settings["default_text_font"].get<std::string>();
	default_text_size_ = settings["default_text_size"];
	default_text_color_ = Color(settings["default_text_color"][0], settings["default_text_color"][1], settings["default_text_color"][2]);

	// Чтение прошло успешно.
	failed_ = false;
}

bool GameSettings::failed() const {
	return failed_;
}

int GameSettings::get_window_width() const {
	return window_width_;
}

int GameSettings::get_window_height() const {
	return window_height_;
}

float GameSettings::get_sounds_volume() const {
	return sounds_volume_;
}

const std::string& GameSettings::get_game_name() const {
	return game_name_;
}

const std::string& GameSettings::get_default_text_font() const {
	return default_text_font_;
}

int GameSettings::get_default_text_size() const {
	return default_text_size_;
}

const Color& GameSettings::get_default_text_color() const {
	return default_text_color_;
}
