#pragma once
#include <DiggerOffline/Tools.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

struct SoundPack {
	sf::SoundBuffer* sound = nullptr;
	sf::Sound* player = nullptr;
};

typedef std::map<std::string, sf::Texture*> sfStorageTexturesMap;
typedef std::map<std::string, sf::Font*> sfStorageFontsMap;
typedef std::map<std::string, SoundPack> sfStorageSoundsMap;

class Tools_SFML : public Tools {
public:
	Window* CreateWindow(int width, int height, const std::string& game_name);
	AudioPlayer* CreateAudioPlayer();
};

class Window_SFML : public Window {
public:
	Window_SFML(int width, int height, const std::string& game_name);
	~Window_SFML();

	void Close();
	void Clear();
	void Display();
	bool GetAction(UserActionInfo& uai);

protected:
	bool DrawTextureFullPath(const Point2DInt& pos, const Point2DInt& size, const std::string& texture_path);
	bool DrawTextFullPath(const std::string& text, const std::string& font_path, int size, const Color& color, const Point2DInt& pos,
		AlignmentX alignment_x, AlignmentY alignment_y);

private:
	sf::RenderWindow window_;
	sf::Event sf_event_;
	sfStorageTexturesMap storage_textures_;
	sfStorageFontsMap storage_fonts_;

	// Возвращает текстуру из хранилища.
	// Если указанной текстуры там не было, то автоматически загружает её.
	// Если загрузка не удалась, то возвращает nullptr.
	sf::Texture* get_texture(const std::string& texture_path);
	// Возвращает шрифт из хранилища.
	// Если указанного шрифта там не было, то автоматически загружает его.
	// Если загрузка не удалась, то возвращает nullptr.
	sf::Font* get_font(const std::string& font_path);
};

class AudioPlayer_SFML : public AudioPlayer {
public:
	~AudioPlayer_SFML();

	void Stop(const std::string& sound_path);
	void StopAll();

protected:
	bool PlayFullPath(const std::string& sound_path, bool interrupt, float volume);

private:
	sfStorageSoundsMap storage_sounds_;
};
