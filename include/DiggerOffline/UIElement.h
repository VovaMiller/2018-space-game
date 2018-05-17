#pragma once
#include <DiggerOffline/Point2DInt.h>
#include <DiggerOffline/Tools.h>
#include <DiggerOffline/Action.h>
#include <json.hpp>
#include <string>

class UIElement {
public:
	UIElement();
	virtual ~UIElement() {}

	const std::string& get_id() const;
	void Initialize(const std::string& id, const nlohmann::json& json);
	void Draw(Window* window) const;
	virtual void ProcessUserAction(UserActionInfo uai) = 0;

protected:
	std::string id_;
	Point2DInt pos_;
	Point2DInt size_;
	std::string texture_;
	std::string text_;
	std::string text_font_;
	int text_size_;
	Color text_color_;
};

class UIButton : public UIElement {
public:
	UIButton(Action* action);
	virtual ~UIButton();

	virtual void ProcessUserAction(UserActionInfo uai);

private:
	Action* action_;
};
