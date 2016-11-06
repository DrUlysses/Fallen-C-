#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <SFML\Graphics.hpp>

// ����� ���������� �������� ��� ����, ����� ����� ���� ������������ ����������� ����������:
// � ������ ���������� �������� ��������� �� �����, � ������ ������ - ������ �� ����������
class Application;

// ����������� �����, ������� ������ ���� ����������� ����� �������
class Screen
{
protected:

	Application& App;

public:

	Screen(Application& App);

	// ����������� �������-����������� ��� ��������� ������� ����
	virtual void Handle(sf::Event event) = 0;

	// ����������� �������-����������� ��� ���������� ����������� ������
	virtual void Draw(sf::Time time) = 0;
};

#endif