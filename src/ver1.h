#pragma once
#include <string>
#include <fstream>
#include <chrono>


class Ver1 {
private:
	struct Stats;
	std::string path;
	void readFile();
public:
	long long runVer1(std::string path);
};