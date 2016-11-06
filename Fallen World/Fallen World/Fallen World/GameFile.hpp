#ifndef _GAMEFILE_HPP_
#define _GAMEFILE_HPP_

#include <fstream>
#include <string>

class GameFile
{
protected:

	// Методы чтения/записи целого 32-х битного числа
	static int readInt32(std::ifstream& stream);
	static void writeInt32(const int& value, std::ofstream& stream);

	// Методы чтения/записи строки
	static std::string readString(std::ifstream& stream);
	static void writeString(const std::string& string, std::ofstream& stream);

	// Методы создания объектов, представляющих файловые потоки
	static std::ifstream openBinaryInput(const std::string& filename);
	static std::ofstream openBinaryOutput(const std::string& filename);

	// Должны быть реализованы классами-наследниками для чтения и записи данных
	virtual void readData(std::ifstream& stream) = 0;
	virtual void writeData(std::ofstream& stream) = 0;

public:

	// Методы для загрузки и сохранения файлов
	bool LoadFile(const std::string& filename);
	void SaveFile(const std::string& filename);
};

#endif