#include "GuiScreenOptions.hpp"
#include "GuiScreenMainMenu.hpp"

GuiScreenOptions::GuiScreenOptions(Application& App) : GuiScreen(App)
{
	counter = 0;

	const float left = getButtonLeft();
	const float top = getButtonsTop(4);

	addControl(new GuiButton(0, left, getButtonTop(top, 1), buttonWidth, buttonHeight, "640 x 480"));
	addControl(new GuiButton(1, left, getButtonTop(top, 2), buttonWidth, buttonHeight, "800 x 600"));
	addControl(new GuiButton(2, left, getButtonTop(top, 3), buttonWidth, buttonHeight, "1024 x 768"));
	addControl(new GuiButton(3, left, getButtonTop(top, 4), buttonWidth, buttonHeight, "1280 x 1024"));
}

void GuiScreenOptions::Draw(sf::Time time)
{
	GuiScreen::Draw(time);

	sf::Text text;
	text.setString("Change game resolution using one from the list");
	text.setPosition(5 + sin(counter / 1000.f * 9) * 3, 5 + sin(counter / 1000.f * 9) * 3);
	text.setFont(App.getButtonFont());
	text.setCharacterSize(15);
	App.draw(text);

	counter += time.asMicroseconds() / 1000.f;
}

void GuiScreenOptions::Handle(sf::Event event)
{
	GuiScreen::Handle(event);

	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Escape)
		{
			App.SetScreen(new GuiScreenMainMenu(App));
		}
	}
}

void GuiScreenOptions::OnButtonPressed(GuiButton& button)
{
	App.close();

	switch(button.getIndex())
	{
	case 0:
		App.create(sf::VideoMode(640, 480, 32), "Application");
		break;
	case 1:
		App.create(sf::VideoMode(800, 600, 32), "Application");
		break;
	case 2:
		App.create(sf::VideoMode(1024, 768, 32), "Application");
		break;
	case 3:
		App.create(sf::VideoMode(1280, 1024, 32), "Application");
		break;
	default:
		App.create(sf::VideoMode::getDesktopMode(), "Application");
	}

	App.SetScreen(new GuiScreenOptions(App));
}