#include "Application.hpp"
#include "GuiScreenStartup.hpp"
#include <iostream>

Application::Application(const int& width, const int& height, const char* title) : sf::RenderWindow(sf::VideoMode(width, height, 32), title)
{
	screen = 0;
	lastScreen = 0;
	lastError = false;
	running = true;
}

Application::~Application() 
{
	if(screen) 
	{
		delete screen;
	}

	screen = 0;

	if(lastScreen)
	{
		delete lastScreen;
	}

	lastScreen = 0;
}

int Application::Run()
{
	// Убираем отображение мыши
	setMouseCursorVisible(false);

	// Загрузка текстур
	getScreenTexture().setRepeated(true);
	getButtonTexture();
	getTextBoxTexture();
	getButtonFont();

	// Загрузка звуков
	getFocusChangedSound();
	getTextEnteredSound();

	// Если хотя бы одна текстура не загрузилась, то закрываем приложение
	if(lastError)
	{
		running = false;
	}

	// Задаём экран "Startup" как текущий
	screen = new GuiScreenStartup(*this);

	// Основной цикл приложения
	sf::Event event;
	sf::Clock clock;
	sf::Time time;

	while(running)
	{
		clock.restart();

		// Обработка событий окна
		while(pollEvent(event))
		{
			if(screen)
			{
				screen->Handle(event);
			}

			if(event.type == sf::Event::Closed)
			{
				goto Completion;
			}
		}		

		// Пустое событие для выполнения различного рода обновлений, не связанных с событиями окна
		event.type = sf::Event::Count;

		screen->Handle(event);
		
		// Рендеринг окна
		clear();

		if(screen)
		{
			screen->Draw(time);
		}

		display();

		// Освобождаем память выделенную под предыдущий экран
		if(lastScreen) 
		{
			delete lastScreen;
			lastScreen = 0;
		}

		time = clock.getElapsedTime();
	}

Completion:

	running = false;

	// Остановка всех проигрывающихся звуков
	std::map<std::string, sf::Sound>::iterator sIt;

	for(sIt = sounds.begin(); sIt != sounds.end(); ++sIt)
	{
		sIt->second.stop();
	}

	// Остановка всей проигрывающейся музыки
	std::map<std::string, sf::Music*>::iterator mIt;

	for(mIt = music.begin(); mIt != music.end(); ++mIt)
	{
		mIt->second->stop();
	}

	close();

	return 0;
}

void Application::Stop()
{
	running = false;
}

void Application::SetScreen(Screen* screen, bool deleteLastScreen)
{
	if(deleteLastScreen)
	{
		lastScreen = this->screen;
	}

	this->screen = screen;
}

sf::Texture& Application::getTexture(const std::string& filename)
{
	std::map<std::string, sf::Texture>::iterator it = textures.find(filename);

	if(it != textures.end())
	{
		return it->second;
	}

	sf::Texture texture;

	if(!texture.loadFromFile(filename))
	{
		lastError = true;
	}

	textures[filename] = texture;

	// Копируем пиксельные данные этой текстуры
	images[filename] = texture.copyToImage();

	return textures[filename];
}

sf::Texture& Application::getLogoTexture()
{
	return getTexture("media\\logo.png");
}

sf::Texture& Application::getScreenTexture()
{
	return getTexture("media\\screen.png");
}

sf::Texture& Application::getButtonTexture()
{
	return getTexture("media\\button.png");
}

sf::Texture& Application::getTextBoxTexture()
{
	return getTexture("media\\textbox.png");
}

sf::Image& Application::getImage(const std::string& filename)
{
	std::map<std::string, sf::Image>::iterator it = images.find(filename);

	if(it != images.end())
	{
		return it->second;
	}

	// При загрузке текстуры пиксельные данные автоматически добавятся в список
	getTexture(filename);

	return images[filename];
}

sf::Font& Application::getFont(const std::string& filename)
{
	std::map<std::string, sf::Font>::iterator it = fonts.find(filename);

	if(it != fonts.end())
	{
		return it->second;
	}

	sf::Font font;

	if(!font.loadFromFile(filename))
	{
		lastError = true;
	}

	fonts[filename] = font;

	return fonts[filename];
}

sf::Font& Application::getButtonFont()
{
	return getFont("media\\font.otf");
}

sf::SoundBuffer& Application::getSoundBuffer(const std::string& filename)
{
	bool result = false;

	sf::SoundBuffer& soundBuffer = getSoundBuffer(filename, result);

	if(!result)
	{
		lastError = true;
	}

	return soundBuffer;
}

sf::SoundBuffer& Application::getSoundBuffer(const std::string& filename, bool& result)
{
	std::map<std::string, sf::SoundBuffer>::iterator it = soundBuffers.find(filename);

	if(it != soundBuffers.end())
	{
		result = true;

		return it->second;
	}

	sf::SoundBuffer soundBuffer;

	if(!soundBuffer.loadFromFile(filename))
	{
		result = false;
	}
	else
	{
		result = true;
	}

	soundBuffers[filename] = soundBuffer;

	return soundBuffers[filename];
}

sf::SoundBuffer& Application::getFocusChangedSB()
{
	return getSoundBuffer("media\\focusChanged.wav");
}

sf::SoundBuffer& Application::getTextEnteredSB()
{
	return getSoundBuffer("media\\textEntered.wav");
}

sf::SoundBuffer& Application::getButtonPressedSB()
{
	return getSoundBuffer("media\\buttonPressed.wav");
}

sf::Sound& Application::getSound(const std::string& filename)
{
	std::map<std::string, sf::Sound>::iterator it = sounds.find(filename);

	if(it != sounds.end())
	{
		return it->second;
	}

	bool result = false;

	sf::SoundBuffer& soundBuffer = getSoundBuffer(filename, result);

	if(!result)
	{
		lastError = true;
	}

	sounds[filename] = sf::Sound(soundBuffer);

	return sounds[filename];
}

sf::Sound& Application::getFocusChangedSound()
{
	return getSound("media\\focusChanged.wav");
}

sf::Sound& Application::getTextEnteredSound()
{
	return getSound("media\\textEntered.wav");
}

sf::Sound& Application::getButtonPressedSound()
{
	return getSound("media\\buttonPressed.wav");
}

void Application::PlaySound(const std::string& filename)
{
	getSound(filename).play();
}

void Application::PlayFocusChangedSound()
{
	getSound("media\\focusChanged.wav").play();
}

void Application::PlayTextEnteredSound()
{
	getSound("media\\textEntered.wav").play();
}

void Application::PlayButtonPressedSound()
{
	getSound("media\\buttonPressed.wav").play();
}

sf::Music* Application::getMusic(const std::string& filename)
{
	std::map<std::string, sf::Music*>::iterator it = music.find(filename);

	if(it != music.end())
	{
		return it->second;
	}

	sf::Music* music_ = new sf::Music();

	if(!music_->openFromFile(filename))
	{
		lastError = true;
	}

	music[filename] = music_;

	return music_;
}

float Application::getWidth() const
{
	return getView().getSize().x;
}

float Application::getHeight() const
{
	return getView().getSize().y;
}