#pragma once
#ifdef SMARTGLOVEDLL_EXPORTS
#define SMARTGLOVE_API _declspec(dllexport)
#else
#define SMARTGLOVE_API _declspec(dllimport)
#endif
class SmartGloveDll
{
public:
	SmartGloveDll();
	~SmartGloveDll();
};
