#pragma once
#include <DiggerOffline/GameObjectDestroyable.h>

class GameObject_D : public GameObjectDestroyable {
	friend class GameObjectFactory;

public:
	virtual ~GameObject_D() {}

	virtual void Update(long long ms_delta, long long ms_cur);
	virtual void Event(GameObjectEventType event_type, GameObjectEventInfo* event_info);
	virtual void Serialize(std::ofstream& file) const;

protected:
	virtual void Deserialize(std::ifstream& file);
	virtual bool SetStaticProperties(const std::string& section, const nlohmann::json& json);
	virtual bool SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json);
};
