#include <DiggerOffline/GameObjectFactory.h>
#include <DiggerOffline/GameplayConfigs.h>


GameObject* GameObjectFactory::Create(const std::string& obj_id, const nlohmann::json& json) {
	if (json.find("section") == json.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Field \"section\" is not specified in \"" << obj_id << "\"" << std::endl;
		return nullptr;
	}
	const std::string section = json["section"].get<std::string>();
	const nlohmann::json& config_objects = GameplayConfigs::Instance()->get_objects();
	if (config_objects.find(section) == config_objects.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Section \"" << section << "\" doesn't exist." << std::endl;
		return nullptr;
	}
	const nlohmann::json& section_json = config_objects[section];
	if (section_json.find("class") == section_json.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Object's section \"" << section << "\" doesn't have mandatory field \"class\"." << std::endl;
		return nullptr;
	}
	GameObject* game_object = CreatePure(section_json["class"].get<std::string>());
	if (game_object != nullptr) {
		game_object->SetStaticProperties(section, section_json);
		game_object->SetDynamicProperties(obj_id, json);
	}
	return game_object;
}

GameObject* GameObjectFactory::Create(std::ifstream& file) {
	const std::string section = BinaryFile::ReadString(file);
	const nlohmann::json& config_objects = GameplayConfigs::Instance()->get_objects();
	if (config_objects.find(section) == config_objects.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Section \"" << section << "\" doesn't exist." << std::endl;
		return nullptr;
	}
	const nlohmann::json& section_json = config_objects[section];
	if (section_json.find("class") == section_json.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Object's section \"" << section << "\" doesn't have mandatory field \"class\"." << std::endl;
		return nullptr;
	}
	GameObject* game_object = CreatePure(section_json["class"].get<std::string>());
	if (game_object != nullptr) {
		game_object->SetStaticProperties(section, section_json);
		game_object->Deserialize(file);
	}
	return game_object;
}

GameObject* GameObjectFactory::CreatePure(const std::string& obj_class) {
	if (obj_class == "GameObject__Actor")
		return new GameObject__Actor();
	else if (obj_class == "GameObject__Block")
		return new GameObject__Block();
	return nullptr;
}
