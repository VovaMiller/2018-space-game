#pragma once
#include <DiggerOffline/GameObject.h>

class GameObjectDestroyable : virtual public GameObject {
	friend class GameObjectFactory;

public:
	GameObjectDestroyable();
	virtual ~GameObjectDestroyable() {}

	int get_condition() const;
	int get_condition_total() const;

	virtual void Update(long long ms_delta, long long ms_cur);
	virtual void Event(GameObjectEventType event_type, GameObjectEventInfo* event_info);
	virtual void Serialize(std::ofstream& file) const;

protected:
	int condition_;
	int condition_total_;
	std::string sound_hit_;

	virtual void Deserialize(std::ifstream& file);
	virtual bool SetStaticProperties(const std::string& section, const nlohmann::json& json);
	virtual bool SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json);
	void Damage(int dmg, GameObject* who);
	void Repair(int hp, GameObject* who);
};
