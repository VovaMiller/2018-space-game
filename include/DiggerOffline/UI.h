#pragma once
#include <DiggerOffline/UIElement.h>
#include <DiggerOffline/UIHolder.h>

class UI {
public:
	UI();
	virtual ~UI();

	virtual void Draw(Window* window) const;
	void ProcessUserAction(UserActionInfo uai);
	virtual void OnLoad() = 0;
	virtual void OnClose() = 0;
	virtual void Update() = 0;

protected:
	std::vector<UIElement*> ui_elements_;

private:
	friend class UIHolder;
	UI* parent_;
};


class UIStartMenu : public UI {
public:
	UIStartMenu();

	virtual void Draw(Window* window) const;
	virtual void OnLoad();
	virtual void OnClose() {}
	virtual void Update() {}

private:
	std::string background_;
	std::string sound_;
};

class UIGameMenu : public UI {
public:
	UIGameMenu();

	virtual void Draw(Window* window) const;
	virtual void OnLoad() {}
	virtual void OnClose() {}
	virtual void Update() {}

private:
	std::string background_;
};

class UIMapMenu : public UI {
public:
	UIMapMenu();

	virtual void Draw(Window* window) const;
	virtual void OnLoad();
	virtual void OnClose() {}
	virtual void Update() {}

private:
	std::string background_;
	nlohmann::json json_btn_map_;

	void UpdateMapButtons();
};

class UIPlaying : public UI {
public:
	UIPlaying();

	virtual void OnLoad();
	virtual void OnClose() {}
	virtual void Update();

private:
	std::string sound_;
};
