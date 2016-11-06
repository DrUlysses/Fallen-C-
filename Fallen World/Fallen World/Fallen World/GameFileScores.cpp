#include "GameFileScores.hpp"
#include <vector>

void GameFileScores::readData(std::ifstream& stream)
{
	for(int i = 0; i < 10; ++i)
	{
		scores[i].name = readString(stream);
		scores[i].score = readInt32(stream);
	}
}

void GameFileScores::writeData(std::ofstream& stream)
{
	for(int i = 0; i < 10; ++i)
	{
		writeString(scores[i].name, stream);
		writeInt32(scores[i].score, stream);
	}
}

void GameFileScores::AddPlayer(const std::string& name, const int& score)
{
	std::vector<Score> vector;

	int i;

	for(i = 0; i < 10; ++i)
	{
		vector.push_back(scores[i]);
	}

	std::vector<Score>::iterator it;

	for(it = vector.begin(); it != vector.end(); ++it)
	{
		if(name == it->name)
		{
			if(score > it->score)
			{
				vector.erase(it);

				break;
			}
			else
			{
				return;
			}
		}
	}

	for(it = vector.begin(); it != vector.end(); ++it)
	{
		if(score > it->score)
		{
			vector.insert(it, Score(name, score));

			break;
		}
	}

	for(i = 0; i < 10; ++i)
	{
		scores[i] = vector[i];
	}
}

Score* GameFileScores::getScores()
{
	return scores;
}