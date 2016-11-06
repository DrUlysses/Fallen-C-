#ifndef _GUISCREENOPTIONS_HPP_
#define _GUISCREENOPTIONS_HPP_

#include "GuiScreen.hpp"

//  ласс представл€ющий экран опций
class GuiScreenOptions : public GuiScreen
{
	float counter;

public:

	GuiScreenOptions(Application& App);

	// –ендеринг экрана
	void Draw(sf::Time time);

	// ќбработка событий
	void Handle(sf::Event event);

	// ќбработка нажатий клавиш
	void OnButtonPressed(GuiButton& button);
};

#endif