#include "GuiScreenNew.hpp"
#include "GuiScreenMainMenu.hpp"
#include "GameScreen.hpp"

GuiScreenNew::GuiScreenNew(Application& App) : GuiScreen(App)
{
	scores.LoadFile("scores.dat");

	const float buttonWidth = App.getWidth() * 0.96f;
	const float left = getButtonLeft(buttonWidth);
	const float top = 10;

	addControl(textBox = new GuiTextBox(0, left, getButtonTop(top, 1), buttonWidth, buttonHeight, "Type your name"));
	addControl(new GuiButton(1, left, getButtonTop(top, 2), buttonWidth, buttonHeight, "Ok"));

	scoresY = getButtonTop(top, 2) + getButtonStep();
}

void GuiScreenNew::Handle(sf::Event event)
{
	GuiScreen::Handle(event);

	if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7))
	{
		App.SetScreen(new GuiScreenMainMenu(App));
	}
}

void GuiScreenNew::Draw(sf::Time time)
{
	GuiScreen::Draw(time);

	sf::Text number;
	sf::Text name;
	sf::Text score;

	number.setFont(App.getButtonFont());
	name.setFont(App.getButtonFont());
	score.setFont(App.getButtonFont());
	number.setPosition(15, scoresY);
	name.setPosition(250, scoresY);
	score.setPosition(0, scoresY);
	
	float margin = App.getHeight() / 17;

	for(int i = -1; i < 10; ++i)
	{
		if(i != -1)
		{
			number.setString(std::to_string((_Longlong)(i + 1)));
			name.setString(scores.getScores()[i].name);
			score.setString(std::to_string((_Longlong)scores.getScores()[i].score));
		}
		else
		{
			number.setString("Number");
			name.setString("Name");
			score.setString("Scores");
		}

		score.setPosition(App.getWidth() - score.getGlobalBounds().width - 50, score.getPosition().y);
		App.draw(number);
		App.draw(name);
		App.draw(score);
		number.move(0, margin);
		name.move(0, margin);
		score.move(0, margin);
	}
}

void GuiScreenNew::OnButtonPressed(GuiButton& button)
{
	if(button.getIndex() == 1 && !textBox->isEmpty())
	{
		App.getMusic("media\\repMenu.ogg")->stop();
		App.SetScreen(new GameScreen(App, textBox->getString()));
	}
}

void GuiScreenNew::OnTextEntered(GuiTextBox& textBox)
{
	if(textBox.getIndex() == this->textBox->getIndex() && !textBox.isEmpty())
	{
		App.getMusic("media\\repMenu.ogg")->stop();
		App.SetScreen(new GameScreen(App, textBox.getString()));
	}
}