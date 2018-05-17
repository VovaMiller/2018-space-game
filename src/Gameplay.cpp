#include <DiggerOffline/Gameplay.h>
#include <DiggerOffline/Game.h>
#include <DiggerOffline/GameplayConfigs.h>
#include <DiggerOffline/Box2DInt.h>
#include <fstream>


Gameplay::Gameplay() : active_map_(""), last_update_(-1), actor_(nullptr), map_generator_(nullptr) {
	// Чтение настроек спавна ГГ.
	Game* game = Game::Instance();
	const std::string actor_spawn_path = game->kGamedata + "spawn/spawn_actor.json";
	nlohmann::json spawn_actor_json;
	std::ifstream ifs(actor_spawn_path);
	if (!ifs.is_open()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Can't open \"" << actor_spawn_path << "\"" << std::endl;
		game->FatalError();
		return;
	}
	ifs >> spawn_actor_json;
	ifs.close();

	// Инициализация свойств спавна ГГ.
	const std::string field_position = "position";
	if (spawn_actor_json.find(field_position) == spawn_actor_json.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    File \"" << actor_spawn_path << "\" doesn't have mandatory field \"" << field_position << "\"." << std::endl;
		game->FatalError();
		return;
	}
	actor_spawn_position_.x = spawn_actor_json[field_position][0];
	actor_spawn_position_.y = spawn_actor_json[field_position][1];
}

Gameplay::~Gameplay() {
	ClearObjects();
}

void Gameplay::set_last_update(long long ms_cur) {
	last_update_ = ms_cur;
}

const std::string& Gameplay::get_active_map() const {
    return active_map_;
}

GameObject__Actor* Gameplay::get_actor() const {
    return actor_;
}

void Gameplay::NewMap() {
	Game* game = Game::Instance();

	// Предварительная очистка.
	ClearObjects();

	// Генератор имени новой карты.
	int n = 1;
	const std::string name_prefix = game->kGamemaps + "map_";
	while (true) {
		std::ifstream f(name_prefix + std::to_string(n));
		if (!f.good())
			break;
		++n;
	}
	active_map_ = name_prefix + std::to_string(n);

	// Открытие настроек начальной генерации.
	const std::string spawn_path = game->kGamedata + "spawn/spawn.json";
	nlohmann::json json_spawn;
	std::ifstream ifs(spawn_path);
	if (!ifs.is_open()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Can't open \"" << spawn_path << "\"" << std::endl;
		game->FatalError();
		return;
	}
	ifs >> json_spawn;
	ifs.close();

	// Создание ГГ.
	SpawnActor();

	// Создание других объектов.
	std::string key;
	for (nlohmann::json::iterator it = json_spawn.begin(); it != json_spawn.end(); ++it) {
		key = it.key();
		GameObject* game_object = GameObjectFactory::Create(key, *it);
		if (game_object == nullptr) {
			game->FatalError();
			return;
		}
		objects_.push_back(game_object);
	}

	// Инициализация генератора карты и создание начального окружения.
	map_generator_ = new MapGenerator(0);
	map_generator_->Tweak(actor_, objects_);

	// Сохранение созданной карты.
	SaveMap();

	// Добавление в список карт.
	std::ofstream maps_list(game->kGamemaps + "GameMapsList", std::ios::app);
	maps_list << "map_" << n << std::endl;
}

void Gameplay::LoadMap(const std::string& file_path) {
	Game* game = Game::Instance();
	std::ifstream map_file(file_path, std::ios::in | std::ios::binary);
	ClearObjects();

	// Загрузка настроек генератора карты.
	int last_layer = BinaryFile::ReadInt(map_file);
	map_generator_ = new MapGenerator(last_layer);

	// Загрузка состояния ГГ.
	const std::string actor_section = BinaryFile::ReadString(map_file);
	actor_ = new GameObject__Actor();
	const nlohmann::json& config_objects = GameplayConfigs::Instance()->get_objects();
	if (config_objects.find(actor_section) == config_objects.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Actor's section \"" << actor_section << "\" doesn't exist." << std::endl;
		game->FatalError();
		return;
	}
	actor_->SetStaticProperties(actor_section, config_objects[actor_section]);
	actor_->Deserialize(map_file);

	// Загрузка остальных объектов.
	int n = BinaryFile::ReadInt(map_file);
	for (int i = 0; i < n; ++i) {
		GameObject* game_object = GameObjectFactory::Create(map_file);
		if (game_object == nullptr) {
			game->FatalError();
			return;
		}
		objects_.push_back(game_object);
	}

	active_map_ = file_path;
	map_file.close();
}

void Gameplay::SaveMap() {
	std::ofstream map_file(active_map_, std::ios::out | std::ios::binary);
	BinaryFile::WriteInt(map_file, map_generator_->get_next_layer());
	actor_->Serialize(map_file);
	BinaryFile::WriteInt(map_file, (int)objects_.size());
	for (ObjectsStorage::iterator it = objects_.begin(); it != objects_.end(); ++it) {
		(*it)->Serialize(map_file);
	}
	map_file.close();
}

void Gameplay::Halt() {
	active_map_ = "";
	last_update_ = -1;
	ClearObjects();
}

void Gameplay::Update(long long ms_cur) {
	long long ms_delta = ms_cur - last_update_;
	if (ms_delta > 0) {
		// Map Generator.
		map_generator_->Tweak(actor_, objects_);

		// Actor.
		actor_->Update(ms_delta, ms_cur);
		UpdateScreenPosition();

		// Other objects.
		for (ObjectsStorage::iterator it = objects_.begin(); it != objects_.end(); ++it) {
			(*it)->Update(ms_delta, ms_cur);
		}

		// Actor's death.
		if (actor_->IsToBeRemoved()) {
			delete actor_;
			SpawnActor();
		}

		// Objects cleaner.
		for (ObjectsStorage::iterator it = objects_.begin(); it != objects_.end(); ) {
			if ((*it)->IsToBeRemoved()) {
				GameObject* game_object = *it;
				it = objects_.erase(it);
				delete game_object;
			} else {
				++it;
			}
		}

		last_update_ = ms_cur;
	}
}

void Gameplay::Draw(Window* window) const {
	// Background.
	Game* game = Game::Instance();
	window->DrawTexture(Point2DInt(0, 0),
		Point2DInt(game->get_settings()->get_window_width(), game->get_settings()->get_window_height()),
		"gameplay/background.png");

	// Actor.
	DrawObject(window, actor_);

	// Other objects.
	for (ObjectsStorage::const_iterator it = objects_.begin(); it != objects_.end(); ++it) {
		DrawObject(window, *it);
	}
}

void Gameplay::ProcessUserAction(UserActionInfo uai) {
	// Обновление pressed_buttons_.
	if (uai.uat == kUserActionPressed) {
		pressed_buttons_.insert(uai.ua);
	} else if (uai.uat == kUserActionReleased) {
		pressed_buttons_.erase(uai.ua);
	}

	// Actor's moving.
	Point2DInt moving_dir(0, 0);
	if (pressed_buttons_.find(kA) != pressed_buttons_.end())
		moving_dir.x -= 1;
	if (pressed_buttons_.find(kD) != pressed_buttons_.end())
		moving_dir.x += 1;
	actor_->SetMovingDirection(moving_dir);

	// Actor's jumping.
	if ((uai.uat == kUserActionPressed) && ((uai.ua == kW) || (uai.ua == kSpace)))
		actor_->Jump();

	// Actor's destruction (TEST).
	if (uai.ua == kMouseClickLeft) {
		GameObject* victim = GetObject(screen_position_.x + uai.x, screen_position_.y + uai.y);
		actor_->InteractWith(victim, screen_position_.x + uai.x, screen_position_.y + uai.y);
	}

}

bool Gameplay::IsOnScreen(GameObject* game_object) const {
	Game* game = Game::Instance();
	Box2DInt screen_box(screen_position_.x, screen_position_.y,
		game->get_settings()->get_window_width(), game->get_settings()->get_window_height());
	Box2DInt object_box(game_object->get_pos(), game_object->get_size());
	return screen_box.IntersectsWith(object_box);
}

void Gameplay::UpdateScreenPosition() {
	// Actor in center.
	Game* game = Game::Instance();
	Point2DInt screen_size(game->get_settings()->get_window_width(), game->get_settings()->get_window_height());
	Point2DInt actor_center = actor_->get_pos() + (actor_->get_size() / 2);
	screen_position_ = actor_center - (screen_size / 2);

	// Left edge.
	screen_position_.x = std::max(screen_position_.x, -MapGenerator::kMapRadiusX);

	// Right edge.
	screen_position_.x = std::min(screen_position_.x, MapGenerator::kMapRadiusX - game->get_settings()->get_window_width());
}

void Gameplay::SpawnActor() {
	Game* game = Game::Instance();
	actor_ = new GameObject__Actor();
	const std::string actor_section = "actor";
	const nlohmann::json& config_objects = GameplayConfigs::Instance()->get_objects();
	if (config_objects.find(actor_section) == config_objects.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Actor's section \"" << actor_section << "\" wasn't found." << std::endl;
		game->FatalError();
		return;
	}
	actor_->SetStaticProperties(actor_section, config_objects[actor_section]);
	actor_->set_pos(actor_spawn_position_);
}

void Gameplay::ClearObjects() {
	if (map_generator_ != nullptr) {
		delete map_generator_;
		map_generator_ = nullptr;
	}
	if (actor_ != nullptr) {
		delete actor_;
		actor_ = nullptr;
	}
	for (ObjectsStorage::iterator it = objects_.begin(); it != objects_.end(); ++it) {
		delete (*it);
	}
	objects_.clear();
}

void Gameplay::DrawObject(Window* window, GameObject* game_object) const {
	if (IsOnScreen(game_object)) {
		window->DrawTexture(game_object->get_pos() - screen_position_, game_object->get_size(), game_object->get_texture());
	}
}

GameObject* Gameplay::GetObject(int x, int y) {
	for (ObjectsStorage::iterator it = objects_.begin(); it != objects_.end(); ++it) {
		Box2DInt box((*it)->get_pos(), (*it)->get_size());
		if (box.Has(x, y))
			return *it;
	}
	return nullptr;
}

GameObject* Gameplay::GetObject(const Point2DInt& point) {
	return GetObject(point.x, point.y);
}
