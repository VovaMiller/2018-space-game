#pragma once
#include <DiggerOffline/GameObject_D.h>

class GameObject__Block : public GameObject_D {
	friend class GameObjectFactory;
	friend class MapGenerator;

public:
	GameObject__Block();
	virtual ~GameObject__Block() {}

	static const int kBlockSize;

	virtual GameObject* Clone() const;
	int get_spawn_min_layer() const;
	int get_spawn_max_layer() const;
	unsigned int get_spawn_w() const;

protected:
	int spawn_min_layer_;
	int spawn_max_layer_;
	unsigned int spawn_w_;

	virtual bool SetStaticProperties(const std::string& section, const nlohmann::json& json);
};
