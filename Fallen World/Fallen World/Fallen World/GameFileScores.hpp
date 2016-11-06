#ifndef _GAMEFILESCORES_HPP_
#define _GAMEFILESCORES_HPP_

#include "GameFile.hpp"

struct Score
{
	std::string name;
	int score;
	
	Score(const std::string& name = "-", const int& score = 0)
	{
		this->name = name;
		this->score = score;
	}
};

class GameFileScores : public GameFile
{
	Score scores[10];

	// Методы чтения и записи данных
	void readData(std::ifstream& stream);
	void writeData(std::ofstream& stream);

public:

	// Добавляет игрока в список
	void AddPlayer(const std::string& name, const int& score);

	// Получает сортированный список
	Score* getScores();
};

#endif