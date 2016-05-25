#pragma once

#define DEFAULT_PORT "80"

class Traffic
{
public:
	Traffic();
	~Traffic(){};
	SOCKET getSocket() const;
	void closeSocket();
private:
	SOCKET _sock;
};