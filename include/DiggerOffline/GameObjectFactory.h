#pragma once
#include <DiggerOffline/GameObject__Actor.h>
#include <DiggerOffline/GameObject__Block.h>
#include <DiggerOffline/Gameplay.h>

class GameObjectFactory {
	friend class Gameplay;

public:
	// ������ ������, ��������� � "spawn.json".
	// ���������� nullptr ��� ������.
	static GameObject* Create(const std::string& obj_id, const nlohmann::json& json);

private:
	// ������ ������ �� ����� ����������.
	// ���������� nullptr ��� ������.
	static GameObject* Create(std::ifstream& file);
	// ������ ������ �� ����� ������.
	// ���������� nullptr ��� ������.
	static GameObject* CreatePure(const std::string& obj_class);
};
