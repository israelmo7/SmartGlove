#include "Properties.h"

Properties::Properties()
{
	this->_file.open(PATHFILE);

	if (!this->_file.is_open())
	{
		std::cout << "Cant open the file " << PATHFILE << "\n";
	}
}
Properties::~Properties()
{
	if (this->_file.is_open())
	{
		this->_file.close();

		if (this->_file.is_open())
		{
			std::cout << "Cant close the file " << PATHFILE << "\n";
		}
	}
}

int Properties::getValueByName(std::string name)
{
	std::string line;

	while(std::getline(this->_file, line))
	{
		if (this->getNameFromLine(line) == name)
		{
			return this->getValueFromLine(line);
		}
	}
	return -1;
}
std::string Properties::getNameFromLine(std::string line)
{
	unsigned int cnt = 0;

	while (line[cnt] != ' ' && line.length() != cnt++);

	return line.substr(0, cnt);
}
int Properties::getValueFromLine(std::string line)
{
	unsigned int cnt = 0,
		len = line.length()-1;

	while (len + 1 != 0 && line[len--] != ' ')
	{
		cnt++;
	}

	return atoi(line.substr(line.length()-cnt).c_str());
}