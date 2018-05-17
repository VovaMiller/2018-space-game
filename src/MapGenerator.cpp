#include <DiggerOffline/MapGenerator.h>
#include <DiggerOffline/GameplayConfigs.h>
#include <cstdlib>
#include <ctime>

MapGenerator::MapGenerator(int next_layer) : next_layer_(next_layer) {
	// Initializing prototypes_.
	const nlohmann::json& objs_json = GameplayConfigs::Instance()->get_objects();
	for (nlohmann::json::const_iterator it = objs_json.begin(); it != objs_json.end(); ++it) {
		if ((*it)["class"].get<std::string>() == "GameObject__Block") {
			GameObject__Block* prototype = new GameObject__Block();
			if (prototype->SetStaticProperties(it.key(), *it)) {
				prototype->condition_ = prototype->get_condition_total();
				prototypes_.push_back(prototype);
			} else {
				delete prototype;
				std::cerr << "[MapGenerator] Can't initialize prototype with section \"" << it.key() << "\"" << std::endl;
			}
		}
	}

	// Initializting seed for std::rand().
	std::srand(unsigned(std::time(0)));
}

MapGenerator::~MapGenerator() {
	for (Prototypes::iterator it = prototypes_.begin(); it != prototypes_.end(); ++it)
		delete (*it);
	prototypes_.clear();
}

const int MapGenerator::kMapRadiusX = 1024;
const int MapGenerator::kGeneratorRadiusY = 512;

int MapGenerator::get_next_layer() const {
	return next_layer_;
}

void MapGenerator::Tweak(GameObject__Actor* actor, std::list<GameObject*>& objects) {
	const int block_size = GameObject__Block::kBlockSize;
	const int actor_y = actor->get_pos().y + (actor->get_size().y / 2);
	while ((next_layer_ * block_size) <= (actor_y + kGeneratorRadiusY)) {
		bool error_exists = false;
		int block_pos_x = -kMapRadiusX;
		while (block_pos_x < kMapRadiusX) {
			GameObject* new_block = GetRandomBlock();
			if (new_block != nullptr) {
				new_block->set_pos(Point2DInt(block_pos_x, next_layer_ * block_size));
				objects.push_back(new_block);
			} else {
				error_exists = true;
			}
			block_pos_x += block_size;
		}
		if (error_exists) {
			std::cerr << "[MapGenerator] Error has been acquired while creating layer " << next_layer_ << "." << std::endl;
		}
		++next_layer_;
	}
}

GameObject* MapGenerator::GetRandomBlock() const {
	int total_w = 0;
	for (Prototypes::const_iterator it = prototypes_.begin(); it != prototypes_.end(); ++it)
		if (((*it)->get_spawn_min_layer() <= next_layer_) && (next_layer_ <= (*it)->get_spawn_max_layer()))
			total_w += (*it)->get_spawn_w();
	if (total_w == 0)
		return nullptr;

	int sum_w = 0;
	int ptr_w = std::rand() % total_w;
	for (Prototypes::const_iterator it = prototypes_.begin(); it != prototypes_.end(); ++it) {
		if (((*it)->get_spawn_min_layer() <= next_layer_) && (next_layer_ <= (*it)->get_spawn_max_layer())) {
			sum_w += (*it)->get_spawn_w();
			if (ptr_w < sum_w)
				return (*it)->Clone();
		}
	}
	
	return nullptr;
}
