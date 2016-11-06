#ifndef _GUICONTROL_HPP_
#define _GUICONTROL_HPP_

#include "Application.hpp"

// ����� ������ �������� ��� ����, ����� ����� ���� ������������ ����������� ����������:
// � ������ ������ �������� ��������� �� ��������� ����������, � � ������ �������� ���������� ���� ���������� ������
class GuiScreen;

// ����������� �����, ����������� ������� ����������. ������� ���������� ������� �������� ������� � ����������.
class GuiControl
{
protected:

	int index;
	bool focused;
	bool pressed;

public:

	GuiControl(const int& index);

	// ��������� ������� �������� ����������, ������� ����� ���� ������������ ���������� ��������� ����������
	virtual void Handle(GuiScreen& screen, Application& app, sf::Event event) = 0;

	// ��������� �������� ����������, ������� ����� ���� ���������� ���������� ��������� ����������
	virtual void Draw(GuiScreen& screen, Application& app, sf::Time time) = 0;

	// ����� ����� �������� ����������
	void setFocused(const bool& focused);

	// ����� ������� �������� ����������
	void setPressed(const bool& pressed);

	// ���������� ������, ���� ������� ���������� ����� �����, ���� - ���� �� �����
	const bool& isFocused() const;

	// ���������� ������, ���� ������� ���������� �����, ���� - ���� �� �����
	const bool& isPressed() const;

	// �������� ������ �������� ����������
	const int& getIndex() const;

	// �������� ������� �������� ����������, ����������� ���������� �����������
	virtual sf::FloatRect getBounds() const = 0;
};

#endif