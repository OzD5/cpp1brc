#include <iostream> 
#include <string>
#include "ver1.h"
#include "ver2.h"

int main()
{
	std::string path = "Data/measurements.txt";
	std::cout << "Press enter to start: ";
	std::cin.ignore();

	Ver1 version1;
	long long time = version1.runVer1(path);
	std::cout << time/1000000 << " s" << "\n";
	return 0;
}