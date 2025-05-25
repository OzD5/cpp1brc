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
	string line;
	ifstream file(this->path);
	file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
	unordered_map < string, Stats> cities;
	
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << this->path << std::endl;
		return;
	}
	while (getline(file, line))
	{
		string city;
		string tempstring;
		bool seen = false;
		for (char let : line)
		{
			if (let == ';')
			{
				seen = true;
				continue;
			}
			if (!seen) city.push_back(let);
			else tempstring.push_back(let);
		}
		float temp = stof(tempstring);
		if (cities.find(city) != cities.end())
		{
			cities[city].count++;
			cities[city].sum += temp;
			cities[city].min = min(cities[city].min, temp);
			cities[city].max = max(cities[city].max, temp);
		}
		else
		{
			cities[city].count = 1;
			cities[city].sum = temp;
			cities[city].min = temp;
			cities[city].max = temp;
		}
		cntr++;
		if (cntr % 1000000 == 0) cout << cntr << "\n";
	}
	vector<string> cityNames;
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

	for (auto cityname : cities)
	{
		cityNames.push_back(cityname.first);
	}
	sort(cityNames.begin(), cityNames.end());
	cout << "{";
	for (string city : cityNames)
	{
		Stats cur = cities[city];
		wcout << converter.from_bytes(city);
		cout << "=" << cur.min << "/" << cur.sum / cur.count << "/" << cur.max << ", ";
	}
	cout << "}" << "\n";
}

long long Ver1::runVer1(std::string path)
{
	using namespace chrono;
	this->path= path;
	auto start = high_resolution_clock::now();

	this->readFile();

	auto end = high_resolution_clock::now();
	auto duration =  duration_cast<microseconds>(end - start);
	return duration.count();
}