#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include <map>

// ����� ������ �������� ��� ����, ����� ����� ���� ������������ ����������� ����������:
// � ������ ���������� �������� ��������� �� �����, � ������ ������ - ������ �� ����������
class Screen;

// �����, �������������� ���������� � ��� ��� ������
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

	// ��������� �������� ���� ����������
	int Run();

	// ������������� ����������
	void Stop();

	// ����� ����� ��� �������� �����������
	void SetScreen(Screen* screen, bool deleteLastScreen = true);

	// ��������� �������
	sf::Texture& getTexture(const std::string& filename);
	sf::Texture& getLogoTexture();
	sf::Texture& getScreenTexture();
	sf::Texture& getButtonTexture();
	sf::Texture& getTextBoxTexture();

	// ��������� ���������� ������ �������
	sf::Image& getImage(const std::string& filename);

	// ��������� �������
	sf::Font& getFont(const std::string& filename);
	sf::Font& getButtonFont();

	// ��������� ������� ������
	sf::SoundBuffer& getSoundBuffer(const std::string& filename);
	sf::SoundBuffer& getSoundBuffer(const std::string& filename, bool& result);
	sf::SoundBuffer& getFocusChangedSB();
	sf::SoundBuffer& getTextEnteredSB();
	sf::SoundBuffer& getButtonPressedSB();

	// ��������� ������� ������
	sf::Sound& getSound(const std::string& filename);
	sf::Sound& getFocusChangedSound();
	sf::Sound& getTextEnteredSound();
	sf::Sound& getButtonPressedSound();

	// ������������ ������� ������
	void PlaySound(const std::string& filename);
	void PlayFocusChangedSound();
	void PlayTextEnteredSound();
	void PlayButtonPressedSound();

	// ��������� ������
	sf::Music* getMusic(const std::string& filename);

	// �������� ���������� ������ �� ������
	float getWidth() const;

	// �������� ���������� ������ �� ������
	float getHeight() const;
};

#endif