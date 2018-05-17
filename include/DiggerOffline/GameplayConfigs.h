#pragma once
#include <json.hpp>

class GameplayConfigs {
public:
	~GameplayConfigs();

	static GameplayConfigs* Instance();
	const nlohmann::json& get_objects() const;

private:
	GameplayConfigs();

	static GameplayConfigs* instance_;
	nlohmann::json objects_;
};
