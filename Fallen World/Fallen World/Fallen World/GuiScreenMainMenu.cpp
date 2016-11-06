#include "GuiScreenMainMenu.hpp"
#include "GuiScreenNew.hpp"
#include "GuiScreenOptions.hpp"
#include "GameScreen.hpp"
#include "GameFileSave.hpp"

GuiScreenMainMenu::GuiScreenMainMenu(Application& App) : GuiScreen(App)
{
	counter = 0;

	const float left = getButtonLeft();
	const float top = getButtonsTop(4);

	addControl(new GuiButton(0, left, getButtonTop(top, 1), buttonWidth, buttonHeight, "New"));
	addControl(new GuiButton(1, left, getButtonTop(top, 2), buttonWidth, buttonHeight, "Continue"));
	addControl(new GuiButton(2, left, getButtonTop(top, 3), buttonWidth, buttonHeight, "Options"));
	addControl(new GuiButton(3, left, getButtonTop(top, 4), buttonWidth, buttonHeight, "Quit"));

	continueButtonTop = getButtonTop(top, 2);
	continueButtonRight = left + buttonWidth;
	continueButtonSelected = false;

	sf::Music* music = App.getMusic("media\\repMenu.ogg");

	if(music->getStatus() != sf::SoundSource::Playing)
	{
		music->setVolume(3);
		music->setLoop(true);
		music->play();
	}
}

void GuiScreenMainMenu::Handle(sf::Event event)
{
	GuiScreen::Handle(event);

	if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7))
	{
		App.Stop();
	}
}

void GuiScreenMainMenu::Draw(sf::Time time)
{
	GuiScreen::Draw(time);

	sf::Text text;
	text.setString("Live fast, die young!");
	text.setPosition(5 + sin(counter / 1000.f * 9) * 3, 5 + sin(counter / 1000.f * 9) * 3);
	text.setFont(App.getButtonFont());
	text.setCharacterSize(15);
	App.draw(text);

	if(continueButtonSelected)
	{
		sf::Text textName;
		textName.setFont(App.getButtonFont());
		textName.setString(name);
		textName.setPosition(continueButtonRight + 15, continueButtonTop + 15);
		App.draw(textName);
	}

	counter += time.asMicroseconds() / 1000.f;
}

void GuiScreenMainMenu::OnButtonPressed(GuiButton& button)
{
	if(button.getIndex() == 0)
	{
		App.SetScreen(new GuiScreenNew(App));
	}
	else if(button.getIndex() == 1)
	{
		GameFileSave save;
		
		if(save.LoadFile("save.dat"))
		{
			App.getMusic("media\\repMenu.ogg")->stop();
			App.SetScreen(new GameScreen(App, save.name, save.score, save.gunLevel, save.health));
		}
	}
	else if(button.getIndex() == 2)
	{
		App.SetScreen(new GuiScreenOptions(App));
	}
	else if(button.getIndex() == 3)
	{
		App.Stop();
	}
}

void GuiScreenMainMenu::OnControlSelected(GuiControl& control)
{
	if(control.getIndex() == 1)
	{
		GameFileSave save;
		
		if(save.LoadFile("save.dat"))
		{
			name = save.name;
			continueButtonSelected = true;
		}
	}
	else
	{
		continueButtonSelected = false;
	}
}