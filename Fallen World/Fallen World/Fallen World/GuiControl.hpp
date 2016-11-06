#ifndef _GUICONTROL_HPP_
#define _GUICONTROL_HPP_

#include "Application.hpp"

// Класс экрана объявлен для того, чтобы можно было использовать перекрёстное объявление:
// В классе экрана хранится коллекция на элементов управления, а в классе элемента управления есть упоминание экрана
class GuiScreen;

// Абстрактный класс, описывающий элемент управления. Требует реализации методов обратоки событий и рендеринга.
class GuiControl
{
protected:

	int index;
	bool focused;
	bool pressed;

public:

	GuiControl(const int& index);

	// Обработка событий элемента управления, которая может быть унаследована конкретным элементом управления
	virtual void Handle(GuiScreen& screen, Application& app, sf::Event event) = 0;

	// Рендеринг элемента управления, который может быть реализован конкретным элементом управления
	virtual void Draw(GuiScreen& screen, Application& app, sf::Time time) = 0;

	// Задаёт фокус элемента управления
	void setFocused(const bool& focused);

	// Задаёт нажатие элемента управления
	void setPressed(const bool& pressed);

	// Возвращает истину, если элемент управления имеет фокус, ложь - если не имеет
	const bool& isFocused() const;

	// Возвращает истину, если элемент управления зажат, ложь - если не имеет
	const bool& isPressed() const;

	// Получает индекс элемента управления
	const int& getIndex() const;

	// Получает границы элемента управления, реализуется конкретным наследником
	virtual sf::FloatRect getBounds() const = 0;
};

#endif