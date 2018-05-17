#include <DiggerOffline/Action.h>
#include <DiggerOffline/Game.h>

ActionMacro::~ActionMacro() {
	Action* action;
	while (actions_.size() > 0) {
		action = actions_.back();
		delete action;
		actions_.pop_back();
	}
}

void ActionMacro::Act() {
	for (std::vector<Action*>::iterator it = actions_.begin(); it != actions_.end(); ++it) {
		(*it)->Act();
	}
}

void ActionMacro::AddAction(Action* action) {
	actions_.push_back(action);
}


void Action_OpenMapMenu::Act() {
	Game* game = Game::Instance();
	game->get_ui()->SwitchToMapMenu();
}

void Action_Exit::Act() {
	Game* game = Game::Instance();
	game->Exit();
}

Action_LoadMap::Action_LoadMap(const std::string& map_path) : map_path_(map_path) {}

void Action_LoadMap::Act() {
	Game* game = Game::Instance();
	game->LoadMap(map_path_);
}

void Action_Back::Act() {
	Game* game = Game::Instance();
	game->get_ui()->Back();
}

void Action_Save::Act() {
	Game* game = Game::Instance();
	game->Save();
}

void Action_Continue::Act() {
	Game* game = Game::Instance();
	game->Continue();
}

void Action_Halt::Act() {
	Game* game = Game::Instance();
	game->Halt();
}

Action_PlaySound::Action_PlaySound(const std::string& sound_path, bool interrupt) : sound_path_(sound_path), interrupt_(interrupt) {}

void Action_PlaySound::Act() {
	Game* game = Game::Instance();
	game->get_audio_player()->Play(sound_path_, interrupt_);
}

Action_StopSound::Action_StopSound(const std::string& sound_path) : sound_path_(sound_path) {}

void Action_StopSound::Act() {
	Game* game = Game::Instance();
	game->get_audio_player()->Stop(sound_path_);
}

void Action_NewMap::Act() {
	Game* game = Game::Instance();
	game->NewMap();
}
