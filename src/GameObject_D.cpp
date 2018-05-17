#include <DiggerOffline/GameObject_D.h>

void GameObject_D::Update(long long ms_delta, long long ms_cur) {
	GameObject::Update(ms_delta, ms_cur);
	GameObjectDestroyable::Update(ms_delta, ms_cur);
}

void GameObject_D::Event(GameObjectEventType event_type, GameObjectEventInfo* event_info) {
	GameObject::Event(event_type, event_info);
	GameObjectDestroyable::Event(event_type, event_info);
}

void GameObject_D::Serialize(std::ofstream& file) const {
	GameObject::Serialize(file);
	GameObjectDestroyable::Serialize(file);
}

void GameObject_D::Deserialize(std::ifstream& file) {
	GameObject::Deserialize(file);
	GameObjectDestroyable::Deserialize(file);
}

bool GameObject_D::SetStaticProperties(const std::string& section, const nlohmann::json& json) {
	return GameObject::SetStaticProperties(section, json)
		&& GameObjectDestroyable::SetStaticProperties(section, json);
}

bool GameObject_D::SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json) {
	return GameObject::SetDynamicProperties(obj_id, json)
		&& GameObjectDestroyable::SetDynamicProperties(obj_id, json);
}
