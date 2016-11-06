#ifndef _GUISCREENSHOP_HPP_
#define _GUISCREENSHOP_HPP_

#include "GuiScreen.hpp"
#include "GameScreen.hpp"

// Класс, описывающий окно магазина, которое появляется во время игры
class GuiScreenShop : public GuiScreen
{
	sf::Texture shopTexture;
	sf::Texture gunsTexture;
	sf::Texture arrowTexture;
	GameScreen* gameScreen;

	static int getTileX(int gunLevel);
	static int getTileY(int gunLevel);

public:

	GuiScreenShop(Application& App, GameScreen* gameScreen);

	// Обработка событий окна
	void Handle(sf::Event event);

	// Рендеринг экрана
	void Draw(sf::Time time);
};

#endif