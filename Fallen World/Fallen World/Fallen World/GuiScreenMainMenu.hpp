#ifndef _GUISCREENMAINMENU_HPP_
#define _GUISCREENMAINMENU_HPP_

#include "GuiScreen.hpp"

// �����, ����������� ������� ����
class GuiScreenMainMenu : public GuiScreen
{
	float counter;
	float continueButtonTop;
	float continueButtonRight;
	bool continueButtonSelected;
	std::string name;

public:

	GuiScreenMainMenu(Application& App);

	// ��������� ������� ����
	void Handle(sf::Event event);

	// ��������� �����������
	void Draw(sf::Time time);

	// ��������� ������� ������� ������
	void OnButtonPressed(GuiButton& button);

	// ��������� ������� ������ �������� ����������
	void OnControlSelected(GuiControl& control);
};

#endif