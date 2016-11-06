#ifndef _GAMEFILE_HPP_
#define _GAMEFILE_HPP_

#include <fstream>
#include <string>

class GameFile
{
protected:

	// ������ ������/������ ������ 32-� ������� �����
	static int readInt32(std::ifstream& stream);
	static void writeInt32(const int& value, std::ofstream& stream);

	// ������ ������/������ ������
	static std::string readString(std::ifstream& stream);
	static void writeString(const std::string& string, std::ofstream& stream);

	// ������ �������� ��������, �������������� �������� ������
	static std::ifstream openBinaryInput(const std::string& filename);
	static std::ofstream openBinaryOutput(const std::string& filename);

	// ������ ���� ����������� ��������-������������ ��� ������ � ������ ������
	virtual void readData(std::ifstream& stream) = 0;
	virtual void writeData(std::ofstream& stream) = 0;

public:

	// ������ ��� �������� � ���������� ������
	bool LoadFile(const std::string& filename);
	void SaveFile(const std::string& filename);
};

#endif