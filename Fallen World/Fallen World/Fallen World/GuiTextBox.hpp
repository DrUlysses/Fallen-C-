#ifndef _TEXTBOX_HPP_
#define _TEXTBOX_HPP_

#include "GuiControl.hpp"

// ������ ����� ��������� ��������� ����
class GuiTextBox : public GuiControl
{
	float x, y;
	float w, h;
	float counter;
	sf::String initialString;
	sf::String currentString;

	// ������, ������������ ������ �� ��� ����
	static bool isLetter(const sf::Uint32& unicode);
	static bool isNumber(const sf::Uint32& unicode);
	static bool isSymbol(const sf::Uint32& unicode);

public:

	GuiTextBox(const int& index, const float& x, const float& y, const float& w, const float& h, const sf::String& string);

	// ��������� ������� ����
	void Handle(GuiScreen& screen, Application& App, sf::Event event);

	// ��������� ���������� ����
	void Draw(GuiScreen& screen, Application& App, sf::Time time);

	// �������� ������, �������� �������������
	const sf::String& getString() const;

	// ���������� ������, ���� ������������ �� ��� ������, ���� - ���� ������ �������
	bool isEmpty() const;

	// �������� ������� ���������� ����
	sf::FloatRect getBounds() const;
};

#endif