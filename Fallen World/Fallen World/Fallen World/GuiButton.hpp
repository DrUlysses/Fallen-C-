#ifndef _GUIBUTTON_HPP_
#define _GUIBUTTON_HPP_

#include "GuiControl.hpp"

// Этот класс описывает кнопку, как элемент управления
class GuiButton : public GuiControl
{
	float x, y;
	float w, h;
	sf::String string;

public:

	GuiButton(const int& index, const float& x, const float& y, const float& w, const float& h, const sf::String& string);

	// Обработка событий окна
	void Handle(GuiScreen& screen, Application& App, sf::Event event);

	// Рендеринг кнопки
	void Draw(GuiScreen& screen, Application& App, sf::Time time);

	// Получает границы кнопки
	sf::FloatRect getBounds() const;
};

#endif