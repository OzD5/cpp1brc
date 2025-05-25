#pragma once
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

class Ver1 {
private:
	struct Stats;
	string path;
	void readFile();
public:
	long long runVer1(string path);
};