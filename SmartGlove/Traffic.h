#pragma once

#define DEFAULT_PORT "80"

class Traffic
{
public:
	Traffic();
	~Traffic(){};
	SOCKET getSocket() const;
private:
	SOCKET _sock;
};