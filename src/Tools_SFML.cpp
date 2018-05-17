#include <DiggerOffline/Tools_SFML.h>

Window* Tools_SFML::CreateWindow(int width, int height, const std::string& game_name) {
	return new Window_SFML(width, height, game_name);
}

AudioPlayer* Tools_SFML::CreateAudioPlayer() {
	return new AudioPlayer_SFML();
}


Window_SFML::Window_SFML(int width, int height, const std::string& game_name) {
	window_.create(sf::VideoMode(width, height), game_name, sf::Style::Close);
}

Window_SFML::~Window_SFML() {
	for (sfStorageTexturesMap::iterator it = storage_textures_.begin(); it != storage_textures_.end(); ++it)
		delete it->second;
	storage_textures_.clear();
	for (sfStorageFontsMap::iterator it = storage_fonts_.begin(); it != storage_fonts_.end(); ++it)
		delete it->second;
	storage_fonts_.clear();
}

void Window_SFML::Close() {
	window_.close();
}

void Window_SFML::Clear() {
	window_.clear();
}

void Window_SFML::Display() {
	window_.display();
}

bool Window_SFML::GetAction(UserActionInfo& uai) {
	if (window_.pollEvent(sf_event_)) {
		if (sf_event_.type == sf::Event::Closed) {
			uai.ua = kCloseWindow;
			return true;
		}
		if (sf_event_.type == sf::Event::MouseButtonPressed) {
			switch (sf_event_.mouseButton.button) {
			case sf::Mouse::Button::Left:
				uai.ua = kMouseClickLeft;
				break;
			case sf::Mouse::Button::Right:
				uai.ua = kMouseClickRight;
				break;
			default:
				return false;
			}
			uai.x = sf_event_.mouseButton.x;
			uai.y = sf_event_.mouseButton.y;
			return true;
		}
		if ((sf_event_.type == sf::Event::KeyPressed) || (sf_event_.type == sf::Event::KeyReleased)) {
			if (sf_event_.type == sf::Event::KeyPressed)
				uai.uat = kUserActionPressed;
			if (sf_event_.type == sf::Event::KeyReleased)
				uai.uat = kUserActionReleased;

			switch (sf_event_.key.code) {
			case sf::Keyboard::Key::Escape:
				uai.ua = kEsc;
				break;
			case sf::Keyboard::Key::LControl:
				uai.ua = kLCtrl;
				break;
			case sf::Keyboard::Key::LShift:
				uai.ua = kLShift;
				break;
			case sf::Keyboard::Key::LAlt:
				uai.ua = kLAlt;
				break;
			case sf::Keyboard::Key::RControl:
				uai.ua = kRCtrl;
				break;
			case sf::Keyboard::Key::RShift:
				uai.ua = kRShift;
				break;
			case sf::Keyboard::Key::RAlt:
				uai.ua = kRAlt;
				break;
			case sf::Keyboard::Key::Space:
				uai.ua = kSpace;
				break;
			case sf::Keyboard::Key::Q:
				uai.ua = kQ;
				break;
			case sf::Keyboard::Key::W:
				uai.ua = kW;
				break;
			case sf::Keyboard::Key::E:
				uai.ua = kE;
				break;
			case sf::Keyboard::Key::R:
				uai.ua = kR;
				break;
			case sf::Keyboard::Key::T:
				uai.ua = kT;
				break;
			case sf::Keyboard::Key::Y:
				uai.ua = kY;
				break;
			case sf::Keyboard::Key::U:
				uai.ua = kU;
				break;
			case sf::Keyboard::Key::I:
				uai.ua = kI;
				break;
			case sf::Keyboard::Key::O:
				uai.ua = kO;
				break;
			case sf::Keyboard::Key::P:
				uai.ua = kP;
				break;
			case sf::Keyboard::Key::A:
				uai.ua = kA;
				break;
			case sf::Keyboard::Key::S:
				uai.ua = kS;
				break;
			case sf::Keyboard::Key::D:
				uai.ua = kD;
				break;
			case sf::Keyboard::Key::F:
				uai.ua = kF;
				break;
			case sf::Keyboard::Key::G:
				uai.ua = kG;
				break;
			case sf::Keyboard::Key::H:
				uai.ua = kH;
				break;
			case sf::Keyboard::Key::J:
				uai.ua = kJ;
				break;
			case sf::Keyboard::Key::K:
				uai.ua = kK;
				break;
			case sf::Keyboard::Key::L:
				uai.ua = kL;
				break;
			case sf::Keyboard::Key::Z:
				uai.ua = kZ;
				break;
			case sf::Keyboard::Key::X:
				uai.ua = kX;
				break;
			case sf::Keyboard::Key::C:
				uai.ua = kC;
				break;
			case sf::Keyboard::Key::V:
				uai.ua = kV;
				break;
			case sf::Keyboard::Key::B:
				uai.ua = kB;
				break;
			case sf::Keyboard::Key::N:
				uai.ua = kN;
				break;
			case sf::Keyboard::Key::M:
				uai.ua = kM;
				break;
			default:
				return false;
			}
			uai.x = sf::Mouse::getPosition(window_).x;
			uai.y = sf::Mouse::getPosition(window_).y;
			return true;
		}
	}
	return false;
}

bool Window_SFML::DrawTextureFullPath(const Point2DInt& pos, const Point2DInt& size, const std::string& texture_path) {
	sf::Texture* sf_texture = get_texture(texture_path);
	if (sf_texture == nullptr)
		return false;
	sf::Sprite sprite(*sf_texture);
	sprite.setPosition((float)pos.x, (float)pos.y);
	sf::Vector2u sf_texture_size = sf_texture->getSize();
	sprite.setScale((float)size.x / (float)sf_texture_size.x, (float)size.y / (float)sf_texture_size.y);
	window_.draw(sprite);
	return true;
}

bool Window_SFML::DrawTextFullPath(const std::string& text, const std::string& font_path, int size, const Color& color, const Point2DInt& pos, 
	AlignmentX alignment_x, AlignmentY alignment_y) {
	sf::Font* sf_font = get_font(font_path);
	if (sf_font == nullptr)
		return false;
	sf::Text sf_text;
	sf_text.setString(text);
	sf_text.setFont(*sf_font);
	sf_text.setCharacterSize(size);
	sf_text.setFillColor(sf::Color(color.get_r(), color.get_g(), color.get_b(), color.get_a()));

	// Определение позиции (в зависимости от pos, alignment_x, alignment_y).
	float x = (float)pos.x;
	float y = (float)pos.y;
	sf::FloatRect sf_bounds = sf_text.getGlobalBounds();
	if (alignment_x == kRightX)
		x -= sf_bounds.width;
	else if (alignment_x == kCenterX)
		x -= sf_bounds.width / 2;
	if (alignment_y == kBottomY)
		y -= sf_bounds.height;
	else if (alignment_y == kCenterY)
		y -= sf_bounds.height / 2;
	sf_text.setPosition(x, y);

	window_.draw(sf_text);
	return true;
}

sf::Texture* Window_SFML::get_texture(const std::string& texture_path) {
	sfStorageTexturesMap::iterator it = storage_textures_.find(texture_path);
	if (it != storage_textures_.end())
		return it->second;
	sf::Texture* sf_texture = new sf::Texture();
	if (!sf_texture->loadFromFile(texture_path)) {
		delete sf_texture;
		return nullptr;
	}
	storage_textures_[texture_path] = sf_texture;
	return sf_texture;
}

sf::Font* Window_SFML::get_font(const std::string& font_path) {
	sfStorageFontsMap::iterator it = storage_fonts_.find(font_path);
	if (it != storage_fonts_.end())
		return it->second;
	sf::Font* sf_font = new sf::Font();
	if (!sf_font->loadFromFile(font_path)) {
		delete sf_font;
		return nullptr;
	}
	storage_fonts_[font_path] = sf_font;
	return sf_font;
}


AudioPlayer_SFML::~AudioPlayer_SFML() {
	for (sfStorageSoundsMap::iterator it = storage_sounds_.begin(); it != storage_sounds_.end(); ++it) {
		delete it->second.player;
		delete it->second.sound;
	}
	storage_sounds_.clear();
}

void AudioPlayer_SFML::Stop(const std::string& sound_path) {
	sfStorageSoundsMap::iterator it = storage_sounds_.find(sound_path);
	if (it != storage_sounds_.end())
		it->second.player->stop();
}

void AudioPlayer_SFML::StopAll() {
	for (sfStorageSoundsMap::iterator it = storage_sounds_.begin(); it != storage_sounds_.end(); ++it) {
		it->second.player->stop();
	}
}

bool AudioPlayer_SFML::PlayFullPath(const std::string& sound_path, bool interrupt, float volume) {
	sfStorageSoundsMap::iterator it = storage_sounds_.find(sound_path);
	if (it != storage_sounds_.end()) {
        it->second.player->setVolume(volume);
		if ((interrupt) || (it->second.player->getStatus() != sf::SoundSource::Status::Playing))
			it->second.player->play();
		return true;
	}
	SoundPack pack;
	pack.sound = new sf::SoundBuffer();
	if (!pack.sound->loadFromFile(sound_path)) {
		delete pack.sound;
		return false;
	}
	pack.player = new sf::Sound();
	pack.player->setBuffer(*pack.sound);
    pack.player->setVolume(volume);
	storage_sounds_[sound_path] = pack;
	pack.player->play();
	return true;
}
