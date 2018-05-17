#pragma once
#include <DiggerOffline/UI.h>

class UI;
class UIStartMenu;
class UIPlaying;
class UIGameMenu;
class UIMapMenu;

class UIHolder {
public:
	UIHolder();
	~UIHolder();

	void Draw(Window* window) const;
	void ProcessUserAction(UserActionInfo uai);
	void Update();
	void Back();
	void SwitchToStartMenu();
	void SwitchToPlaying();
	void SwitchToGameMenu();
	void SwitchToMapMenu();

private:
	UI* ui_active_;
	UIStartMenu* ui_start_menu_;
	UIPlaying* ui_playing_;
	UIGameMenu* ui_game_menu_;
	UIMapMenu* ui_map_menu_;
};
