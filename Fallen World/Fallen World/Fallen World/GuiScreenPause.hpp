#ifndef _GUISCREENPAUSE_HPP_
#define _GUISCREENPAUSE_HPP_

#include "GuiScreen.hpp"
#include "GameScreen.hpp"

class GuiScreenPause : public GuiScreen
{
	GameScreen* gameScreen;

public:

	GuiScreenPause(Application& App, GameScreen* gameScreen);

	// Обрабатывает события окна
	void Handle(sf::Event event);

	// Обрабатывает нажатие кнопок
	void OnButtonPressed(GuiButton& button);
};

#endif