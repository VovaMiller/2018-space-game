#include <DiggerOffline/Game.h>
#include <DiggerOffline/Tools_SFML.h>
#include <DiggerOffline/GameplayConfigs.h>
#include <fstream>
#include <chrono>

Game* Game::instance_ = nullptr;

Game* Game::Instance() {
	if (instance_ == nullptr)
		instance_ = new Game;
	return instance_;
}

Game::Game() : window_(nullptr), audio_player_(nullptr), ui_(nullptr), gameplay_(nullptr), state_(kStateOffline) {
	// settings_
	std::string settings_file = kGamedata + "config/settings.json";
	settings_ = new GameSettings(settings_file);
	if (settings_->failed()) {
        std::cerr << "[ERROR] Can't open settings file \"" << settings_file << "\"" << std::endl;
		settings_ = nullptr;
	}
}

Game::~Game() {
	instance_ = nullptr;
	if (gameplay_ != nullptr)
		delete gameplay_;
	if (ui_ != nullptr)
		delete ui_;
	if (audio_player_ != nullptr)
		delete audio_player_;
	if (window_ != nullptr)
		delete window_;
	if (settings_ != nullptr)
		delete settings_;
}

UIHolder* Game::get_ui() const {
	return ui_;
}

const GameSettings* Game::get_settings() const {
	return settings_;
}

AudioPlayer* Game::get_audio_player() const {
	return audio_player_;
}

Gameplay* Game::get_gameplay() const {
	return gameplay_;
}

long long Game::GetMS() const {
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);
	return ms.count();
}

void Game::Launch() {
	Initialize();
	state_ = kStateIntro;
	UserActionInfo uai;
	while (state_ != kStateOffline) {
		// Interacting.
		while (window_->GetAction(uai)) {
			if (uai.ua == kCloseWindow) {
				// Закрытие игры.
				Exit();
			} else if ((uai.ua == kEsc) && (uai.uat == kUserActionPressed)) {
				// Переключения Меню <-> Игра.
				if (state_ == kStatePlaying)
					Pause();
				else if (state_ == kStatePaused)
					Continue();
			} else {
				// Взаимодействие с игрой и UI.
				if (state_ == kStatePlaying)
					gameplay_->ProcessUserAction(uai);
				ui_->ProcessUserAction(uai);
			}
		}

		// Updating.
		if (state_ == kStatePlaying)
			gameplay_->Update(GetMS());
		ui_->Update();

		// Drawing.
		window_->Clear();
		if (state_ == kStatePlaying)
			gameplay_->Draw(window_);
		ui_->Draw(window_);
		window_->Display();
	}
	Finalize();
}

void Game::FatalError() {
	std::cerr << "... => FATAL ERROR" << std::endl;
	Exit();
}

void Game::Pause() {
	ui_->SwitchToGameMenu();
	state_ = kStatePaused;
}

void Game::Continue() {
	gameplay_->set_last_update(GetMS());
	ui_->SwitchToPlaying();
	state_ = kStatePlaying;
}

void Game::NewMap() {
	// Экран загрузки.
	window_->Clear();
	window_->DrawTexture(Point2DInt(0, 0), Point2DInt(settings_->get_window_width(), settings_->get_window_height()), "ui/ui_loading.png");
	window_->Display();

	// Создание и загрузка новой карты.
	gameplay_->NewMap();
	gameplay_->set_last_update(GetMS());
	audio_player_->StopAll();
	ui_->SwitchToPlaying();
	state_ = kStatePlaying;
}

void Game::LoadMap(const std::string& map_path) {
	// Экран загрузки.
	window_->Clear();
	window_->DrawTexture(Point2DInt(0, 0), Point2DInt(settings_->get_window_width(), settings_->get_window_height()), "ui/ui_loading.png");
	window_->Display();

	// Загрузка карты.
	gameplay_->LoadMap(map_path);
	gameplay_->set_last_update(GetMS());
	audio_player_->StopAll();
	ui_->SwitchToPlaying();
	state_ = kStatePlaying;
}

void Game::Save() {
	// Экран сохранения.
	window_->Clear();
	window_->DrawTexture(Point2DInt(0, 0), Point2DInt(settings_->get_window_width(), settings_->get_window_height()), "ui/ui_saving.png");
	window_->Display();

	// Сохранение.
	gameplay_->SaveMap();
}

void Game::Halt() {
	gameplay_->Halt();
	audio_player_->StopAll();
	ui_->SwitchToStartMenu();
	state_ = kStateIntro;
}

void Game::Exit() {
	state_ = kStateOffline;
}

void Game::Initialize() {
    // Check settings_.
    if (settings_ == nullptr) {
        std::cerr << "[ERROR] Can't initialize the game having no settings." << std::endl;
        FatalError();
        return;
    }
    
	// window_ & audio_player_
	Tools_SFML tools;
	window_ = tools.CreateWindow(settings_->get_window_width(), settings_->get_window_height(), settings_->get_game_name());
	audio_player_ = tools.CreateAudioPlayer();

	// Экран загрузки.
	window_->Clear();
	window_->DrawTexture(Point2DInt(0, 0), Point2DInt(settings_->get_window_width(), settings_->get_window_height()), "ui/ui_loading.png");
	window_->Display();
	
	// ui_
	ui_ = new UIHolder();

	// gameplay_
	gameplay_ = new Gameplay();

	// GameplayConfigs (предзагрузка).
	GameplayConfigs* gameplay_configs = GameplayConfigs::Instance();
}

void Game::Finalize() {
	audio_player_->StopAll();
	window_->Close();

	delete gameplay_;
	gameplay_ = nullptr;
	delete ui_;
	ui_ = nullptr;
	delete audio_player_;
	audio_player_ = nullptr;
	delete window_;
	window_ = nullptr;
	delete settings_;
	settings_ = nullptr;
}
