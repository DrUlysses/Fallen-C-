#ifndef _GUISCREEN_HPP_
#define _GUISCREEN_HPP_

#include "Screen.hpp"
#include "GuiControl.hpp"
#include "GuiButton.hpp"
#include "GuiTextBox.hpp"
#include <vector>

// Класс, описывающий экран с графическим интерфейсом пользователя
class GuiScreen : public Screen
{
	int controlIndex;
	std::vector<GuiControl*> controls;

protected:

	// Геометрические параметры кнопок по умолчанию
	static const float buttonWidth;
	static const float buttonHeight;
	static const float buttonMargin;

	// Работа с группами кнопок
	float getButtonLeft(const float& width = buttonWidth);
	float getButtonTop(const float& top, const int& number, const float& height = buttonHeight, const float& margin = buttonMargin);
	float getButtonsTop(const int& count, const float& height = buttonHeight, const float& margin = buttonMargin);
	float getButtonStep(const float& height = buttonHeight, const float& margin = buttonMargin);

	bool drawBackground;

public:

	GuiScreen(Application& App);
	~GuiScreen();

	// Обработка событий
	void Handle(sf::Event event);

	// Рендеринг содержимого
	void Draw(sf::Time time);

	// Добавляет элемент управления в данный экран
	void addControl(GuiControl* control);

	// События элементов управления, которые могут быть реализованы экранами-наследниками
	virtual void OnButtonPressed(GuiButton& button) { };
	virtual void OnTextEntered(GuiTextBox& textBox) { };
	virtual void OnControlSelected(GuiControl& control) { };
};

#endif