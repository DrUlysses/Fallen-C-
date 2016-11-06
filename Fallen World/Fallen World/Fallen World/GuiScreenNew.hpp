#ifndef _GUISCREENNEW_HPP_
#define _GUISCREENNEW_HPP_

#include "GuiScreen.hpp"
#include "GuiTextBox.hpp"
#include "GameFileScores.hpp"

// �����, ����������� ���� ������ ����� ����
class GuiScreenNew : public GuiScreen
{
	float scoresY;
	GuiTextBox* textBox;
	GameFileScores scores;

public:

	GuiScreenNew(Application& App);

	// ��������� ������� ����
	void Handle(sf::Event event);

	// ��������� ������
	void Draw(sf::Time time);

	// ��������� ������� ������� ������
	void OnButtonPressed(GuiButton& button);

	// ��������� ������� ���������� ����� ������
	void OnTextEntered(GuiTextBox& textBox);
};

#endif