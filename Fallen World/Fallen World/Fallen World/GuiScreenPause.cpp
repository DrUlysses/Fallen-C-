#include "GuiScreenPause.hpp"
#include "GuiScreenMainMenu.hpp"
#include "GameFileSave.hpp"

GuiScreenPause::GuiScreenPause(Application& App, GameScreen* gameScreen) : GuiScreen(App)
{
	this->gameScreen = gameScreen;

	const float left = getButtonLeft();
	const float top = getButtonsTop(2);

	addControl(new GuiButton(0, left, getButtonTop(top, 1), buttonWidth, buttonHeight, "Continue"));
	addControl(new GuiButton(1, left, getButtonTop(top, 2), buttonWidth, buttonHeight, "Main menu"));
}

void GuiScreenPause::Handle(sf::Event event)
{
	GuiScreen::Handle(event);

	if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7))
	{
		gameScreen->StartGame();
		App.SetScreen(gameScreen);
	}
}

void GuiScreenPause::OnButtonPressed(GuiButton& button)
{
	if(button.getIndex() == 0)
	{
		gameScreen->StartGame();
		App.SetScreen(gameScreen);
	}
	else if(button.getIndex() == 1)
	{
		GameFileSave save;
		save.name = gameScreen->getPlayer()->getName();

		if(!gameScreen->getPlayer()->IsDead())
		{
			save.score = gameScreen->getPlayer()->getPoints();
			save.health = gameScreen->getPlayer()->getHealth();
		}
		else
		{
			save.score = 0;
			save.health = 100;
		}

		save.gunLevel = gameScreen->getPlayer()->getGunLevel();
		save.SaveFile("save.dat");

		App.SetScreen(new GuiScreenMainMenu(App));
	}
}