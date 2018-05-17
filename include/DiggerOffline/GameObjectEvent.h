#pragma once
#include <DiggerOffline/GameObject.h>

class GameObject;

class GameObjectEventInfo {};

class GameObjectEventInfo_dCondition : public GameObjectEventInfo {
public:
	GameObjectEventInfo_dCondition(int delta, GameObject* who);

	int get_delta() const;
	GameObject* get_who() const;

private:
	int delta_;
	GameObject* who_;
};
