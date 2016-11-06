#ifndef _GUISCREENMAINMENU_HPP_
#define _GUISCREENMAINMENU_HPP_

#include "GuiScreen.hpp"

// Класс, описывающий главное меню
class GuiScreenMainMenu : public GuiScreen
{
	float counter;
	float continueButtonTop;
	float continueButtonRight;
	bool continueButtonSelected;
	std::string name;

public:

	GuiScreenMainMenu(Application& App);

	// Обработка событий окна
	void Handle(sf::Event event);

	// Рендеринг содержимого
	void Draw(sf::Time time);

	// Обработка события нажатия кнопки
	void OnButtonPressed(GuiButton& button);

	// Обработка события выбора элемента управления
	void OnControlSelected(GuiControl& control);
};

#endif