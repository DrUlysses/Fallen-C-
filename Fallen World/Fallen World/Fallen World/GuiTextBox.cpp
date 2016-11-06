#include "GuiTextBox.hpp"
#include "GuiScreen.hpp"

bool GuiTextBox::isLetter(const sf::Uint32& unicode)
{
	if(unicode >= 'a' && unicode <= 'z')
	{
		return true;
	}

	if(unicode >= 'A' && unicode <= 'Z')
	{
		return true;
	}

	if(unicode >= 'à' && unicode <= 'ÿ' || unicode == '¸')
	{
		return true;
	}
	
	if(unicode >= 'À' && unicode <= 'ß' || unicode == '¨')
	{
		return true;
	}

	return false;
}

bool GuiTextBox::isNumber(const sf::Uint32& unicode)
{
	return unicode >= '0' && unicode <= '9';
}

bool GuiTextBox::isSymbol(const sf::Uint32& unicode)
{
	switch(unicode)
	{
	case ' ':
	case '.':
	case ',':
	case '?':
	case '!':
		return true;
	}

	return false;
}

GuiTextBox::GuiTextBox(const int& index, const float& x, const float& y, const float& w, const float& h, const sf::String& string) : GuiControl(index)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	initialString = string;
	counter = 0;
}

void GuiTextBox::Handle(GuiScreen& screen, Application& App, sf::Event event)
{
	if(focused)
	{
		if(event.type == sf::Event::TextEntered)
		{
			const sf::Uint32 ch = event.text.unicode;

			if(ch == '\b')
			{
				if(!currentString.isEmpty())
				{
					currentString.erase(currentString.getSize() - 1, 1);

					App.PlayTextEnteredSound();
				}
			}
			else
			{
				if(isLetter(ch) || isNumber(ch) || isSymbol(ch))
				{
					currentString += ch;

					App.PlayTextEnteredSound();
				}
			}
		}

		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return || event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0)
		{
			screen.OnTextEntered(*this);
		}
	}
}

void GuiTextBox::Draw(GuiScreen& screen, Application& App, sf::Time time)
{
	const int imageHeight = 26;
	const int imageSideWidth = 41;
	const int imageMiddleWidth = 32;

	const int imageLeftX = 0;
	const int imageMiddleX = 49;
	const int imageRightX = 89;
	const int imageTextZoneX = 32;

	float spriteScale = h / imageHeight;

	sf::Sprite leftSprite;
	leftSprite.setScale(spriteScale, spriteScale);
	leftSprite.setPosition(x, y);
	leftSprite.setTexture(App.getTextBoxTexture());
	leftSprite.setTextureRect(sf::IntRect(imageLeftX, 0, imageSideWidth, imageHeight));
	App.draw(leftSprite);

	sf::Sprite middleSprite;
	middleSprite.setScale((w - imageSideWidth * spriteScale * 2) / imageMiddleWidth, spriteScale);
	middleSprite.setPosition(x + imageSideWidth * spriteScale, y);
	middleSprite.setTexture(App.getTextBoxTexture());
	middleSprite.setTextureRect(sf::IntRect(imageMiddleX, 0, imageMiddleWidth, imageHeight));
	App.draw(middleSprite);

	sf::Sprite rightSprite;
	rightSprite.setScale(spriteScale, spriteScale);
	rightSprite.setPosition(x + (w - imageSideWidth * spriteScale), y);
	rightSprite.setTexture(App.getTextBoxTexture());
	rightSprite.setTextureRect(sf::IntRect(imageRightX, 0, imageSideWidth, imageHeight));
	App.draw(rightSprite);

	sf::Text text;
	text.setFont(App.getButtonFont());

	float height = sf::Text("A", App.getButtonFont()).getGlobalBounds().height * 2;

	sf::String string = currentString.isEmpty() ? initialString : currentString;

	if(focused)
	{
		if(counter <= 275)
		{
			text.setString(string);
		}
		else if(counter > 275)
		{
			text.setString(string + "_");

			if(counter > 500)
			{
				counter = 0;
			}
		}

		text.setPosition(x + imageTextZoneX * 4, y + (h - height) / 2);
	}
	else
	{
		text.setString(string);
		text.setPosition(x + (w - text.getGlobalBounds().width) / 2, y + (h - height) / 2);
	}

	App.draw(text);

	counter += time.asMicroseconds() / 1000.f;
}

const sf::String& GuiTextBox::getString() const
{
	return currentString;
}

bool GuiTextBox::isEmpty() const
{
	return currentString.isEmpty();
}

sf::FloatRect GuiTextBox::getBounds() const
{
	return sf::FloatRect(sf::Vector2f(x, y), sf::Vector2f(w, h));
}