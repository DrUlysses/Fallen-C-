#ifndef _GAMEFILESAVE_HPP_
#define _GAMEFILESAVE_HPP_

#include "GameFile.hpp"

class GameFileSave : public GameFile
{
	// ������ ������ � ������ ������
	void readData(std::ifstream& stream);
	void writeData(std::ofstream& stream);

public:

	// ��� ������
	std::string name;

	// ���� ������
	int score;

	// ������� ������ ������
	int gunLevel;

	// �������� ������
	int health;

	GameFileSave();
};

#endif