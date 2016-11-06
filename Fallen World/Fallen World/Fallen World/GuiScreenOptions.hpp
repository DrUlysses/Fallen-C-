#ifndef _GUISCREENOPTIONS_HPP_
#define _GUISCREENOPTIONS_HPP_

#include "GuiScreen.hpp"

// ����� �������������� ����� �����
class GuiScreenOptions : public GuiScreen
{
	float counter;

public:

	GuiScreenOptions(Application& App);

	// ��������� ������
	void Draw(sf::Time time);

	// ��������� �������
	void Handle(sf::Event event);

	// ��������� ������� ������
	void OnButtonPressed(GuiButton& button);
};

#endif