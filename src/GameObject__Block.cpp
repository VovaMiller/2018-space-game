#include <DiggerOffline/GameObject__Block.h>
#include <limits>  // std::numeric_limits

GameObject__Block::GameObject__Block() {
	size_.x = GameObject__Block::kBlockSize;
	size_.y = GameObject__Block::kBlockSize;
}

const int GameObject__Block::kBlockSize = 32;

GameObject* GameObject__Block::Clone() const {
	return new GameObject__Block(*this);
}

int GameObject__Block::get_spawn_min_layer() const {
	return spawn_min_layer_;
}

int GameObject__Block::get_spawn_max_layer() const {
	return spawn_max_layer_;
}

unsigned int GameObject__Block::get_spawn_w() const {
	return spawn_w_;
}

bool GameObject__Block::SetStaticProperties(const std::string& section, const nlohmann::json& json) {
	if (!GameObject_D::SetStaticProperties(section, json)) {
		return false;
	}

	// Default block size.
	size_.x = GameObject__Block::kBlockSize;
	size_.y = GameObject__Block::kBlockSize;

	// spawn_min_layer (spawn_min_layer_)
	const std::string spawn_min_layer_field = "spawn_min_layer";
	if (json.find(spawn_min_layer_field) == json.end())
		spawn_min_layer_ = 0;
	else
		spawn_min_layer_ = json[spawn_min_layer_field].get<int>();

	// spawn_max_layer (spawn_max_layer_)
	const std::string spawn_max_layer_field = "spawn_max_layer";
	if (json.find(spawn_max_layer_field) == json.end())
		spawn_max_layer_ = std::numeric_limits<int>::max() / kBlockSize;
	else
		spawn_max_layer_ = json[spawn_max_layer_field].get<int>();

	// spawn_w (spawn_w_)
	const std::string spawn_w_field = "spawn_w";
	if (json.find(spawn_w_field) == json.end())
		spawn_w_ = 0;
	else
		spawn_w_ = json[spawn_w_field].get<int>();

	return true;
}
