#pragma once

class Pressure
{
public:
	Pressure(int press = 0);
	~Pressure();
	int getValue() const;
private:
	int _value;

};