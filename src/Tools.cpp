#include <DiggerOffline/Tools.h>
#include <DiggerOffline/Game.h>

void Window::DrawTexture(const Point2DInt& pos, const Point2DInt& size, const std::string& texture_path) {
	Game* game = Game::Instance();
	std::string full_path = game->kGamedata + "textures/" + texture_path;
	if (!DrawTextureFullPath(pos, size, full_path)) {
		std::cerr << "[ERROR] Can't draw texture \"" << texture_path << "\"." << std::endl;
		game->FatalError();
	}
}

void Window::DrawText(const std::string& text, const std::string& font_path, int size, const Color& color, const Point2DInt& pos,
	AlignmentX alignment_x, AlignmentY alignment_y) {
	Game* game = Game::Instance();
	std::string full_path = game->kGamedata + "fonts/" + font_path;
	if (!DrawTextFullPath(text, full_path, size, color, pos, alignment_x, alignment_y)) {
		std::cerr << "[ERROR] Can't draw text with font \"" << font_path << "\"." << std::endl;
		game->FatalError();
	}
}


void AudioPlayer::Play(const std::string& sound_path, bool interrupt) {
	Game* game = Game::Instance();
    float volume = game->get_settings()->get_sounds_volume();
	std::string full_path = game->kGamedata + "sounds/" + sound_path;
	if (!PlayFullPath(full_path, interrupt, volume)) {
		std::cerr << "[ERROR] Can't play sound \"" << sound_path << "\"." << std::endl;
		game->FatalError();
	}
}
