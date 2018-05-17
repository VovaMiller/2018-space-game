#include <DiggerOffline/GameObjectDestroyable.h>
#include <DiggerOffline/Game.h>

GameObjectDestroyable::GameObjectDestroyable() : condition_(100), condition_total_(100) {}

int GameObjectDestroyable::get_condition() const {
	return condition_;
}

int GameObjectDestroyable::get_condition_total() const {
	return condition_total_;
}

void GameObjectDestroyable::Update(long long ms_delta, long long ms_cur) {}

void GameObjectDestroyable::Event(GameObjectEventType event_type, GameObjectEventInfo* event_info) {
	if (event_type == kObjEventCondition) {
		GameObjectEventInfo_dCondition* info = (GameObjectEventInfo_dCondition*)event_info;
		int delta = info->get_delta();
		if (delta < 0)
			Damage(-delta, info->get_who());
		else
			Repair(delta, info->get_who());
	}
}

void GameObjectDestroyable::Serialize(std::ofstream& file) const {
	BinaryFile::WriteInt(file, condition_);
}

void GameObjectDestroyable::Deserialize(std::ifstream& file) {
	condition_ = BinaryFile::ReadInt(file);
}

bool GameObjectDestroyable::SetStaticProperties(const std::string& section, const nlohmann::json& json) {
	// condition_total (condition_total_)
	const std::string condition_total_field = "condition_total";
	if (json.find(condition_total_field) == json.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Object's section \"" << section << "\" doesn't have mandatory field \"" << condition_total_field << "\"." << std::endl;
		return false;
	}
	condition_total_ = json[condition_total_field].get<int>();

	// sound_hit (sound_hit_)
	const std::string sound_hit_field = "sound_hit";
	if (json.find(sound_hit_field) == json.end())
		sound_hit_ = "";
	else
		sound_hit_ = json[sound_hit_field].get<std::string>();

	return true;
}

bool GameObjectDestroyable::SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json) {
	// condition (condition_)
	const std::string condition_field = "condition";
	if (json.find(condition_field) == json.end())
		condition_ = condition_total_;
	else
		condition_ = json[condition_field].get<int>();

	return true;
}

void GameObjectDestroyable::Damage(int dmg, GameObject* who) {
	if (dmg <= 0)
		return;

	// Изменение состояния.
	condition_ = std::max(condition_ - dmg, 0);

	// Воспроизведение sound_hit.
	if ((who != nullptr) && (who->IsActor())) {
		if (sound_hit_.length() > 0)
			Game::Instance()->get_audio_player()->Play(sound_hit_, true);
	}

	// Убиение объекта, если необходимо.
	if (condition_ == 0)
		Event(kObjEventDeath, nullptr);
}

void GameObjectDestroyable::Repair(int hp, GameObject* who) {
	if (hp <= 0)
		return;
	condition_ = std::min(condition_ + hp, condition_total_);
}
