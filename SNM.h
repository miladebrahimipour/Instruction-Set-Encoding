#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include "Instruction.h"
using namespace std;


double SNM_Table(double SP)
{
	if (SP == 0)
		return 0.2;
	else if (SP <= 0.1)
		return 0.16;
	else if (SP <= 0.2)
		return 0.14;
	else if (SP <= 0.3)
		return 0.12;
	else if (SP <= 0.4)
		return 0.1;
	else if (SP <= 0.5)
		return 0.8;
	else if (SP <= 0.6)
		return 0.11;
	else if (SP <= 0.7)
		return 0.13;
	else if (SP <= 0.8)
		return 0.15;
	else if (SP <= 0.9)
		return 0.17;
	else if (SP <= 1)
		return 0.2;
}


#pragma once
struct MemoryProbability
{
	struct MemoryLine
	{
		vector<double> signalProbability;
	};
	struct MemoryWay
	{
		vector<MemoryLine> lines;
	};
	vector<MemoryWay> ways;
};


void ComputeSignalProbability(vector<bitset<32>>& inst, vector<int>& Tick, vector<double>& SP, double& sp)
{
	int i, j;
	int temp, avg, total;
	total = Tick[Tick.size() - 1] - Tick[0];
	if (Tick.size() == 1)
		avg = Tick[0];
	else
		avg = total / Tick.size();
	total += avg;
	SP.resize(32);
	sp = 0;
	for (i = 0; i < 32; i++)
	{
		temp = 0;
		for (j = 0; j < inst.size(); j++)
		{
			if (inst[j][i] == 1)
			{
				if (j != inst.size() - 1)
					temp += (Tick[j + 1] - Tick[j]);
				else
					temp += avg;
			}
		}
		if (temp == 0)
			SP[i] = 0;
		else if (total == 0)
			SP[i] == temp;
		else
			SP[i] = (double)temp / total;
		sp += SP[i];
	}
	sp /= 32;
}


void ComputeSignalProbabilityMax(vector<bitset<32>>& inst, vector<int>& Tick, vector<double>& SP, double& sp)
{
	int i, j;
	int temp, avg, total;
	total = Tick[Tick.size() - 1] - Tick[0];
	avg = total / Tick.size();
	SP.resize(32);
	sp = 0;
	for (i = 0; i < 32; i++)
	{
		temp = 0;
		for (j = 0; j < inst.size(); j++)
		{
			if (inst[j][i] == 1)
			{
				if (j != inst.size() - 1)
					temp += (Tick[j + 1] - Tick[j]);
				else
					temp += avg;
			}
		}
		if (temp == 0)
			SP[i] = 0;
		else if (total == 0)
			SP[i] == temp;
		else
			SP[i] = temp / total;
	}
	sp = *max_element(SP.begin(), SP.end());
}


double SignalProbabilityCalculation(vector<MemorySet>& BinaryMemory, vector<MemoryProbability>& BinaryMemoryProbability)
{
	int i, j, k, z, m = 0;
	bool flag = false;
	vector<int> tick;
	vector<bitset<32>> insts;
	bitset<32> b;
	double s, sp = 0;
	BinaryMemoryProbability.resize(BinaryMemory.size());
	//sp.resize(BinaryMemory.size() * BinaryMemory[0].ways.size() * BinaryMemory[0].ways[0].lines.size());
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		BinaryMemoryProbability[i].ways.resize(BinaryMemory[i].ways.size());
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			BinaryMemoryProbability[i].ways[j].lines.resize(BinaryMemory[i].ways[j].lines.size());
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				flag = false;
				insts.clear();
				tick.clear();
				BinaryMemoryProbability[i].ways[j].lines[k].signalProbability.resize(32);
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					InstructionToBitset(BinaryMemory[i].ways[j].lines[k].insts[z], b);
					insts.push_back(b);
					tick.push_back(BinaryMemory[i].ways[j].lines[k].tick[z]);
					flag = true;
				}
				if (flag == true)
				{
					ComputeSignalProbability(insts, tick, BinaryMemoryProbability[i].ways[j].lines[k].signalProbability, s);
					sp += s;
					m++;
				}
			}
		}
	}
	return sp / m;
}


double SignalProbabilityCalculationMax(vector<MemorySet>& BinaryMemory, vector<MemoryProbability>& BinaryMemoryProbability)
{
	int i, j, k, z, m = 0;
	bool flag = false;
	vector<int> tick;
	vector<bitset<32>> insts;
	bitset<32> b;
	double s, sp = 0;
	BinaryMemoryProbability.resize(BinaryMemory.size());
	//sp.resize(BinaryMemory.size() * BinaryMemory[0].ways.size() * BinaryMemory[0].ways[0].lines.size());
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		BinaryMemoryProbability[i].ways.resize(BinaryMemory[i].ways.size());
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			BinaryMemoryProbability[i].ways[j].lines.resize(BinaryMemory[i].ways[j].lines.size());
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				flag = false;
				insts.clear();
				tick.clear();
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					InstructionToBitset(BinaryMemory[i].ways[j].lines[k].insts[z], b);
					insts.push_back(b);
					tick.push_back(BinaryMemory[i].ways[j].lines[k].tick[z]);
					flag = true;
				}
				if (flag == true)
				{
					ComputeSignalProbabilityMax(insts, tick, BinaryMemoryProbability[i].ways[j].lines[k].signalProbability, s);
					sp = max(sp, s);
					//sp += s;
					//m++;
				}
			}
		}
	}
	return sp;// / m;
}


// SNM Optimization
enum Opt{ opcodes, fields, registers };
typedef pair<graph::const_iterator, int> Node;
typedef pair<bitset<3>, bitset<3>> Opcode;
typedef pair<bitset<4>, bitset<4>> Register;
typedef pair<bitset<5>, bitset<5>> Field;
typedef pair<bitset<8>, bitset<8>> Opcode_8bit;
typedef pair<int, int> NumOfAccess;


template <class bitset> int HammingDistance(bitset a, bitset b)
{
	int i;
	bitset temp;
	temp = a ^ b;
	i = temp.count();
	return i;
}


void BestCode_3bit(vector<Node>& nodes, vector<Opcode>& opcode, vector<bitset<3>>& Available_Codes, graph::const_iterator itr)
{
	int i, j, k;
	unsigned int a;
	int temp, max;
	bool flag = false;
	vector<NumOfAccess> Accesses;
	for (i = 0; i < itr->second->adj.size(); i++)
	{
		//flag = false;
		temp = 0;
		for (j = 0; j < nodes.size() - 1; j++)
		{
			if (itr->second->adj[i].second->opcode == nodes[j].first->first)
			{
				temp += itr->second->adj[i].first;
				Accesses.push_back(make_pair(j, itr->second->adj[i].first));
				//flag = true;
			}
		}
		//if (flag == true)
		//Accesses.push_back(make_pair(j, temp));
	}
	flag = false;
	max = 0;
	for (i = 0; i < Available_Codes.size(); i++)
	{
		temp = 0;
		for (j = 0; j < Accesses.size(); j++)
		{
			//a = HammingDistance<bitset<3>>(Available_Codes[i], bitset<3>(nodes[j].first->first));
			a = HammingDistance<bitset<3>>(Available_Codes[i], opcode[j].second);
			temp += (a * Accesses[j].second);
		}
		if (temp > max)
		{
			max = temp;
			k = i;
			flag = true;
		}
	}
	if (flag == true)
	{
		opcode.push_back(make_pair(bitset<3>(nodes[nodes.size() - 1].first->first), Available_Codes[k]));
		Available_Codes.erase(Available_Codes.begin() + k);
	}
	else
	{
		opcode.push_back(make_pair(bitset<3>(nodes[nodes.size() - 1].first->first), Available_Codes[0]));
		Available_Codes.erase(Available_Codes.begin());
	}
}


void BestCode_4bit(vector<Node>& nodes, vector<Register>& opcode, vector<bitset<4>>& Available_Codes, graph::const_iterator itr)
{
	int i, j, k;
	unsigned int a;
	int temp, max;
	bool flag = false;
	vector<NumOfAccess> Accesses;
	for (i = 0; i < itr->second->adj.size(); i++)
	{
		//flag = false;
		temp = 0;
		for (j = 0; j < nodes.size() - 1; j++)
		{
			if (itr->second->adj[i].second->opcode == nodes[j].first->first)
			{
				temp += itr->second->adj[i].first;
				Accesses.push_back(make_pair(j, itr->second->adj[i].first));
				//flag = true;
			}
		}
		//if (flag == true)
		//Accesses.push_back(make_pair(j, temp));
	}
	flag = false;
	max = 0;
	for (i = 0; i < Available_Codes.size(); i++)
	{
		temp = 0;
		for (j = 0; j < Accesses.size(); j++)
		{
			//a = HammingDistance<bitset<3>>(Available_Codes[i], bitset<3>(nodes[j].first->first));
			a = HammingDistance<bitset<4>>(Available_Codes[i], opcode[j].second);
			temp += (a * Accesses[j].second);
		}
		if (temp > max)
		{
			max = temp;
			k = i;
			flag = true;
		}
	}
	if (flag == true)
	{
		opcode.push_back(make_pair(bitset<4>(nodes[nodes.size() - 1].first->first), Available_Codes[k]));
		Available_Codes.erase(Available_Codes.begin() + k);
	}
	else
	{
		opcode.push_back(make_pair(bitset<4>(nodes[nodes.size() - 1].first->first), Available_Codes[0]));
		Available_Codes.erase(Available_Codes.begin());
	}
}


void BestCode_5bit(vector<Node>& nodes, vector<Field>& opcode, vector<bitset<5>>& Available_Codes, graph::const_iterator itr)
{
	int i, j, k;
	unsigned int a;
	int temp, max;
	bool flag = false;
	vector<NumOfAccess> Accesses;
	for (i = 0; i < itr->second->adj.size(); i++)
	{
		//flag = false;
		temp = 0;
		for (j = 0; j < nodes.size() - 1; j++)
		{
			if (itr->second->adj[i].second->opcode == nodes[j].first->first)
			{
				temp += itr->second->adj[i].first;
				Accesses.push_back(make_pair(j, itr->second->adj[i].first));
				//flag = true;
			}
		}
		//if (flag == true)
		//Accesses.push_back(make_pair(j, temp));
	}
	flag = false;
	max = 0;
	for (i = 0; i < Available_Codes.size(); i++)
	{
		temp = 0;
		for (j = 0; j < Accesses.size(); j++)
		{
			//a = HammingDistance<bitset<3>>(Available_Codes[i], bitset<3>(nodes[j].first->first));
			a = HammingDistance<bitset<5>>(Available_Codes[i], opcode[j].second);
			temp += (a * Accesses[j].second);
		}
		if (temp > max)
		{
			max = temp;
			k = i;
			flag = true;
		}
	}
	if (flag == true)
	{
		opcode.push_back(make_pair(bitset<5>(nodes[nodes.size() - 1].first->first), Available_Codes[k]));
		Available_Codes.erase(Available_Codes.begin() + k);
	}
	else
	{
		opcode.push_back(make_pair(bitset<5>(nodes[nodes.size() - 1].first->first), Available_Codes[0]));
		Available_Codes.erase(Available_Codes.begin());
	}
}


void BestCode_8bit(vector<Node>& nodes, vector<Opcode_8bit>& opcode, vector<bitset<8>>& Available_Codes, graph::const_iterator itr)
{
	int i, j, k;
	unsigned int a;
	int temp, max;
	bool flag = false;
	vector<NumOfAccess> Accesses;
	for (i = 0; i < itr->second->adj.size(); i++)
	{
		//flag = false;
		temp = 0;
		for (j = 0; j < nodes.size() - 1; j++)
		{
			if (itr->second->adj[i].second->opcode == nodes[j].first->first)
			{
				temp += itr->second->adj[i].first;
				Accesses.push_back(make_pair(j, itr->second->adj[i].first));
				//flag = true;
			}
		}
		//if (flag == true)
		//Accesses.push_back(make_pair(j, temp));
	}
	flag = false;
	max = 0;
	for (i = 0; i < Available_Codes.size(); i++)
	{
		temp = 0;
		for (j = 0; j < Accesses.size(); j++)
		{
			//a = HammingDistance<bitset<3>>(Available_Codes[i], bitset<3>(nodes[j].first->first));
			a = HammingDistance<bitset<8>>(Available_Codes[i], opcode[j].second);
			temp += (a * Accesses[j].second);
		}
		if (temp > max)
		{
			max = temp;
			k = i;
			flag = true;
		}
	}
	if (flag == true)
	{
		opcode.push_back(make_pair(bitset<8>(nodes[nodes.size() - 1].first->first), Available_Codes[k]));
		Available_Codes.erase(Available_Codes.begin() + k);
	}
	else
	{
		opcode.push_back(make_pair(bitset<8>(nodes[nodes.size() - 1].first->first), Available_Codes[0]));
		Available_Codes.erase(Available_Codes.begin());
	}
}


/*void Opcode_Optimization(vector<vector<vector<Instructions>>>& InstructionMemory)
{
vector<bitset<3>> opcode3 = { 000, 001, 010, 011, 100, 101, 110, 111 };
vector<bitset<4>> opcode4 = { 0000, 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111 };
vector<bitset<5>> opcode5 = { 00000, 00001, 00010, 00011, 00100, 00101, 00110, 00111, 01000, 01001, 01010, 01011, 01100, 01101, 01110, 01111,
10000, 10001, 10010, 10011, 10100, 10101, 10110, 10111, 11000, 11001, 11010, 11011, 11100, 11101, 11110, 11111 };
int i, j, max = 0, temp = 0;
Graph Opcode_Graph;
graph::const_iterator itr, itr1;
vector<Node> nodes;
vector<Opcode> New_Codes;

Opcode_3bit_graph(InstructionMemory, Opcode_Graph);
for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
{
temp = 0;
for (i = 0; i < itr->second->adj.size(); i++)
temp += itr->second->adj[i].first;
if (temp >= max)
{
max = temp;
itr1 = itr;
}
}
for (i = 0; i < opcode3.size(); i++)
{
if (bitset<3>(itr1->first) == opcode3[i])
opcode3.erase(opcode3.begin() + i);
}
nodes.push_back(make_pair(itr1, max));
New_Codes.push_back(make_pair(bitset<3>(itr1->first), bitset<3>(itr1->first)));
max = 0;
for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
{
temp = 0;
//itr->second->adj
for (i = 0; i < itr->second->adj.size(); i++)
{
for (j = 0; j < nodes.size(); j++)
{
if (itr->second->adj[i].second->opcode == nodes[j].first->first)
{
temp += itr->second->adj[i].first;
}
}
}
if (temp >= max)
{
max = temp;
itr1 = itr;
}
BestCode(nodes, New_Codes, opcode3, itr1);
nodes.push_back(make_pair(itr1, max));
}
}*/


void Opcode_3bit_Optimization(vector<MemorySet>& BinaryMemory, vector<Opcode>& New_Codes)
{
	vector<bitset<3>> opcode3 = { 0, 1, 2, 3, 4, 5, 6, 7 };//{ 000, 001, 010, 011, 100, 101, 110, 111 };
	int i, j, max = 0, temp = 0;
	bool flag = false;
	Graph Opcode_Graph;
	graph::const_iterator itr, itr1, itr2;
	vector<Node> nodes;


	Opcode_3bit_graph(BinaryMemory, Opcode_Graph);
	for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
	{
		temp = 0;
		for (i = 0; i < itr->second->adj.size(); i++)
			temp += itr->second->adj[i].first;
		if (temp >= max)
		{
			max = temp;
			itr1 = itr;
		}
	}
	for (i = 0; i < opcode3.size(); i++)
	{
		if (bitset<3>(itr1->first) == opcode3[i])
			opcode3.erase(opcode3.begin() + i);
	}
	nodes.push_back(make_pair(itr1, max));
	New_Codes.push_back(make_pair(bitset<3>(itr1->first), bitset<3>(itr1->first)));
	while (nodes.size() != Opcode_Graph.getGraphSize())
	{
		max = 0;
		for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
		{
			flag = false;
			temp = 0;
			for (i = 0; i < nodes.size(); i++)
			{
				if (itr->first == nodes[i].first->first)
				{
					flag = true;
					break;
				}
			}
			if (flag == true)
				continue;

			//itr->second->adj
			for (i = 0; i < itr->second->adj.size(); i++)
			{
				for (j = 0; j < nodes.size(); j++)
				{
					if (itr->second->adj[i].second->opcode == nodes[j].first->first)
					{
						temp += itr->second->adj[i].first;
					}
				}
			}
			if (temp >= max)
			{
				max = temp;
				itr1 = itr;
			}
		}
		nodes.push_back(make_pair(itr1, max));
		BestCode_3bit(nodes, New_Codes, opcode3, itr1);
	}
}


void Opcode_4bit_Optimization(vector<MemorySet>& BinaryMemory, vector<Register>& New_Codes, int EndofOpcode)
{
	vector<bitset<4>> opcode4 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int i, j, max = 0, temp = 0;
	bool flag = false;
	Graph Opcode_Graph;
	graph::const_iterator itr, itr1;
	vector<Node> nodes;

	Opcode_4bit_graph(BinaryMemory, Opcode_Graph, EndofOpcode);
	for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
	{
		temp = 0;
		for (i = 0; i < itr->second->adj.size(); i++)
			temp += itr->second->adj[i].first;
		if (temp >= max)
		{
			max = temp;
			itr1 = itr;
		}
	}
	for (i = 0; i < opcode4.size(); i++)
	{
		if (bitset<4>(itr1->first) == opcode4[i])
			opcode4.erase(opcode4.begin() + i);
	}
	nodes.push_back(make_pair(itr1, max));
	New_Codes.push_back(make_pair(bitset<4>(itr1->first), bitset<4>(itr1->first)));
	while (nodes.size() != Opcode_Graph.getGraphSize())
	{
		max = 0;
		for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
		{
			flag = false;
			temp = 0;
			for (i = 0; i < nodes.size(); i++)
			{
				if (itr->first == nodes[i].first->first)
				{
					flag = true;
					break;
				}
			}
			if (flag == true)
				continue;

			//itr->second->adj
			for (i = 0; i < itr->second->adj.size(); i++)
			{
				for (j = 0; j < nodes.size(); j++)
				{
					if (itr->second->adj[i].second->opcode == nodes[j].first->first)
					{
						temp += itr->second->adj[i].first;
					}
				}
			}
			if (temp >= max)
			{
				max = temp;
				itr1 = itr;
			}
		}
		nodes.push_back(make_pair(itr1, max));
		BestCode_4bit(nodes, New_Codes, opcode4, itr1);
	}
}


void Opcode_5bit_Optimization(vector<MemorySet>& BinaryMemory, vector<Field>& New_Codes)
{
	vector<bitset<5>> opcode5 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	int i, j, max = 0, temp = 0;
	bool flag = false;
	Graph Opcode_Graph;
	graph::const_iterator itr, itr1, itr2;
	vector<Node> nodes;

	Opcode_5bit_graph(BinaryMemory, Opcode_Graph);
	for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
	{
		temp = 0;
		for (i = 0; i < itr->second->adj.size(); i++)
			temp += itr->second->adj[i].first;
		if (temp >= max)
		{
			max = temp;
			itr1 = itr;
		}
	}
	for (i = 0; i < opcode5.size(); i++)
	{
		if (bitset<5>(itr1->first) == opcode5[i])
			opcode5.erase(opcode5.begin() + i);
	}
	nodes.push_back(make_pair(itr1, max));
	New_Codes.push_back(make_pair(bitset<5>(itr1->first), bitset<5>(itr1->first)));
	while (nodes.size() != Opcode_Graph.getGraphSize())
	{
		max = 0;
		for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
		{
			flag = false;
			temp = 0;
			for (i = 0; i < nodes.size(); i++)
			{
				if (itr->first == nodes[i].first->first)
				{
					flag = true;
					break;
				}
			}
			if (flag == true)
				continue;

			//itr->second->adj
			for (i = 0; i < itr->second->adj.size(); i++)
			{
				for (j = 0; j < nodes.size(); j++)
				{
					if (itr->second->adj[i].second->opcode == nodes[j].first->first)
					{
						temp += itr->second->adj[i].first;
					}
				}
			}
			if (temp >= max)
			{
				max = temp;
				itr1 = itr;
			}
		}
		nodes.push_back(make_pair(itr1, max));
		BestCode_5bit(nodes, New_Codes, opcode5, itr1);
	}
}


void Register_Optimization(vector<MemorySet>& BinaryMemory, vector<Register>& New_Codes)
{
	vector<bitset<4>> opcode4 = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int i, j, max = 0, temp = 0;
	bool flag = false;
	Graph Opcode_Graph;
	graph::const_iterator itr, itr1, itr2;
	vector<Node> nodes;

	Register_Opcode_graph(BinaryMemory, Opcode_Graph);
	for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
	{
		temp = 0;
		for (i = 0; i < itr->second->adj.size(); i++)
			temp += itr->second->adj[i].first;
		if (temp >= max)
		{
			max = temp;
			itr1 = itr;
		}
	}
	for (i = 0; i < opcode4.size(); i++)
	{
		if (bitset<4>(itr1->first) == opcode4[i])
			opcode4.erase(opcode4.begin() + i);
	}
	nodes.push_back(make_pair(itr1, max));
	New_Codes.push_back(make_pair(bitset<4>(itr1->first), bitset<4>(itr1->first)));
	while (nodes.size() != Opcode_Graph.getGraphSize())
	{
		max = 0;
		for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
		{
			flag = false;
			temp = 0;
			for (i = 0; i < nodes.size(); i++)
			{
				if (itr->first == nodes[i].first->first)
				{
					flag = true;
					break;
				}
			}
			if (flag == true)
				continue;

			//itr->second->adj
			for (i = 0; i < itr->second->adj.size(); i++)
			{
				for (j = 0; j < nodes.size(); j++)
				{
					if (itr->second->adj[i].second->opcode == nodes[j].first->first)
					{
						temp += itr->second->adj[i].first;
					}
				}
			}
			if (temp >= max)
			{
				max = temp;
				itr1 = itr;
			}
		}
		nodes.push_back(make_pair(itr1, max));
		BestCode_4bit(nodes, New_Codes, opcode4, itr1);
	}
}


void Opcode_8bit_Graph_Optimization(vector<MemorySet>& BinaryMemory, vector<Opcode_8bit>& New_Codes)
{
	vector<bitset<8>> opcode8;
	int i, j, max = 0, temp = 0;
	bool flag = false;
	Graph Opcode_Graph;
	graph::const_iterator itr, itr1, itr2;
	vector<Node> nodes;

	for (i = 0; i < 256; i++)
		opcode8.push_back(i);
	SDC_graph(BinaryMemory, Opcode_Graph);
	for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
	{
		temp = 0;
		for (i = 0; i < itr->second->adj.size(); i++)
			temp += itr->second->adj[i].first;
		if (temp >= max)
		{
			max = temp;
			itr1 = itr;
		}
	}
	for (i = 0; i < opcode8.size(); i++)
	{
		if (bitset<8>(itr1->first) == opcode8[i])
			opcode8.erase(opcode8.begin() + i);
	}
	nodes.push_back(make_pair(itr1, max));
	New_Codes.push_back(make_pair(bitset<8>(itr1->first), bitset<8>(itr1->first)));
	while (nodes.size() != Opcode_Graph.getGraphSize())
	{
		max = 0;
		for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
		{
			flag = false;
			temp = 0;
			for (i = 0; i < nodes.size(); i++)
			{
				if (itr->first == nodes[i].first->first)
				{
					flag = true;
					break;
				}
			}
			if (flag == true)
				continue;

			//itr->second->adj
			for (i = 0; i < itr->second->adj.size(); i++)
			{
				for (j = 0; j < nodes.size(); j++)
				{
					if (itr->second->adj[i].second->opcode == nodes[j].first->first)
					{
						temp += itr->second->adj[i].first;
					}
				}
			}
			if (temp >= max)
			{
				max = temp;
				itr1 = itr;
			}
		}
		nodes.push_back(make_pair(itr1, max));
		BestCode_8bit(nodes, New_Codes, opcode8, itr1);
	}
}


void Condition_Replacement(Instructions& inst, vector<Register>& opcode_4bit)
{
	int i;
	for (i = 0; i < opcode_4bit.size(); i++)
	{
		if (inst.opcode_31_28 == opcode_4bit[i].first)
		{
			inst.opcode_31_28 = opcode_4bit[i].second;
			break;
		}
	}
}


void Opcode_Replacement(Instructions& inst, vector<Opcode>& opcode_3bit)
{
	int i;
	for (i = 0; i < opcode_3bit.size(); i++)
	{
		if (inst.opcode_27_25 == opcode_3bit[i].first)
		{
			inst.opcode_27_25 = opcode_3bit[i].second;
			break;
		}
	}
}


void Field_Replacement(Instructions& inst, vector<Field>& opcode_5bit)
{
	int i;
	for (i = 0; i < opcode_5bit.size(); i++)
	{
		if (inst.opcode_24_20 == opcode_5bit[i].first)
		{
			inst.opcode_24_20 = opcode_5bit[i].second;
			break;
		}
	}
}


void Register_Replacement(Instructions& inst, vector<Register>& opcode_4bit)
{
	int i;
	bool x;
	bitset<4> c;
	bitset<5> b;
	b = inst.opcode_24_20;
	c = inst.opcode_7_4;
	x = ((inst.opcode_27_25 == 000) && (inst.opcode_24_20 == 10010) &&
		(inst.opcode_19_16 == 1111) && (inst.opcode_15_12 == 1111) &&
		(inst.opcode_11_8 == 1111) && (inst.opcode_7_4 == 0001));
	for (i = 0; i < opcode_4bit.size(); i++)
	{
		if (!(x || ((inst.opcode_27_25 == 111) && b[4] == 1) || (inst.opcode_27_25 == 101)))
		{
			if (inst.opcode_19_16 == opcode_4bit[i].first)
				inst.opcode_19_16 = opcode_4bit[i].second;
			if (inst.opcode_27_25 != 100)
			{
				if (inst.opcode_15_12 == opcode_4bit[i].first)
					inst.opcode_15_12 = opcode_4bit[i].second;
			}
		}

		if ((inst.opcode_27_25 == 000) || ((inst.opcode_27_25 == 000) && b[4] == 0))
		{
			if (inst.opcode_3_0 == opcode_4bit[i].first)
				inst.opcode_3_0 = opcode_4bit[i].second;
		}

		if (((inst.opcode_27_25 == 000) && (!x) && (c[3] == 0 && c[0] == 1)))
		{
			if (inst.opcode_11_8 == opcode_4bit[i].first)
				inst.opcode_11_8 = opcode_4bit[i].second;
		}
	}
}


void Opcode_8bit_Replacement(Instructions& inst, vector<Opcode_8bit>& opcode_8bit)
{
	int i;
	for (i = 0; i < opcode_8bit.size(); i++)
	{
		if (Add<bitset<3>, bitset<5>, bitset<8>>(inst.opcode_27_25, inst.opcode_24_20) == opcode_8bit[i].first)
		{
			inst.opcode_27_25[2] = opcode_8bit[i].second[7];
			inst.opcode_27_25[1] = opcode_8bit[i].second[6];
			inst.opcode_27_25[0] = opcode_8bit[i].second[5];
			inst.opcode_24_20[4] = opcode_8bit[i].second[4];
			inst.opcode_24_20[3] = opcode_8bit[i].second[3];
			inst.opcode_24_20[2] = opcode_8bit[i].second[2];
			inst.opcode_24_20[1] = opcode_8bit[i].second[1];
			inst.opcode_24_20[0] = opcode_8bit[i].second[0];
			break;
		}
	}
}


void New_Instruction_Memory(vector<MemorySet>& BinaryMemory, vector<Opcode>& opcode_3bit, vector<Register>& opcode_4bit, vector<Register>& register_opcode, vector<Field>& opcode_5bit)
{
	int i, j, k, z;
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					Condition_Replacement(BinaryMemory[i].ways[j].lines[k].insts[z], opcode_4bit);
					Opcode_Replacement(BinaryMemory[i].ways[j].lines[k].insts[z], opcode_3bit);
					Field_Replacement(BinaryMemory[i].ways[j].lines[k].insts[z], opcode_5bit);
					Register_Replacement(BinaryMemory[i].ways[j].lines[k].insts[z], register_opcode);
				}
			}
		}
	}
}


void New_Instruction_Memory(vector<MemorySet>& BinaryMemory, vector<Register>& opcode_4bit, vector<Register>& register_opcode, vector<Opcode_8bit>& opcode_8bit)
{
	int i, j, k, z;
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					Condition_Replacement(BinaryMemory[i].ways[j].lines[k].insts[z], opcode_4bit);
					Opcode_8bit_Replacement(BinaryMemory[i].ways[j].lines[k].insts[z], opcode_8bit);
					Register_Replacement(BinaryMemory[i].ways[j].lines[k].insts[z], register_opcode);
				}
			}
		}
	}
}