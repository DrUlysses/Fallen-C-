#include "GuiButton.hpp"
#include "GuiScreen.hpp"

GuiButton::GuiButton(const int& index, const float& x, const float& y, const float& w, const float& h, const sf::String& string) : GuiControl(index)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->string = string;
}

void GuiButton::Handle(GuiScreen& screen, Application& App, sf::Event event)
{
	if(focused)
	{
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == sf::Keyboard::Return)
			{
				App.PlayButtonPressedSound();

				pressed = true;
			}
		}
		else if(event.type == sf::Event::KeyReleased)
		{
			if(event.key.code == sf::Keyboard::Return)
			{
				screen.OnButtonPressed(*this);

				pressed = false;
			}
		}
		if(sf::Joystick::isConnected(0))
		{
			if(event.type == sf::Event::JoystickButtonPressed)
			{
				if(event.joystickButton.button == 0)
				{
					App.PlayButtonPressedSound();

					pressed = true;
				}
			}
			else if(event.type == sf::Event::JoystickButtonReleased)
			{
				if(event.joystickButton.button == 0)
				{
					screen.OnButtonPressed(*this);

					pressed = false;
				}
			}
		}
		/*else if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.mouseButton.button == sf::Mouse::Left)
			{
				screen.OnButtonPressed(*this);

				App.PlayButtonPressedSound();
			}
		}*/
	}
}

void GuiButton::Draw(GuiScreen& screen, Application& App, sf::Time time)
{
	const int imageHeight = 26;
	const int imageSideWidth = 41;
	const int imageMiddleWidth = 32;

	const int imageLeftX = 0;
	const int imageMiddleX = 49;
	const int imageRightX = 89;

	const int imageFirstY = 0;
	const int imageSecondY = 32;
	const int imageThirdY = 64;

	int imageOffsetY;

	if(focused)
	{
		if(pressed)
		{
			imageOffsetY = imageThirdY;
		}
		else
		{
			imageOffsetY = imageSecondY;
		}
	}
	else
	{
		imageOffsetY = imageFirstY;
	}

	float spriteScale = h / imageHeight;

	sf::Sprite leftSprite;
	leftSprite.setScale(spriteScale, spriteScale);
	leftSprite.setPosition(x, y);
	leftSprite.setTexture(App.getButtonTexture());
	leftSprite.setTextureRect(sf::IntRect(imageLeftX, imageOffsetY, imageSideWidth, imageHeight));
	App.draw(leftSprite);

	sf::Sprite middleSprite;
	middleSprite.setScale((w - imageSideWidth * spriteScale * 2) / imageMiddleWidth, spriteScale);
	middleSprite.setPosition(x + imageSideWidth * spriteScale, y);
	middleSprite.setTexture(App.getButtonTexture());
	middleSprite.setTextureRect(sf::IntRect(imageMiddleX, imageOffsetY, imageMiddleWidth, imageHeight));
	App.draw(middleSprite);

	sf::Sprite rightSprite;
	rightSprite.setScale(spriteScale, spriteScale);
	rightSprite.setPosition(x + (w - imageSideWidth * spriteScale), y);
	rightSprite.setTexture(App.getButtonTexture());
	rightSprite.setTextureRect(sf::IntRect(imageRightX, imageOffsetY, imageSideWidth, imageHeight));
	App.draw(rightSprite);

	float height = sf::Text("A", App.getButtonFont()).getGlobalBounds().height * 2;

	sf::Text text;
	text.setString(string);
	text.setFont(App.getButtonFont());
	text.setColor(sf::Color::Black);
	text.setPosition(x + (w - text.getGlobalBounds().width) / 2, y + (h - height) / 2);
	App.draw(text);
}

sf::FloatRect GuiButton::getBounds() const
{
	return sf::FloatRect(sf::Vector2f(x, y), sf::Vector2f(w, h));
}