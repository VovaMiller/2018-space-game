#include <DiggerOffline/GameObject.h>

GameObject::GameObject() : type_(kObjTypeImpenetrable), state_(kObjStateOnline), to_be_removed_(false) {}

void GameObject::set_pos(const Point2DInt& pos) {
	pos_.x = (double)pos.x;
	pos_.y = (double)pos.y;
}

void GameObject::set_pos(const Point2D& pos) {
	pos_ = pos;
}

Point2DInt GameObject::get_pos() const {
	return Point2DInt((int)pos_.x, (int)pos_.y);
}

const Point2D& GameObject::get_posd() const {
	return pos_;
}

const Point2DInt& GameObject::get_size() const {
	return size_;
}

const std::string& GameObject::get_section() const {
	return section_;
}

const std::string& GameObject::get_texture() const {
	return texture_;
}

GameObjectType GameObject::get_type() const {
	return type_;
}

GameObjectState GameObject::get_state() const {
	return state_;
}

double GameObject::Distance(int x, int y) const {
	return Distance(Point2DInt(x, y));
}

double GameObject::Distance(const Point2DInt& point) const {
	return ((get_pos() + (get_size() / 2)) - point).len();
}

double GameObject::Distance(GameObject* other) const {
	return Distance(other->get_pos() + (other->get_size() / 2));
}

void GameObject::Remove() {
	to_be_removed_ = true;
}

bool GameObject::IsToBeRemoved() const {
	return to_be_removed_;
}

bool GameObject::IsActor() const {
	return false;
}

void GameObject::Event(GameObjectEventType event_type, GameObjectEventInfo* event_info) {
	if (event_type == kObjEventDeath)
		Remove();
}

void GameObject::Serialize(std::ofstream& file) const {
	BinaryFile::WriteString(file, section_);
	BinaryFile::WriteDouble(file, pos_.x);
	BinaryFile::WriteDouble(file, pos_.y);
	BinaryFile::WriteInt(file, static_cast<int>(type_));
	BinaryFile::WriteInt(file, static_cast<int>(state_));
	BinaryFile::WriteBool(file, to_be_removed_);
}

void GameObject::Deserialize(std::ifstream& file) {
	pos_.x = BinaryFile::ReadDouble(file);
	pos_.y = BinaryFile::ReadDouble(file);
	type_ = static_cast<GameObjectType>(BinaryFile::ReadInt(file));
	state_ = static_cast<GameObjectState>(BinaryFile::ReadInt(file));
	to_be_removed_ = BinaryFile::ReadBool(file);
}

bool GameObject::SetStaticProperties(const std::string& section, const nlohmann::json& json) {
	section_ = section;

	// size (size_)
	const std::string size_field = "size";
	if (json.find(size_field) == json.end()) {
		size_.x = 32;
		size_.y = 32;
	} else {
		size_.x = json[size_field][0];
		size_.y = json[size_field][1];
	}

	// texture (texture_)
	const std::string texture_field = "texture";
	if (json.find(texture_field) == json.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Object's section \"" << section << "\" doesn't have mandatory field \"" << texture_field << "\"." << std::endl;
		return false;
	}
	texture_ = json[texture_field].get<std::string>();

	return true;
}

bool GameObject::SetDynamicProperties(const std::string& obj_id, const nlohmann::json& json) {
	// position (pos_)
	const std::string pos_field = "position";
	if (json.find(pos_field) == json.end()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Object \"" << obj_id << "\" doesn't have mandatory field \"" << pos_field << "\"." << std::endl;
		return false;
	}
	pos_.x = json[pos_field][0];
	pos_.y = json[pos_field][1];

	// type (type_)
	const std::string type_field = "type";
	if (json.find(type_field) == json.end())
		type_ = kObjTypeImpenetrable;
	else
		type_ = static_cast<GameObjectType>(json[type_field].get<int>());

	// state (state_)
	const std::string state_field = "state";
	if (json.find(state_field) == json.end())
		state_ = kObjStateOnline;
	else
		state_ = static_cast<GameObjectState>(json[state_field].get<int>());

	// temp (to_be_removed_)
	const std::string temp_field = "temp";
	if (json.find(temp_field) == json.end())
		to_be_removed_ = false;
	else
		to_be_removed_ = json[temp_field].get<bool>();

	return true;
}
