#pragma once
#include <DiggerOffline/Tools.h>
#include <DiggerOffline/GameSettings.h>
#include <DiggerOffline/UIHolder.h>
#include <DiggerOffline/Gameplay.h>

enum GameState {
	kStateOffline,
	kStateIntro,
	kStatePlaying,
	kStatePaused
};

class Game {
public:
	~Game();
	static Game* Instance();

	const std::string kGamedata = "../../gamedata/";
	const std::string kGamemaps = "../../gamemaps/";
	UIHolder* get_ui() const;
	const GameSettings* get_settings() const;
	AudioPlayer* get_audio_player() const;
	Gameplay* get_gameplay() const;

	long long GetMS() const;
	void Launch();
	void FatalError();
	void Pause();
	void Continue();
	void NewMap();
	void LoadMap(const std::string& map_path);
	void Save();
	void Halt();
	void Exit();

protected:
	Game();

private:
	void Initialize();
	void Finalize();

	static Game* instance_;
	GameSettings* settings_;
	Window* window_;
	AudioPlayer* audio_player_;
	UIHolder* ui_;
	Gameplay* gameplay_;
	GameState state_;
};
