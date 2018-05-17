#pragma once
#include <DiggerOffline/GameObject__Actor.h>
#include <DiggerOffline/GameObject__Block.h>
#include <DiggerOffline/Gameplay.h>

class GameObjectFactory {
	friend class Gameplay;

public:
	// Создаёт объект, описанный в "spawn.json".
	// Возвращает nullptr при ошибке.
	static GameObject* Create(const std::string& obj_id, const nlohmann::json& json);

private:
	// Создаёт объект из файла сохранения.
	// Возвращает nullptr при ошибке.
	static GameObject* Create(std::ifstream& file);
	// Создаёт объект по имени класса.
	// Возвращает nullptr при ошибке.
	static GameObject* CreatePure(const std::string& obj_class);
};
