#include <DiggerOffline/GameObject_DM.h>

void GameObject_DM::Update(long long ms_delta, long long ms_cur) {
	GameObject::Update(ms_delta, ms_cur);
	GameObjectDestroyable::Update(ms_delta, ms_cur);
	GameObjectMotile::Update(ms_delta, ms_cur);
}

void GameObject_DM::Event(GameObjectEventType event_type, GameObjectEventInfo* event_info) {
	GameObject::Event(event_type, event_info);
	GameObjectDestroyable::Event(event_type, event_info);
	GameObjectMotile::Event(event_type, event_info);
}

void GameObject_DM::Serialize(std::ofstream& file) const {
	GameObject::Serialize(file);
	GameObjectDestroyable::Serialize(file);
	GameObjectMotile::Serialize(file);
}

void GameObject_DM::Deserialize(std::ifstream& file) {
	GameObject::Deserialize(file);
	GameObjectDestroyable::Deserialize(file);
	GameObjectMotile::Deserialize(file);
}

bool GameObject_DM::SetStaticProperties(const std::string& section, const nlohmann::json& json) {
	return GameObject::SetStaticProperties(section, json)
		&& GameObjectDestroyable::SetStaticProperties(section, json)
		&& GameObjectMotile::SetStaticProperties(section, json);
}

bool GameObject_DM::SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json) {
	return GameObject::SetDynamicProperties(obj_id, json)
		&& GameObjectDestroyable::SetDynamicProperties(obj_id, json)
		&& GameObjectMotile::SetDynamicProperties(obj_id, json);
}

void GameObject_DM::set_velocity(const Point2D& velocity) {
	double delta = (get_velocity() - velocity).len();
	GameObjectMotile::set_velocity(velocity);
	if (delta > 10.0) {
		Damage((int)(8.0 * (delta - 10.0)), nullptr);
	}
}
