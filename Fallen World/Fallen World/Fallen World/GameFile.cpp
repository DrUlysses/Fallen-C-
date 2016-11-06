#include "GameFile.hpp"

int GameFile::readInt32(std::ifstream& stream)
{
	int value;

	stream.read(reinterpret_cast<char*>(&value), sizeof(int));

	return value;
}

void GameFile::writeInt32(const int& value, std::ofstream& stream)
{
	stream.write(reinterpret_cast<const char*>(&value), sizeof(int));
}

std::string GameFile::readString(std::ifstream& stream)
{
	std::string string;

readChar :

	char c;

	stream.read(&c, sizeof(char));

	if(c != EOF && c != '\0')
	{
		string += c;

		goto readChar;
	}

	return string;
}

void GameFile::writeString(const std::string& string, std::ofstream& stream)
{
	stream << string;
	stream << '\0';
}

std::ifstream GameFile::openBinaryInput(const std::string& filename)
{
	return std::ifstream(filename, std::ifstream::binary);
}

std::ofstream GameFile::openBinaryOutput(const std::string& filename)
{
	return std::ofstream(filename, std::ifstream::binary);
}

bool GameFile::LoadFile(const std::string& filename)
{
	std::ifstream stream = openBinaryInput(filename);

	if(!stream.is_open())
	{
		return false;
	}

	readData(stream);

	stream.close();

	return true;
}

void GameFile::SaveFile(const std::string& filename)
{
	std::ofstream stream = openBinaryOutput(filename);

	if(stream.is_open())
	{
		writeData(stream);
	}

	stream.close();
}