#ifndef _GUISCREENSTARTUP_HPP_
#define _GUISCREENSTARTUP_HPP_

#include "GuiScreen.hpp"

// �����, ����������� ���� ������ ����� ����
class GuiScreenStartup : public GuiScreen
{
	float counter;

public:

	GuiScreenStartup(Application& App);

	// ��������� �����������
	void Draw(sf::Time time);
};

#endif