#ifndef _GUISCREENPAUSE_HPP_
#define _GUISCREENPAUSE_HPP_

#include "GuiScreen.hpp"
#include "GameScreen.hpp"

class GuiScreenPause : public GuiScreen
{
	GameScreen* gameScreen;

public:

	GuiScreenPause(Application& App, GameScreen* gameScreen);

	// ������������ ������� ����
	void Handle(sf::Event event);

	// ������������ ������� ������
	void OnButtonPressed(GuiButton& button);
};

#endif