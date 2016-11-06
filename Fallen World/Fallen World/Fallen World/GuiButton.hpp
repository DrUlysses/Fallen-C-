#ifndef _GUIBUTTON_HPP_
#define _GUIBUTTON_HPP_

#include "GuiControl.hpp"

// ���� ����� ��������� ������, ��� ������� ����������
class GuiButton : public GuiControl
{
	float x, y;
	float w, h;
	sf::String string;

public:

	GuiButton(const int& index, const float& x, const float& y, const float& w, const float& h, const sf::String& string);

	// ��������� ������� ����
	void Handle(GuiScreen& screen, Application& App, sf::Event event);

	// ��������� ������
	void Draw(GuiScreen& screen, Application& App, sf::Time time);

	// �������� ������� ������
	sf::FloatRect getBounds() const;
};

#endif