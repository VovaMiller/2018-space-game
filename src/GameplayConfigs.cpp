#include <DiggerOffline/GameplayConfigs.h>
#include <DiggerOffline/Game.h>
#include <fstream>

GameplayConfigs* GameplayConfigs::instance_ = nullptr;

GameplayConfigs* GameplayConfigs::Instance() {
	if (instance_ == nullptr)
		instance_ = new GameplayConfigs;
	return instance_;
}

GameplayConfigs::GameplayConfigs() {
	Game* game = Game::Instance();

	// objects_
	const std::string json_path = game->kGamedata + "config/gameplay/objects.json";
	std::ifstream ifs(json_path);
	if (!ifs.is_open()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Can't open \"" << json_path << "\"" << std::endl;
		game->FatalError();
		return;
	}
	ifs >> objects_;
	ifs.close();
}

GameplayConfigs::~GameplayConfigs() {
	instance_ = nullptr;
}

const nlohmann::json& GameplayConfigs::get_objects() const {
	return objects_;
}
