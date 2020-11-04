#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

struct Binary_Memory
{
	struct Line
	{
		vector<bitset<32>> insts;
	};

	struct Memory_Way
	{
		vector<Line> Memory_Line;
	};

	vector<Memory_Way> Memory_Set;
};