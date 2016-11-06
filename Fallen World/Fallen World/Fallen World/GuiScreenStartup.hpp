#ifndef _GUISCREENSTARTUP_HPP_
#define _GUISCREENSTARTUP_HPP_

#include "GuiScreen.hpp"

// Класс, описывающий окно начала новой игры
class GuiScreenStartup : public GuiScreen
{
	float counter;

public:

	GuiScreenStartup(Application& App);

	// Рендеринг содержимого
	void Draw(sf::Time time);
};

#endif