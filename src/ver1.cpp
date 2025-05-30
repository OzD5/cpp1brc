#include "ver1.h"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <locale>
#include <codecvt>

struct Ver1::Stats
{
	float min;
	float max;
	int count;
	double sum;
};
void Ver1::readFile()
{
	long long cntr = 0;
	std::string line;
	std::ifstream file(this->path);
	std::vector<std::string> cityNames;
	std::unordered_map<std::string, Stats> cities;
	//We know there's 10 000 cities so reserving space for them is faster than letting the vector always dynamically reserve more space
	cityNames.reserve(10000);
	
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << this->path << std::endl;
		return;
	}

	while (getline(file, line))
	{
		std::string city;
		std::string tempstring;
		bool seen = false;

		for (char let : line)
		{
			if (let == ';')
			{
				seen = true;
				continue;
			}
			if (!seen)
				city.push_back(let);
			else
				tempstring.push_back(let);
		}
		float temp = std::stof(tempstring);
		if (cities.find(city) != cities.end())
		{
			auto& cityStat = cities[city]; //No need to lookup everytime
			cityStat.count++;
			cityStat.sum += temp;
			cityStat.min = (cityStat.count == 1) ? temp : std::min(cityStat.min, temp);
			cityStat.max = (cityStat.count == 1) ? temp : std::max(cityStat.max, temp);
		}
		else
		{
			cities[city] = { temp,temp,1,temp };
		}
		
		cntr++;
		if (cntr % 1000000 == 0) std::cout << cntr << "\n";
	}
	cityNames.assign(cities.size(), "");
	for (const auto& cityname : cities)
	{
		cityNames.push_back(cityname.first);
	}

	std::sort(cityNames.begin(), cityNames.end());
	std::cout << "{";
	std::cout << "TESTING";
	for (const auto& city : cityNames)
	{
		const Stats& cur = cities[city];
		std::cout << (city);
		std::cout << "=" << cur.min << "/" << cur.sum / cur.count << "/" << cur.max << ", ";
	}
	std::cout << "}" << "\n";
}

long long Ver1::runVer1(std::string path)
{
	using namespace std::chrono;
	this->path= path;
	auto start = high_resolution_clock::now();

	this->readFile();

	auto end = high_resolution_clock::now();
	auto duration =  duration_cast<microseconds>(end - start);
	return duration.count();
}