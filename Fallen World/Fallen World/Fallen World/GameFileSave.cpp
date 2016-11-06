#include "GameFileSave.hpp"

GameFileSave::GameFileSave()
{
	name = "Player";
	score = 0;
	gunLevel = 0;
	health = 0;
}

void GameFileSave::readData(std::ifstream& stream)
{
	name = readString(stream);
	score = readInt32(stream);
	gunLevel = readInt32(stream);
	health = readInt32(stream);
}

void GameFileSave::writeData(std::ofstream& stream)
{
	writeString(name, stream);
	writeInt32(score, stream);
	writeInt32(gunLevel, stream);
	writeInt32(health, stream);
}