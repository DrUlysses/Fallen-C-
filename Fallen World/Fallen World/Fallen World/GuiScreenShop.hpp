#ifndef _GUISCREENSHOP_HPP_
#define _GUISCREENSHOP_HPP_

#include "GuiScreen.hpp"
#include "GameScreen.hpp"

// �����, ����������� ���� ��������, ������� ���������� �� ����� ����
class GuiScreenShop : public GuiScreen
{
	sf::Texture shopTexture;
	sf::Texture gunsTexture;
	sf::Texture arrowTexture;
	GameScreen* gameScreen;

	static int getTileX(int gunLevel);
	static int getTileY(int gunLevel);

public:

	GuiScreenShop(Application& App, GameScreen* gameScreen);

	// ��������� ������� ����
	void Handle(sf::Event event);

	// ��������� ������
	void Draw(sf::Time time);
};

#endif