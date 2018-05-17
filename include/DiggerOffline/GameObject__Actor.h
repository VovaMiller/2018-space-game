#pragma once
#include <DiggerOffline/GameObject_DM.h>

class GameObject__Actor : public GameObject_DM {
	friend class GameObjectFactory;
	friend class Gameplay;

public:
	GameObject__Actor();
	virtual ~GameObject__Actor() {}

	const double kInteractionRange = 64.0;

	virtual GameObject* Clone() const;
	virtual bool IsActor() const;

private:
	void InteractWith(GameObject* obj, int x, int y);
};
