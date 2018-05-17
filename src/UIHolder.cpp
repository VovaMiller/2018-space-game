#include <DiggerOffline/UIHolder.h>

UIHolder::UIHolder() : ui_active_(nullptr) {
	ui_start_menu_ = new UIStartMenu();
	ui_playing_ = new UIPlaying();
	ui_game_menu_ = new UIGameMenu();
	ui_map_menu_ = new UIMapMenu();
	ui_playing_->parent_ = ui_game_menu_;
	ui_game_menu_->parent_ = ui_playing_;
	ui_map_menu_->parent_ = ui_start_menu_;
	SwitchToStartMenu();
}

UIHolder::~UIHolder() {
	ui_active_ = nullptr;
	delete ui_start_menu_;
	delete ui_playing_;
	delete ui_game_menu_;
	delete ui_map_menu_;
}

void UIHolder::Draw(Window* window) const {
	if (ui_active_ != nullptr)
		ui_active_->Draw(window);
}

void UIHolder::ProcessUserAction(UserActionInfo uai) {
	if (ui_active_ != nullptr)
		ui_active_->ProcessUserAction(uai);
}

void UIHolder::Update() {
	ui_active_->Update();
}

void UIHolder::Back() {
	if (ui_active_->parent_ != nullptr) {
		ui_active_->OnClose();
		ui_active_->parent_->OnLoad();
		ui_active_ = ui_active_->parent_;
	}
}

void UIHolder::SwitchToStartMenu() {
	if ((ui_active_ != nullptr) && (ui_active_ != ui_start_menu_))
		ui_active_->OnClose();
	ui_start_menu_->OnLoad();
	ui_active_ = ui_start_menu_;
}

void UIHolder::SwitchToPlaying() {
	if ((ui_active_ != nullptr) && (ui_active_ != ui_playing_))
		ui_active_->OnClose();
	ui_playing_->OnLoad();
	ui_active_ = ui_playing_;
}

void UIHolder::SwitchToGameMenu() {
	if ((ui_active_ != nullptr) && (ui_active_ != ui_game_menu_))
		ui_active_->OnClose();
	ui_game_menu_->OnLoad();
	ui_active_ = ui_game_menu_;
}

void UIHolder::SwitchToMapMenu() {
	if ((ui_active_ != nullptr) && (ui_active_ != ui_map_menu_))
		ui_active_->OnClose();
	ui_map_menu_->OnLoad();
	ui_active_ = ui_map_menu_;
}
