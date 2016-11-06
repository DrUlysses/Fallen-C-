#include "GuiScreen.hpp"
#include "Application.hpp"

const float GuiScreen::buttonWidth = 520;
const float GuiScreen::buttonHeight = 104;
const float GuiScreen::buttonMargin = 15;

float GuiScreen::getButtonLeft(const float& width)
{
	return (App.getWidth() - width) / 2;
}

float GuiScreen::getButtonTop(const float& top, const int& number, const float& height, const float& margin)
{
	return top + (height + margin) * (number - 1);
}

float GuiScreen::getButtonsTop(const int& count, const float& height, const float& margin)
{
	return (App.getHeight() - (height + margin) * count - margin) / 2;
}

float GuiScreen::getButtonStep(const float& height, const float& margin)
{
	return height + margin;
}

GuiScreen::GuiScreen(Application& App) : Screen(App)
{
	controlIndex = 0;
	drawBackground = true;
}

GuiScreen::~GuiScreen()
{
	// Освобождаем память, выделенную под элементы управления
	for(int i = 0; i < (int)controls.size(); ++i)
	{
		if(controls[i])
		{
			delete controls[i];
		}
	}
}

void GuiScreen::Handle(sf::Event event)
{
	if(!controls.empty())
	{
		// Если элемент управления выбран, но имеет фокуса, то наделяем его фокусом
		GuiControl* focusedControl = controls[controlIndex];

		if(!focusedControl->isFocused())
		{
			focusedControl->setFocused(true);
		}

		// Обработка нажатий клавиш, для смены фокуса
		if(event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickMoved)
		{
			if((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) || (int(event.joystickMove.position == -100) || int(event.joystickMove.position == 100)))
			{
				focusedControl->setFocused(false);
				focusedControl->setPressed(false);

				if(event.key.code == sf::Keyboard::Up || int(event.joystickMove.position) == -100)
				{
					if(--controlIndex < 0)
					{
						controlIndex = controls.size() + controlIndex;
					}
				}
				else if(event.key.code == sf::Keyboard::Down || int(event.joystickMove.position) == 100)
				{
					controlIndex = ++controlIndex % controls.size();
				}

				focusedControl = controls[controlIndex];
				focusedControl->setFocused(true);
				focusedControl->setPressed(false);

				App.PlayFocusChangedSound();

				OnControlSelected(*focusedControl);
			}
		}

		// Обработка событий мыши

		/*if(event.type == sf::Event::MouseMoved)
		{
			GuiControl* newFocusedControl = 0;

			for(int i = 0; i < (int)controls.size(); ++i)
			{
				GuiControl* control = controls[i];

				sf::Vector2f coords = App.mapPixelToCoords(sf::Mouse::getPosition(App), App.getView());

				if(sf::FloatRect(coords.x, coords.y, 1.f, 1.f).intersects(control->getBounds()))
				{
					newFocusedControl = control;
					break;
				}
			}

			if(newFocusedControl)
			{
				controlIndex = newFocusedControl->getIndex();
				focusedControl->setFocused(false);
				focusedControl = newFocusedControl;
				focusedControl->setFocused(true);
			}
		}*/

		// Обработка данного события всеми элементами управления
		for(int i = 0; i < (int)controls.size(); ++i)
		{
			controls[i]->Handle(*this, App, event);
		}
	}
}

void GuiScreen::Draw(sf::Time time)
{
	// Фон экрана
	if(drawBackground)
	{
		sf::Sprite sprite;
		sprite.setPosition(0, 0);
		sprite.setTexture(App.getScreenTexture());
		sprite.setTextureRect(sf::IntRect(0, 0, App.getSize().x, App.getSize().y));
		App.draw(sprite);
	}

	// Рендеринг элементов управления
	for(int i = 0; i < (int)controls.size(); ++i)
	{
		controls[i]->Draw(*this, App, time);
	}
}

void GuiScreen::addControl(GuiControl* control)
{
	controls.push_back(control);
}