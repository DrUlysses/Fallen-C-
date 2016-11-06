#ifndef _GUISCREEN_HPP_
#define _GUISCREEN_HPP_

#include "Screen.hpp"
#include "GuiControl.hpp"
#include "GuiButton.hpp"
#include "GuiTextBox.hpp"
#include <vector>

// �����, ����������� ����� � ����������� ����������� ������������
class GuiScreen : public Screen
{
	int controlIndex;
	std::vector<GuiControl*> controls;

protected:

	// �������������� ��������� ������ �� ���������
	static const float buttonWidth;
	static const float buttonHeight;
	static const float buttonMargin;

	// ������ � �������� ������
	float getButtonLeft(const float& width = buttonWidth);
	float getButtonTop(const float& top, const int& number, const float& height = buttonHeight, const float& margin = buttonMargin);
	float getButtonsTop(const int& count, const float& height = buttonHeight, const float& margin = buttonMargin);
	float getButtonStep(const float& height = buttonHeight, const float& margin = buttonMargin);

	bool drawBackground;

public:

	GuiScreen(Application& App);
	~GuiScreen();

	// ��������� �������
	void Handle(sf::Event event);

	// ��������� �����������
	void Draw(sf::Time time);

	// ��������� ������� ���������� � ������ �����
	void addControl(GuiControl* control);

	// ������� ��������� ����������, ������� ����� ���� ����������� ��������-������������
	virtual void OnButtonPressed(GuiButton& button) { };
	virtual void OnTextEntered(GuiTextBox& textBox) { };
	virtual void OnControlSelected(GuiControl& control) { };
};

#endif