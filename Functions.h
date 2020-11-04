#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include "Memory.h"
#include "Types.h"
using namespace std;


struct MemoryContent
{
	int tick;
	int set;
	int way;
	vector<int> data;
};


void Parser(vector<MemoryContent>& MemoryTransactions, string FileName)
{
	string STRING;
	basic_string<char> substr;
	basic_string<char>::size_type indexCh1, indexCh2, indexCh3;
	fstream infile;
	infile.open(FileName, ios::in);
	while (!infile.eof())
	{
		getline(infile, STRING);
		indexCh1 = STRING.find("icache");
		if (indexCh1 != string::npos)
		{
			MemoryTransactions.resize(MemoryTransactions.size() + 1);
			indexCh1 = STRING.find(":");
			substr = STRING.substr(0, indexCh1);
			MemoryTransactions[MemoryTransactions.size() - 1].tick = stoi(substr);
			indexCh1 = STRING.find("data");
			STRING.erase(0, indexCh1 + 5);
			indexCh2 = STRING.find("\t");
			for (indexCh1 = 0; indexCh1 < indexCh2 - 1; indexCh1++)
			{
				indexCh3 = indexCh1;
				indexCh1 = STRING.find(" ", indexCh1);
				substr = STRING.substr(indexCh3, indexCh1 - indexCh3);
				MemoryTransactions[MemoryTransactions.size() - 1].data.push_back(stoi(substr));
			}
			STRING.erase(0, indexCh2 + 5);
			indexCh2 = STRING.find("\t");
			substr = STRING.substr(0, indexCh2 - 1);
			MemoryTransactions[MemoryTransactions.size() - 1].set = stoi(substr);

			STRING.erase(0, indexCh2 + 5);
			indexCh2 = STRING.find("\t");
			substr = STRING.substr(0, indexCh2 - 1);
			MemoryTransactions[MemoryTransactions.size() - 1].way = stoi(substr);
		}
	}
}


void Parser(vector<MemoryContent>& MemoryTransactions, string FileName1, string FileName2, string FileName3)
{
	int Tick, Tick1;
	string STRING;
	basic_string<char> substr;
	basic_string<char>::size_type indexCh1, indexCh2, indexCh3;
	fstream infile;
	infile.open(FileName1, ios::in);
	while (!infile.eof())
	{
		getline(infile, STRING);
		indexCh1 = STRING.find("icache");
		if (indexCh1 != string::npos)
		{
			MemoryTransactions.resize(MemoryTransactions.size() + 1);
			indexCh1 = STRING.find(":");
			substr = STRING.substr(0, indexCh1);
			MemoryTransactions[MemoryTransactions.size() - 1].tick = stoi(substr);
			Tick = MemoryTransactions[MemoryTransactions.size() - 1].tick;
			indexCh1 = STRING.find("data");
			STRING.erase(0, indexCh1 + 5);
			indexCh2 = STRING.find("\t");
			for (indexCh1 = 0; indexCh1 < indexCh2 - 1; indexCh1++)
			{
				indexCh3 = indexCh1;
				indexCh1 = STRING.find(" ", indexCh1);
				substr = STRING.substr(indexCh3, indexCh1 - indexCh3);
				MemoryTransactions[MemoryTransactions.size() - 1].data.push_back(stoi(substr));
			}
			STRING.erase(0, indexCh2 + 5);
			indexCh2 = STRING.find("\t");
			substr = STRING.substr(0, indexCh2 - 1);
			MemoryTransactions[MemoryTransactions.size() - 1].set = stoi(substr);

			STRING.erase(0, indexCh2 + 5);
			indexCh2 = STRING.find("\t");
			substr = STRING.substr(0, indexCh2 - 1);
			MemoryTransactions[MemoryTransactions.size() - 1].way = stoi(substr);
		}
	}
	infile.close();

	infile.open(FileName2, ios::in);
	while (!infile.eof())
	{
		getline(infile, STRING);
		indexCh1 = STRING.find("icache");
		if (indexCh1 != string::npos)
		{
			MemoryTransactions.resize(MemoryTransactions.size() + 1);
			indexCh1 = STRING.find(":");
			substr = STRING.substr(0, indexCh1);
			MemoryTransactions[MemoryTransactions.size() - 1].tick = Tick + stoi(substr);
			Tick1 = MemoryTransactions[MemoryTransactions.size() - 1].tick;
			indexCh1 = STRING.find("data");
			STRING.erase(0, indexCh1 + 5);
			indexCh2 = STRING.find("\t");
			for (indexCh1 = 0; indexCh1 < indexCh2 - 1; indexCh1++)
			{
				indexCh3 = indexCh1;
				indexCh1 = STRING.find(" ", indexCh1);
				substr = STRING.substr(indexCh3, indexCh1 - indexCh3);
				MemoryTransactions[MemoryTransactions.size() - 1].data.push_back(stoi(substr));
			}
			STRING.erase(0, indexCh2 + 5);
			indexCh2 = STRING.find("\t");
			substr = STRING.substr(0, indexCh2 - 1);
			MemoryTransactions[MemoryTransactions.size() - 1].set = stoi(substr);

			STRING.erase(0, indexCh2 + 5);
			indexCh2 = STRING.find("\t");
			substr = STRING.substr(0, indexCh2 - 1);
			MemoryTransactions[MemoryTransactions.size() - 1].way = stoi(substr);
		}
	}
	infile.close();

	infile.open(FileName1, ios::in);
	while (!infile.eof())
	{
		getline(infile, STRING);
		indexCh1 = STRING.find("icache");
		if (indexCh1 != string::npos)
		{
			MemoryTransactions.resize(MemoryTransactions.size() + 1);
			indexCh1 = STRING.find(":");
			substr = STRING.substr(0, indexCh1);
			MemoryTransactions[MemoryTransactions.size() - 1].tick = Tick1 + stoi(substr);
			indexCh1 = STRING.find("data");
			STRING.erase(0, indexCh1 + 5);
			indexCh2 = STRING.find("\t");
			for (indexCh1 = 0; indexCh1 < indexCh2 - 1; indexCh1++)
			{
				indexCh3 = indexCh1;
				indexCh1 = STRING.find(" ", indexCh1);
				substr = STRING.substr(indexCh3, indexCh1 - indexCh3);
				MemoryTransactions[MemoryTransactions.size() - 1].data.push_back(stoi(substr));
			}
			STRING.erase(0, indexCh2 + 5);
			indexCh2 = STRING.find("\t");
			substr = STRING.substr(0, indexCh2 - 1);
			MemoryTransactions[MemoryTransactions.size() - 1].set = stoi(substr);

			STRING.erase(0, indexCh2 + 5);
			indexCh2 = STRING.find("\t");
			substr = STRING.substr(0, indexCh2 - 1);
			MemoryTransactions[MemoryTransactions.size() - 1].way = stoi(substr);
		}
	}
	infile.close();
}


void MemoryGenerator(vector<Memory>& memory, vector<MemoryContent>& MemoryTransactions, int assoc)
{
	int i, j, k;
	bool flag = true;
	Block block;
	block.BlockData.resize(1);
	block.BlockData[0].resize(MemoryTransactions[0].data.size());
	for (i = 0; i < MemoryTransactions.size(); i++)
	{
		flag = true;
		for (j = 0; j < memory.size(); j++)
		{
			if (MemoryTransactions[i].set == memory[j].getSetID())
			{
				block.Tick = MemoryTransactions[i].tick;
				block.wayID = MemoryTransactions[i].way;
				for (k = 0; k < MemoryTransactions[i].data.size(); k++)
					block.BlockData[0][k] = MemoryTransactions[i].data[k];
				memory[j].setBlock(block, block.wayID);
				//memory[j].setSet(MemoryTransactions[i].way, block);
				flag = false;
				break;
			}
		}
		if (flag == true)
		{
			memory.resize(memory.size() + 1);
			memory[memory.size() - 1].setSetID(MemoryTransactions[i].set);
			memory[memory.size() - 1].setAssociativity(assoc);
			//memory[memory.size() - 1].Set(assoc, MemoryTransactions[0].data.size());
			block.Tick = MemoryTransactions[i].tick;
			block.wayID = MemoryTransactions[i].way;
			for (k = 0; k < MemoryTransactions[i].data.size(); k++)
				block.BlockData[0][k] = MemoryTransactions[i].data[k];
			memory[memory.size() - 1].setBlock(block, block.wayID);
			//memory[memory.size() - 1].setSet(MemoryTransactions[i].way, block);
			//memory[memory.size() - 1].setSetID(MemoryTransactions[i].set);
		}
	}
	MemoryTransactions.reserve(0);
	MemoryTransactions.clear();
}


void MemorySort(vector<Memory>& memory)
{
	sort(memory.begin(), memory.end(), [](Memory a, Memory b) { return a.getSetID() < b.getSetID(); });
}


void StringBinaryMemoryCreator(vector<Memory>& memory, vector<vector<vector<string>>>& BinaryMemory, int associativity)
{
	int i, j, k, z, m, n;
	int half;
	string STRING, str;
	bitset<8> b;
	BinaryMemory.resize(memory.size());
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		BinaryMemory[i].resize(associativity);
		for (j = 0; j < BinaryMemory[i].size(); j++)
		{
		//	BinaryMemory[i][j].resize(memory[i].getSet(j).BlockData.size());
			for (k = 0; k < BinaryMemory[i][j].size(); k++)
			{
				for (z = 0; z < 5; z = z + 4)
				{
					for (m = 0; m < 4; m++)
					{
						str.clear();
					//	str = to_string(memory[i].getSet(j).BlockData[k][m + z] & 255);
						b = bitset<8>(str.c_str());
						str.clear();
						str = b.template to_string<char, char_traits<char>, allocator<char> >();
						STRING += str;
					}
					BinaryMemory[i][j][k] = STRING;
				}
			}
		}
	}
	memory.reserve(0);
	memory.clear();
}


void BinaryMemoryCreator(vector<Memory>& memory, vector<vector<vector<vector<bitset<32>>>>>& BinaryMemory, int associativity)
{
	int i, j, k, z, m, n;
	int half;
	string STRING, str;
	bitset<8> b;
	bitset<32> instr;
	BinaryMemory.resize(memory.size());
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		BinaryMemory[i].resize(associativity);
		for (j = 0; j < BinaryMemory[i].size(); j++)
		{
			BinaryMemory[i][j].resize(memory[i].getWayBlockNumbers(j));//memory[i].getBlock(0, 0).BlockData.size());
			//BinaryMemory[i][j].resize(memory[i].getSet(j).BlockData.size());
			for (k = 0; k < BinaryMemory[i][j].size(); k++)
			{
				BinaryMemory[i][j][k].resize(memory[i].getBlock(j, k).BlockData.size());
				for (n = 0; n < BinaryMemory[i][j][k].size(); n++)
				{
					for (z = 0; z < 5; z = z + 4)
					{
						STRING.clear();
						for (m = 0; m < 4; m++)
						{
							str.clear();
							str = to_string(memory[i].getBlock(j, k).BlockData[n][m + z] & 255); //.BlockData[k][m + z] & 255);
							//str = to_string(memory[i].getSet(j).BlockData[k][m + z] & 255);
							b = bitset<8>(stoi(str));
							//b = bitset<8>(str.c_str());
							str.clear();
							str = b.template to_string<char, char_traits<char>, allocator<char> >();
							STRING += str;
						}
						instr = bitset<32>(STRING.c_str());
						BinaryMemory[i][j][k][n] = instr;
					}
				}
				/*
				for (z = 0; z < 5; z = z + 4)
				{
					STRING.clear();
					for (m = 0; m < 4; m++)
					{
						str.clear();
						str = to_string(memory[i].getBlock(j,k).  .BlockData[k][m + z] & 255);
						//str = to_string(memory[i].getSet(j).BlockData[k][m + z] & 255);
						b = bitset<8>(str.c_str());
						str.clear();
						str = b.template to_string<char, char_traits<char>, allocator<char> >();
						STRING += str;
					}
					instr = bitset<32>(STRING.c_str());
					BinaryMemory[i][j][k] = instr;
				}
				*/
			}
		}
	}
	memory.reserve(0);
	memory.clear();
}
