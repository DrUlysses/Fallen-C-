#ifndef _GUISCREENNEW_HPP_
#define _GUISCREENNEW_HPP_

#include "GuiScreen.hpp"
#include "GuiTextBox.hpp"
#include "GameFileScores.hpp"

// Класс, описывающий окно начала новой игры
class GuiScreenNew : public GuiScreen
{
	float scoresY;
	GuiTextBox* textBox;
	GameFileScores scores;

public:

	GuiScreenNew(Application& App);

	// Обработка событий окна
	void Handle(sf::Event event);

	// Рендеринг экрана
	void Draw(sf::Time time);

	// Обработка события нажатия кнопки
	void OnButtonPressed(GuiButton& button);

	// Обработка события завершения ввода текста
	void OnTextEntered(GuiTextBox& textBox);
};

#endif