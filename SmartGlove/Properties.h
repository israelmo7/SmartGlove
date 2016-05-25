#include <iostream>
#include <string>
#include <fstream>

#define PATHFILE "Properties.txt"
class Properties
{
public:
	Properties();
	~Properties();

	int getValueByName(std::string name);
	std::string getNameFromLine(std::string line);
	int getValueFromLine(std::string line);
private:
	std::ifstream _file;
};