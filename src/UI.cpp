#include <DiggerOffline/UI.h>
#include <DiggerOffline/Game.h>
#include <fstream>
#include <vector>


UI::UI() : parent_(nullptr) {}

UI::~UI() {
	parent_ = nullptr;
	while (ui_elements_.size() > 0) {
		UIElement* ui_element = ui_elements_.back();
		delete ui_element;
		ui_elements_.pop_back();
	}
}

void UI::Draw(Window* window) const {
	for (std::vector<UIElement*>::const_iterator it = ui_elements_.begin(); it != ui_elements_.end(); ++it) {
		(*it)->Draw(window);
	}
}

void UI::ProcessUserAction(UserActionInfo uai) {
	for (std::vector<UIElement*>::iterator it = ui_elements_.begin(); it != ui_elements_.end(); ++it) {
		(*it)->ProcessUserAction(uai);
	}
}


UIStartMenu::UIStartMenu() {
	Game* game = Game::Instance();
	std::string json_path = game->kGamedata + "config/ui/ui_StartMenu.json";

	// Чтение данных.
	nlohmann::json json_ui;
	std::ifstream ifs(json_path);
	if (!ifs.is_open()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Can't open \"" << json_path << "\"" << std::endl;
		game->FatalError();
		return;
	}
	ifs >> json_ui;
	ifs.close();

	// Проверка наличия нужных данных.
	std::vector<std::string> fields = {
		"background",
		"sound",
		"btn_play",
		"btn_exit"
	};
	for (std::vector<std::string>::iterator it = fields.begin(); it != fields.end(); ++it)
		if (json_ui.find(*it) == json_ui.end()) {
			std::cerr << "[FATAL ERROR]" << std::endl;
			std::cerr << "    UI file \"" << json_path << "\" doesn't have mandatory field \"" << *it << "\"." << std::endl;
			game->FatalError();
			return;
		}

	// Инициализация данных.
	background_ = json_ui["background"].get<std::string>();
	sound_ = json_ui["sound"].get<std::string>();

	UIButton* btn_play = new UIButton(new Action_OpenMapMenu());
	btn_play->Initialize("btn_play", json_ui["btn_play"]);
	ui_elements_.push_back(btn_play);

	UIButton* btn_exit = new UIButton(new Action_Exit());
	btn_exit->Initialize("btn_exit", json_ui["btn_exit"]);
	ui_elements_.push_back(btn_exit);
}

void UIStartMenu::Draw(Window* window) const {
	// Отрисовка background.
	Game* game = Game::Instance();
	Point2DInt pos(0, 0);
	Point2DInt size(game->get_settings()->get_window_width(), game->get_settings()->get_window_height());
	window->DrawTexture(pos, size, background_);

	// Всё остальное.
	UI::Draw(window);
}

void UIStartMenu::OnLoad() {
	Action_PlaySound action(sound_, false);
	action.Act();
}


UIGameMenu::UIGameMenu() {
	Game* game = Game::Instance();
	std::string json_path = game->kGamedata + "config/ui/ui_GameMenu.json";

	// Чтение данных.
	nlohmann::json json_ui;
	std::ifstream ifs(json_path);
	if (!ifs.is_open()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Can't open \"" << json_path << "\"" << std::endl;
		game->FatalError();
		return;
	}
	ifs >> json_ui;
	ifs.close();

	// Проверка наличия нужных данных.
	std::vector<std::string> fields = {
		"background",
		"btn_continue",
		"btn_save",
		"btn_halt",
		"btn_exit"
	};
	for (std::vector<std::string>::iterator it = fields.begin(); it != fields.end(); ++it)
		if (json_ui.find(*it) == json_ui.end()) {
			std::cerr << "[FATAL ERROR]" << std::endl;
			std::cerr << "    UI file \"" << json_path << "\" doesn't have mandatory field \"" << *it << "\"." << std::endl;
			game->FatalError();
			return;
		}

	// Инициализация данных.
	background_ = json_ui["background"].get<std::string>();

	UIButton* btn_continue = new UIButton(new Action_Continue());
	btn_continue->Initialize("btn_continue", json_ui["btn_continue"]);
	ui_elements_.push_back(btn_continue);

	UIButton* btn_save = new UIButton(new Action_Save());
	btn_save->Initialize("btn_save", json_ui["btn_save"]);
	ui_elements_.push_back(btn_save);

	UIButton* btn_halt = new UIButton(new Action_Halt());
	btn_halt->Initialize("btn_halt", json_ui["btn_halt"]);
	ui_elements_.push_back(btn_halt);

	UIButton* btn_exit = new UIButton(new Action_Exit());
	btn_exit->Initialize("btn_exit", json_ui["btn_exit"]);
	ui_elements_.push_back(btn_exit);
}

void UIGameMenu::Draw(Window* window) const {
	// Отрисовка background.
	Game* game = Game::Instance();
	Point2DInt pos(0, 0);
	Point2DInt size(game->get_settings()->get_window_width(), game->get_settings()->get_window_height());
	window->DrawTexture(pos, size, background_);

	// Всё остальное.
	UI::Draw(window);
}


UIMapMenu::UIMapMenu() {
	Game* game = Game::Instance();
	std::string json_path = game->kGamedata + "config/ui/ui_MapMenu.json";

	// Чтение данных.
	nlohmann::json json_ui;
	std::ifstream ifs(json_path);
	if (!ifs.is_open()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Can't open \"" << json_path << "\"" << std::endl;
		game->FatalError();
		return;
	}
	ifs >> json_ui;
	ifs.close();

	// Проверка наличия нужных данных.
	std::vector<std::string> fields = {
		"background",
		"btn_back",
		"btn_new_map",
		"btn_map"
	};
	for (std::vector<std::string>::iterator it = fields.begin(); it != fields.end(); ++it)
		if (json_ui.find(*it) == json_ui.end()) {
			std::cerr << "[FATAL ERROR]" << std::endl;
			std::cerr << "    UI file \"" << json_path << "\" doesn't have mandatory field \"" << *it << "\"." << std::endl;
			game->FatalError();
			return;
		}

	// Инициализация данных.
	background_ = json_ui["background"].get<std::string>();

	UIButton* btn_back = new UIButton(new Action_Back());
	btn_back->Initialize("btn_back", json_ui["btn_back"]);
	ui_elements_.push_back(btn_back);

	UIButton* btn_new_map = new UIButton(new Action_NewMap());
	btn_new_map->Initialize("btn_new_map", json_ui["btn_new_map"]);
	ui_elements_.push_back(btn_new_map);

	json_btn_map_ = json_ui["btn_map"];
}

void UIMapMenu::Draw(Window* window) const {
	// Отрисовка background.
	Game* game = Game::Instance();
	Point2DInt pos(0, 0);
	Point2DInt size(game->get_settings()->get_window_width(), game->get_settings()->get_window_height());
	window->DrawTexture(pos, size, background_);

	// Всё остальное.
	UI::Draw(window);
}

void UIMapMenu::OnLoad() {
	UpdateMapButtons();
}


void UIMapMenu::UpdateMapButtons() {
	// Избавляемся от старых кнопок-карт.
	for (std::vector<UIElement*>::iterator it = ui_elements_.begin(); it != ui_elements_.end(); ) {
		UIElement* ui_element = *it;
		if (ui_element->get_id() == "btn_map") {
			delete ui_element;
			it = ui_elements_.erase(it);
		} else {
			++it;
		}
	}
    
    // Извлекаем список карт.
	Game* game = Game::Instance();
    bool update_required = false;
    const std::string maps_list_path = game->kGamemaps + "GameMapsList";
    typedef std::vector<std::string> MapsList;
    MapsList maps_list;
	std::string map_name;
	std::ifstream maps_list_ifs(maps_list_path);
	while (maps_list_ifs >> map_name) {
        std::ifstream ifs(game->kGamemaps + map_name);
        if (!ifs.fail())
            maps_list.push_back(map_name);
        else
            update_required = true;
        ifs.close();
	}
    maps_list_ifs.close();
    
    // Обновляем список карт.
    if (update_required) {
        std::ofstream maps_list_ofs(maps_list_path, std::ios_base::trunc);
        for (MapsList::iterator it = maps_list.begin(); it != maps_list.end(); ++it)
            maps_list_ofs << *it << std::endl;
        maps_list_ofs.close();
    }

	// Добавляем новые кнопки-карты.
	int btn_n = 0;
    for (MapsList::iterator it = maps_list.begin(); it != maps_list.end(); ++it) {
        map_name = *it;
		UIButton* btn_map = new UIButton(new Action_LoadMap(game->kGamemaps + map_name));
		nlohmann::json json_btn_map = json_btn_map_;
		std::vector<int> position = json_btn_map["position"];
		position[1] += (btn_n++) * ((json_btn_map["size"][1].get<int>()) * 3 / 2);
		json_btn_map["position"] = position;
		json_btn_map["text"] = map_name;
		btn_map->Initialize("btn_map", json_btn_map);
		ui_elements_.push_back(btn_map);
	}
}


UIPlaying::UIPlaying() {
	Game* game = Game::Instance();
	std::string json_path = game->kGamedata + "config/ui/ui_Playing.json";

	// Чтение данных.
	nlohmann::json json_ui;
	std::ifstream ifs(json_path);
	if (!ifs.is_open()) {
		std::cerr << "[FATAL ERROR]" << std::endl;
		std::cerr << "    Can't open \"" << json_path << "\"" << std::endl;
		game->FatalError();
		return;
	}
	ifs >> json_ui;
	ifs.close();

	// Проверка наличия нужных данных.
	std::vector<std::string> fields = {
		"sound"
	};
	for (std::vector<std::string>::iterator it = fields.begin(); it != fields.end(); ++it)
		if (json_ui.find(*it) == json_ui.end()) {
			std::cerr << "[FATAL ERROR]" << std::endl;
			std::cerr << "    UI file \"" << json_path << "\" doesn't have mandatory field \"" << *it << "\"." << std::endl;
			game->FatalError();
			return;
		}

	// Инициализация данных.
	sound_ = json_ui["sound"].get<std::string>();
}

void UIPlaying::OnLoad() {
	Action_PlaySound action(sound_, false);
	action.Act();
}

void UIPlaying::Update() {
	// TODO

}

