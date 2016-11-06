#ifndef _TEXTBOX_HPP_
#define _TEXTBOX_HPP_

#include "GuiControl.hpp"

// Данный класс описывает текстовое поле
class GuiTextBox : public GuiControl
{
	float x, y;
	float w, h;
	float counter;
	sf::String initialString;
	sf::String currentString;

	// Методы, распознающие символ по его коду
	static bool isLetter(const sf::Uint32& unicode);
	static bool isNumber(const sf::Uint32& unicode);
	static bool isSymbol(const sf::Uint32& unicode);

public:

	GuiTextBox(const int& index, const float& x, const float& y, const float& w, const float& h, const sf::String& string);

	// Обработка событий окна
	void Handle(GuiScreen& screen, Application& App, sf::Event event);

	// Рендеринг текстового поля
	void Draw(GuiScreen& screen, Application& App, sf::Time time);

	// Получает строку, введённую пользователем
	const sf::String& getString() const;

	// Возвращает истину, если пользователь не ввёл строку, ложь - если строка введена
	bool isEmpty() const;

	// Получает границы текстового поля
	sf::FloatRect getBounds() const;
};

#endif