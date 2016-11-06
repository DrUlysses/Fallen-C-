#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include <map>

// Класс экрана объявлен для того, чтобы можно было использовать перекрёстное объявление:
// В классе приложения хранится указатель на экран, в классе экрана - ссылка на приложение
class Screen;

// Класс, представляющий приложение и все его данные
class Application : public sf::RenderWindow
{
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Image> images;
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, sf::Music*> music;

	Screen* screen;
	Screen* lastScreen;
	bool lastError;
	bool running;

public:

	Application(const int& width = 640, const int& height = 480, const char* title = "SFML_Application");
	~Application();

	// Запускает основной цикл приложения
	int Run();

	// Останавливает приложение
	void Stop();

	// Задаёт экран для текущего отображения
	void SetScreen(Screen* screen, bool deleteLastScreen = true);

	// Получение текстур
	sf::Texture& getTexture(const std::string& filename);
	sf::Texture& getLogoTexture();
	sf::Texture& getScreenTexture();
	sf::Texture& getButtonTexture();
	sf::Texture& getTextBoxTexture();

	// Получение пиксельных данных текстур
	sf::Image& getImage(const std::string& filename);

	// Получение шрифтов
	sf::Font& getFont(const std::string& filename);
	sf::Font& getButtonFont();

	// Получение буферов звуков
	sf::SoundBuffer& getSoundBuffer(const std::string& filename);
	sf::SoundBuffer& getSoundBuffer(const std::string& filename, bool& result);
	sf::SoundBuffer& getFocusChangedSB();
	sf::SoundBuffer& getTextEnteredSB();
	sf::SoundBuffer& getButtonPressedSB();

	// Получение готовых звуков
	sf::Sound& getSound(const std::string& filename);
	sf::Sound& getFocusChangedSound();
	sf::Sound& getTextEnteredSound();
	sf::Sound& getButtonPressedSound();

	// Проигрывание готовых звуков
	void PlaySound(const std::string& filename);
	void PlayFocusChangedSound();
	void PlayTextEnteredSound();
	void PlayButtonPressedSound();

	// Получение музыки
	sf::Music* getMusic(const std::string& filename);

	// Получает разрешение экрана по ширине
	float getWidth() const;

	// Получает разрешение экрана по высоте
	float getHeight() const;
};

#endif