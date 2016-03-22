#include "Hardware.h"


Hardware::Hardware()
{
}

Hardware::Hardware(int* stats)
{
	this->stats = stats;
}

int* Hardware::getValues()
{
	return stats;
}

void Hardware::setValues(int* newStats)
{
	this->stats = newStats;
}

Hardware::~Hardware()
{
}
