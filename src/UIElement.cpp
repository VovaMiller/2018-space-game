#include <DiggerOffline/UIElement.h>
#include <DiggerOffline/Game.h>

UIElement::UIElement() : text_size_(0) {}

const std::string& UIElement::get_id() const {
	return id_;
}

void UIElement::Initialize(const std::string& id, const nlohmann::json& json) {
	Game* game = Game::Instance();
	id_ = id;

	// pos_
	if (json.find("position") != json.end()) {
		pos_ = Point2DInt(json["position"][0], json["position"][1]);
	} else {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    UIElement \"" << id << "\" doesn't have mandatory field \"position\"." << std::endl;
		game->FatalError();
		return;
	}

	// size_
	if (json.find("size") != json.end()) {
		size_ = Point2DInt(json["size"][0], json["size"][1]);
	} else {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    UIElement \"" << id << "\" doesn't have mandatory field \"size\"." << std::endl;
		game->FatalError();
		return;
	}

	// texture_
	if (json.find("texture") != json.end()) {
		texture_ = json["texture"].get<std::string>();
	} else {
		texture_ = "";
	}

	// text_
	if (json.find("text") != json.end()) {
		text_ = json["text"].get<std::string>();
	} else {
		text_ = id;
	}

	// text_font_
	if (json.find("text_font") != json.end()) {
		text_font_ = json["text_font"].get<std::string>();
	} else {
		text_font_ = game->get_settings()->get_default_text_font();
	}

	//text_size_
	if (json.find("text_size") != json.end()) {
		text_size_ = json["text_size"];
	} else {
		text_size_ = game->get_settings()->get_default_text_size();
	}

	// text_color_
	if (json.find("text_color") != json.end()) {
		text_color_ = Color(json["text_color"][0], json["text_color"][1], json["text_color"][2]);
	} else {
		text_color_ = game->get_settings()->get_default_text_color();
	}
}

void UIElement::Draw(Window* window) const {
	// Отрисовка текстуры.
	if (texture_.size() > 0)
		window->DrawTexture(pos_, size_, texture_);

	// Отрисовка текста.
	Point2DInt text_pos_ = pos_ + (size_ / 2);
	window->DrawText(text_, text_font_, text_size_, text_color_, text_pos_, kCenterX, kCenterY);
}



UIButton::UIButton(Action* action) : action_(action) {}

UIButton::~UIButton() {
	if (action_ != nullptr)
		delete action_;
}

void UIButton::ProcessUserAction(UserActionInfo uai) {
	if (uai.ua == kMouseClickLeft) {
		Point2DInt bottom_right = pos_ + size_;
		if ((uai.x >= pos_.x) && (uai.x <= bottom_right.x)
			&& (uai.y >= pos_.y) && (uai.y <= bottom_right.y)) {
			if (action_ != nullptr)
				action_->Act();
		}
	}
}
