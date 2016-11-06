#ifndef _GAMEFILESAVE_HPP_
#define _GAMEFILESAVE_HPP_

#include "GameFile.hpp"

class GameFileSave : public GameFile
{
	// Методы чтения и записи данных
	void readData(std::ifstream& stream);
	void writeData(std::ofstream& stream);

public:

	// Имя игрока
	std::string name;

	// Очки игрока
	int score;

	// Уровень оружия игрока
	int gunLevel;

	// Здоровье игрока
	int health;

	GameFileSave();
};

#endif