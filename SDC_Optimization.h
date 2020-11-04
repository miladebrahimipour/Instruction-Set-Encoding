#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <random>
#include <chrono>
#include "Instruction.h"
#include "SNM.h"
using namespace std;


#pragma once
struct Inst
{
	unsigned int inst;
	int ResistanceTime;
	int ResistanceNumber;
};


void AddNode(vector<Inst>& inst, Inst temp_inst)
{
	int i, temp1, temp2;
	bool flag = false;
	stringstream s1, s2;
	bitset<32> b1, b2;
	s1 << std::dec << temp_inst.inst;
	s1 >> temp1;
	b1 = temp1;
	for (i = 0; i < inst.size(); i++)
	{
		s2 << std::dec << inst[i].inst;
		s2 >> temp2;
		b2 = temp2;
		if ((b1 & b2) == b1)
		{
			inst[i].ResistanceTime += temp_inst.ResistanceTime;
			inst[i].ResistanceNumber++;
			flag = true;
			break;
		}
	}
	if (flag == false)
		inst.push_back(temp_inst);
}


void SDC_Graph_Extraction(vector<MemorySet>& BinaryMemory, vector<bitset<8>>& inst, int numberOfInstructions)
{
	//vector<bitset<8>> opcode8;
	int i, j, max, index, temp = 0;
	bool flag = false, flag1 = false;
	Graph Opcode_Graph;
	graph::const_iterator itr, itr1, itr2;
	vector<Node> nodes;
	vector<int> insts_iterations;


	SDC_graph(BinaryMemory, Opcode_Graph);
	for (itr = Opcode_Graph.GraphBegin(); itr != Opcode_Graph.GraphEnd(); itr++)
	{
		temp = 0;
		for (i = 0; i < itr->second->adj.size(); i++)
			temp += itr->second->adj[i].first;
		if (insts_iterations.size() < numberOfInstructions)
		{
			inst.push_back(bitset<8>(itr->first));
			//inst.push_back(stoi(itr->first));
			insts_iterations.push_back(temp);
		}
		else
		{
			max = 0;
			flag1 = false;
			for (i = 0; i < insts_iterations.size(); i++)
			{
				if (temp > max)
				{
					max = temp;
					index = i;
					flag1 = true;
				}
			}
			if (flag1 == true)
			{
				insts_iterations.erase(insts_iterations.begin() + index);
				inst.erase(inst.begin() + index);
				insts_iterations.push_back(temp);
				inst.push_back(bitset<8>(itr->first));
			}
		}
	}
}


/*vector<int> Data_Processing_AND_Analysis(Instructions inst)
{
	vector<int> vulnerable_bits;
	if (inst.opcode_27_25[0] == 0) // Register
	{
		if (inst.opcode_24_20[0] == 0)
		{
			if (inst.opcode_7_4[0] == 0)
			{
				vulnerable_bits.push_back(0);
				vulnerable_bits.push_back(1);
				vulnerable_bits.push_back(2);
				vulnerable_bits.push_back(3);
				vulnerable_bits.push_back(4);
				vulnerable_bits.push_back(5);
				vulnerable_bits.push_back(6);
			    vulnerable_bits.push_back(7);
				vulnerable_bits.push_back(8);
				vulnerable_bits.push_back(9);
				vulnerable_bits.push_back(10);
				vulnerable_bits.push_back(11);
				vulnerable_bits.push_back(12);
				vulnerable_bits.push_back(13);
				vulnerable_bits.push_back(14);
				vulnerable_bits.push_back(15);
				vulnerable_bits.push_back(16);
				vulnerable_bits.push_back(17);
				vulnerable_bits.push_back(18);
				vulnerable_bits.push_back(19);
				vulnerable_bits.push_back(20);
				vulnerable_bits.push_back(21);
				vulnerable_bits.push_back(22);
				vulnerable_bits.push_back(23);
			 // vulnerable_bits.push_back(24);
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
				vulnerable_bits.push_back(27);
				vulnerable_bits.push_back(28);
				vulnerable_bits.push_back(29);
				vulnerable_bits.push_back(30);
				vulnerable_bits.push_back(31);
			}
			else if (inst.opcode_7_4[3] == 0 && inst.opcode_7_4[0] == 1)
			{
				vulnerable_bits.push_back(0);
				vulnerable_bits.push_back(1);
				vulnerable_bits.push_back(2);
				vulnerable_bits.push_back(3);
				vulnerable_bits.push_back(4);
				vulnerable_bits.push_back(5);
				vulnerable_bits.push_back(6);
				vulnerable_bits.push_back(7);
				vulnerable_bits.push_back(8);
				vulnerable_bits.push_back(9);
				vulnerable_bits.push_back(10);
				vulnerable_bits.push_back(11);
				vulnerable_bits.push_back(12);
				vulnerable_bits.push_back(13);
				vulnerable_bits.push_back(14);
				vulnerable_bits.push_back(15);
				vulnerable_bits.push_back(16);
				vulnerable_bits.push_back(17);
				vulnerable_bits.push_back(18);
				vulnerable_bits.push_back(19);
				vulnerable_bits.push_back(20);
				vulnerable_bits.push_back(21);
				vulnerable_bits.push_back(22);
				vulnerable_bits.push_back(23);
			 // vulnerable_bits.push_back(24);
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
				vulnerable_bits.push_back(27);
				vulnerable_bits.push_back(28);
				vulnerable_bits.push_back(29);
				vulnerable_bits.push_back(30);
				vulnerable_bits.push_back(31);
			}
		}
		else
		{
			if (inst.opcode_7_4[0] == 0)
			{
				vulnerable_bits.push_back(0);
				vulnerable_bits.push_back(1);
				vulnerable_bits.push_back(2);
				vulnerable_bits.push_back(3);
				vulnerable_bits.push_back(4);
				vulnerable_bits.push_back(5);
				vulnerable_bits.push_back(6);
				vulnerable_bits.push_back(7);
				vulnerable_bits.push_back(8);
				vulnerable_bits.push_back(9);
				vulnerable_bits.push_back(10);
				vulnerable_bits.push_back(11);
				vulnerable_bits.push_back(12);
				vulnerable_bits.push_back(13);
				vulnerable_bits.push_back(14);
				vulnerable_bits.push_back(15);
				vulnerable_bits.push_back(16);
				vulnerable_bits.push_back(17);
				vulnerable_bits.push_back(18);
				vulnerable_bits.push_back(19);
				vulnerable_bits.push_back(20);
				vulnerable_bits.push_back(21);
				vulnerable_bits.push_back(22);
				vulnerable_bits.push_back(23);
				vulnerable_bits.push_back(24);
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
				vulnerable_bits.push_back(27);
				vulnerable_bits.push_back(28);
				vulnerable_bits.push_back(29);
				vulnerable_bits.push_back(30);
				vulnerable_bits.push_back(31);
			}
			else if (inst.opcode_7_4[3] == 0 && inst.opcode_7_4[0] == 1)
			{
				vulnerable_bits.push_back(0);
				vulnerable_bits.push_back(1);
				vulnerable_bits.push_back(2);
				vulnerable_bits.push_back(3);
			 // vulnerable_bits.push_back(4);
				vulnerable_bits.push_back(5);
				vulnerable_bits.push_back(6);
				vulnerable_bits.push_back(7);
				vulnerable_bits.push_back(8);
				vulnerable_bits.push_back(9);
				vulnerable_bits.push_back(10);
				vulnerable_bits.push_back(11);
				vulnerable_bits.push_back(12);
				vulnerable_bits.push_back(13);
				vulnerable_bits.push_back(14);
				vulnerable_bits.push_back(15);
				vulnerable_bits.push_back(16);
				vulnerable_bits.push_back(17);
				vulnerable_bits.push_back(18);
				vulnerable_bits.push_back(19);
				vulnerable_bits.push_back(20);
				vulnerable_bits.push_back(21);
				vulnerable_bits.push_back(22);
				vulnerable_bits.push_back(23);
				vulnerable_bits.push_back(24);
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
				vulnerable_bits.push_back(27);
				vulnerable_bits.push_back(28);
				vulnerable_bits.push_back(29);
				vulnerable_bits.push_back(30);
				vulnerable_bits.push_back(31);
			}
		}
	}
	else // Immediate
	{
		if (inst.opcode_24_20[0] == 0)
		{
			vulnerable_bits.push_back(0);
			vulnerable_bits.push_back(1);
			vulnerable_bits.push_back(2);
			vulnerable_bits.push_back(3);
			vulnerable_bits.push_back(4);
			vulnerable_bits.push_back(5);
			vulnerable_bits.push_back(6);
			vulnerable_bits.push_back(7);
			vulnerable_bits.push_back(8);
			vulnerable_bits.push_back(9);
			vulnerable_bits.push_back(10);
			vulnerable_bits.push_back(11);
			vulnerable_bits.push_back(12);
			vulnerable_bits.push_back(13);
			vulnerable_bits.push_back(14);
			vulnerable_bits.push_back(15);
			vulnerable_bits.push_back(16);
			vulnerable_bits.push_back(17);
			vulnerable_bits.push_back(18);
			vulnerable_bits.push_back(19);
			vulnerable_bits.push_back(20);
			vulnerable_bits.push_back(21);
			vulnerable_bits.push_back(22);
			vulnerable_bits.push_back(23);
		 // vulnerable_bits.push_back(24);
			if (inst.opcode_7_4[0] == 0 || (inst.opcode_7_4[3] == 0 && inst.opcode_7_4[0] == 1))
			{
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
			}
			vulnerable_bits.push_back(27);
			vulnerable_bits.push_back(28);
			vulnerable_bits.push_back(29);
			vulnerable_bits.push_back(30);
			vulnerable_bits.push_back(31);
		}
		else
		{
			vulnerable_bits.push_back(0);
			vulnerable_bits.push_back(1);
			vulnerable_bits.push_back(2);
			vulnerable_bits.push_back(3);
			vulnerable_bits.push_back(4);
			vulnerable_bits.push_back(5);
			vulnerable_bits.push_back(6);
			vulnerable_bits.push_back(7);
			vulnerable_bits.push_back(8);
			vulnerable_bits.push_back(9);
			vulnerable_bits.push_back(10);
			vulnerable_bits.push_back(11);
			vulnerable_bits.push_back(12);
			vulnerable_bits.push_back(13);
			vulnerable_bits.push_back(14);
			vulnerable_bits.push_back(15);
			vulnerable_bits.push_back(16);
			vulnerable_bits.push_back(17);
			vulnerable_bits.push_back(18);
			vulnerable_bits.push_back(19);
			vulnerable_bits.push_back(20);
			vulnerable_bits.push_back(21);
			vulnerable_bits.push_back(22);
			vulnerable_bits.push_back(23);
			vulnerable_bits.push_back(24);
			if (inst.opcode_7_4[0] == 0 || (inst.opcode_7_4[3] == 0 && inst.opcode_7_4[0] == 1))
			{
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
			}
			vulnerable_bits.push_back(27);
			vulnerable_bits.push_back(28);
			vulnerable_bits.push_back(29);
			vulnerable_bits.push_back(30);
			vulnerable_bits.push_back(31);
		}
	}
	return vulnerable_bits;
}*/


/*vector<int> Data_Processing_EOR_Analysis(Instructions inst)
{
	vector<int> vulnerable_bits;
	if (inst.opcode_27_25[0] == 0) // Register
	{
		if (inst.opcode_24_20[0] == 0)
		{
			if (inst.opcode_7_4[0] == 0)
			{
				vulnerable_bits.push_back(0);
				vulnerable_bits.push_back(1);
				vulnerable_bits.push_back(2);
				vulnerable_bits.push_back(3);
				vulnerable_bits.push_back(4);
				vulnerable_bits.push_back(5);
				vulnerable_bits.push_back(6);
				vulnerable_bits.push_back(7);
				vulnerable_bits.push_back(8);
				vulnerable_bits.push_back(9);
				vulnerable_bits.push_back(10);
				vulnerable_bits.push_back(11);
				vulnerable_bits.push_back(12);
				vulnerable_bits.push_back(13);
				vulnerable_bits.push_back(14);
				vulnerable_bits.push_back(15);
				vulnerable_bits.push_back(16);
				vulnerable_bits.push_back(17);
				vulnerable_bits.push_back(18);
				vulnerable_bits.push_back(19);
				vulnerable_bits.push_back(20);
				vulnerable_bits.push_back(21);
				vulnerable_bits.push_back(22);
				vulnerable_bits.push_back(23);
			 // vulnerable_bits.push_back(24);
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
				vulnerable_bits.push_back(27);
				vulnerable_bits.push_back(28);
				vulnerable_bits.push_back(29);
				vulnerable_bits.push_back(30);
				vulnerable_bits.push_back(31);
			}
			else if (inst.opcode_7_4[3] == 0 && inst.opcode_7_4[0] == 1)
			{
				vulnerable_bits.push_back(0);
				vulnerable_bits.push_back(1);
				vulnerable_bits.push_back(2);
				vulnerable_bits.push_back(3);
				vulnerable_bits.push_back(4);
				vulnerable_bits.push_back(5);
				vulnerable_bits.push_back(6);
				vulnerable_bits.push_back(7);
				vulnerable_bits.push_back(8);
				vulnerable_bits.push_back(9);
				vulnerable_bits.push_back(10);
				vulnerable_bits.push_back(11);
				vulnerable_bits.push_back(12);
				vulnerable_bits.push_back(13);
				vulnerable_bits.push_back(14);
				vulnerable_bits.push_back(15);
				vulnerable_bits.push_back(16);
				vulnerable_bits.push_back(17);
				vulnerable_bits.push_back(18);
				vulnerable_bits.push_back(19);
				vulnerable_bits.push_back(20);
				vulnerable_bits.push_back(21);
				vulnerable_bits.push_back(22);
				vulnerable_bits.push_back(23);
				// vulnerable_bits.push_back(24);
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
				vulnerable_bits.push_back(27);
				vulnerable_bits.push_back(28);
				vulnerable_bits.push_back(29);
				vulnerable_bits.push_back(30);
				vulnerable_bits.push_back(31);
			}
		}
		else
		{
			if (inst.opcode_7_4[0] == 0)
			{
				vulnerable_bits.push_back(0);
				vulnerable_bits.push_back(1);
				vulnerable_bits.push_back(2);
				vulnerable_bits.push_back(3);
				vulnerable_bits.push_back(4);
				vulnerable_bits.push_back(5);
				vulnerable_bits.push_back(6);
				vulnerable_bits.push_back(7);
				vulnerable_bits.push_back(8);
				vulnerable_bits.push_back(9);
				vulnerable_bits.push_back(10);
				vulnerable_bits.push_back(11);
				vulnerable_bits.push_back(12);
				vulnerable_bits.push_back(13);
				vulnerable_bits.push_back(14);
				vulnerable_bits.push_back(15);
				vulnerable_bits.push_back(16);
				vulnerable_bits.push_back(17);
				vulnerable_bits.push_back(18);
				vulnerable_bits.push_back(19);
				vulnerable_bits.push_back(20);
				vulnerable_bits.push_back(21);
				vulnerable_bits.push_back(22);
				vulnerable_bits.push_back(23);
				vulnerable_bits.push_back(24);
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
				vulnerable_bits.push_back(27);
				vulnerable_bits.push_back(28);
				vulnerable_bits.push_back(29);
				vulnerable_bits.push_back(30);
				vulnerable_bits.push_back(31);
			}
			else if (inst.opcode_7_4[3] == 0 && inst.opcode_7_4[0] == 1)
			{
				vulnerable_bits.push_back(0);
				vulnerable_bits.push_back(1);
				vulnerable_bits.push_back(2);
				vulnerable_bits.push_back(3);
				// vulnerable_bits.push_back(4);
				vulnerable_bits.push_back(5);
				vulnerable_bits.push_back(6);
				vulnerable_bits.push_back(7);
				vulnerable_bits.push_back(8);
				vulnerable_bits.push_back(9);
				vulnerable_bits.push_back(10);
				vulnerable_bits.push_back(11);
				vulnerable_bits.push_back(12);
				vulnerable_bits.push_back(13);
				vulnerable_bits.push_back(14);
				vulnerable_bits.push_back(15);
				vulnerable_bits.push_back(16);
				vulnerable_bits.push_back(17);
				vulnerable_bits.push_back(18);
				vulnerable_bits.push_back(19);
				vulnerable_bits.push_back(20);
				vulnerable_bits.push_back(21);
				vulnerable_bits.push_back(22);
				vulnerable_bits.push_back(23);
				vulnerable_bits.push_back(24);
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
				vulnerable_bits.push_back(27);
				vulnerable_bits.push_back(28);
				vulnerable_bits.push_back(29);
				vulnerable_bits.push_back(30);
				vulnerable_bits.push_back(31);
			}
		}
	}
	else // Immediate
	{
		if (inst.opcode_24_20[0] == 0)
		{
			vulnerable_bits.push_back(0);
			vulnerable_bits.push_back(1);
			vulnerable_bits.push_back(2);
			vulnerable_bits.push_back(3);
			vulnerable_bits.push_back(4);
			vulnerable_bits.push_back(5);
			vulnerable_bits.push_back(6);
			vulnerable_bits.push_back(7);
			vulnerable_bits.push_back(8);
			vulnerable_bits.push_back(9);
			vulnerable_bits.push_back(10);
			vulnerable_bits.push_back(11);
			vulnerable_bits.push_back(12);
			vulnerable_bits.push_back(13);
			vulnerable_bits.push_back(14);
			vulnerable_bits.push_back(15);
			vulnerable_bits.push_back(16);
			vulnerable_bits.push_back(17);
			vulnerable_bits.push_back(18);
			vulnerable_bits.push_back(19);
			vulnerable_bits.push_back(20);
			vulnerable_bits.push_back(21);
			vulnerable_bits.push_back(22);
			vulnerable_bits.push_back(23);
			// vulnerable_bits.push_back(24);
			if (inst.opcode_7_4[0] == 0 || (inst.opcode_7_4[3] == 0 && inst.opcode_7_4[0] == 1))
			{
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
			}
			vulnerable_bits.push_back(27);
			vulnerable_bits.push_back(28);
			vulnerable_bits.push_back(29);
			vulnerable_bits.push_back(30);
			vulnerable_bits.push_back(31);
		}
		else
		{
			vulnerable_bits.push_back(0);
			vulnerable_bits.push_back(1);
			vulnerable_bits.push_back(2);
			vulnerable_bits.push_back(3);
			vulnerable_bits.push_back(4);
			vulnerable_bits.push_back(5);
			vulnerable_bits.push_back(6);
			vulnerable_bits.push_back(7);
			vulnerable_bits.push_back(8);
			vulnerable_bits.push_back(9);
			vulnerable_bits.push_back(10);
			vulnerable_bits.push_back(11);
			vulnerable_bits.push_back(12);
			vulnerable_bits.push_back(13);
			vulnerable_bits.push_back(14);
			vulnerable_bits.push_back(15);
			vulnerable_bits.push_back(16);
			vulnerable_bits.push_back(17);
			vulnerable_bits.push_back(18);
			vulnerable_bits.push_back(19);
			vulnerable_bits.push_back(20);
			vulnerable_bits.push_back(21);
			vulnerable_bits.push_back(22);
			vulnerable_bits.push_back(23);
			vulnerable_bits.push_back(24);
			if (inst.opcode_7_4[0] == 0 || (inst.opcode_7_4[3] == 0 && inst.opcode_7_4[0] == 1))
			{
				vulnerable_bits.push_back(25);
				vulnerable_bits.push_back(26);
			}
			vulnerable_bits.push_back(27);
			vulnerable_bits.push_back(28);
			vulnerable_bits.push_back(29);
			vulnerable_bits.push_back(30);
			vulnerable_bits.push_back(31);
		}
	}
	return vulnerable_bits;
}*/


vector<int> SDC_Analysis(bitset<32> bitset_inst)
{
	int i, j;
	unsigned int temp;
	bool flag = false;
	stringstream temp_str;
	vector<int> vulnerable_bits;
	bitset<32> temp_inst, temp_inst1;
	vector<unsigned int> int_Instruction_Set = { 0xf0efffef, 0xf1efffef, 0xf0efff7f, 0xf1efff7f, 0xf1ffffef, 0xf1ffff7f, 0xf2efffff, 0xf3efffff, 0xf3ffffff, 0xf03fff9f,
		                                         0xf0ffff9f, 0xf14ff09f, 0xf12fff1f, 0xf1bff0ff, 0xf1ffffff, 0xf5ffffff, 0xf7ffffef, 0xf7ffff7f, 0xf9ffffff, 0xfbffffff,
		                                         0xfdfff1ff, 0xfefff1ef, 0xfefff1ff, 0xff000000 };
	vector<bitset<32>> Instruction_Set;
	for (i = 0; i < int_Instruction_Set.size(); i++)
	{
		temp_str << std::dec << int_Instruction_Set[i];
		temp_str >> temp;
		Instruction_Set.push_back(temp);
	}
	//InstructionToBitset(inst, bitset_inst);
	for (i = 0; i < bitset_inst.size(); i++)
	{
		flag = false;
		temp_inst = bitset_inst.flip(i);
		for (j = 0; j < Instruction_Set.size(); j++)
		{
			temp_inst1 = temp_inst & Instruction_Set[j];
			if (temp_inst == temp_inst1)
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
			vulnerable_bits.push_back(i);
	}
	return vulnerable_bits;
}


/*void SDC_Analysis(vector<bitset<12>>& inst, double *SDC_Rate)
{
	int i;
	bitset<3> b3;
	bitset<4> b4;
	bitset<5> b5;
	vector<int> vulnerable_bits;
	for (i = 0; i < inst.size(); i++)
	{
		b3[2] = inst[i][11];
		b3[1] = inst[i][10];
		b3[0] = inst[i][9];
		b5[4] = inst[i][8];
		b5[3] = inst[i][7];
		b5[2] = inst[i][6];
		b5[1] = inst[i][5];
		b5[0] = inst[i][4];
		b4[3] = inst[i][3];
		b4[2] = inst[i][2];
		b4[1] = inst[i][1];
		b4[0] = inst[i][0];


		if (b3 == 0)
		{
			if (b4 == 9)
			{
				if (b5[4] == 0 && b5[3] == 0) // Multiply
				{
					vulnerable_bits.push_back(0);
					vulnerable_bits.push_back(1);
					vulnerable_bits.push_back(2);
					vulnerable_bits.push_back(3);
					vulnerable_bits.push_back(4);
					vulnerable_bits.push_back(5);
					vulnerable_bits.push_back(6);
					vulnerable_bits.push_back(7);
					vulnerable_bits.push_back(8);
					vulnerable_bits.push_back(9);
					vulnerable_bits.push_back(10);
					vulnerable_bits.push_back(11);
					vulnerable_bits.push_back(12);
					vulnerable_bits.push_back(13);
					vulnerable_bits.push_back(14);
					vulnerable_bits.push_back(15);
					vulnerable_bits.push_back(16);
					vulnerable_bits.push_back(17);
					vulnerable_bits.push_back(18);
					vulnerable_bits.push_back(19);
					vulnerable_bits.push_back(20);
					vulnerable_bits.push_back(21);
					vulnerable_bits.push_back(22);
					vulnerable_bits.push_back(23);
					vulnerable_bits.push_back(24);
					vulnerable_bits.push_back(25);
					vulnerable_bits.push_back(26);
					vulnerable_bits.push_back(27);
					vulnerable_bits.push_back(28);
					vulnerable_bits.push_back(29);
					vulnerable_bits.push_back(30);
					vulnerable_bits.push_back(31);
				}
				else if (b5[4] == 0 && b5[3] == 1) // Multiply Long
				{
				}
				else if (b5[4] == 1 && b5[3] == 0) // Single Data Swap
				{
				}
			}

			else if ((b4[0] == 0) || (b4[3] == 0 && b4[0] == 1))
			{
				if ((b4[3] == 0 && b4[0] == 1) && (b5 == 18)) // Branch and Exchange
				{
				}
				else // Data Processing Register
				{
				}
			}

			else if (b4 == 11 || b4 == 13 || b4 == 15) // Half Word Data Transfer
			{
				if (b5[2] == 0) // Register Offset
				{
				}
				else // Immediate Offset
				{
				}
			}
		}


		else if (b3 == 1) // Data Processing Immediate
		{

		}


		else if (b3 == 2) // Single Data Transfer Immediate
		{
		}


		else if (b3 == 3)
		{
			if ((b4[0] == 0) || (b4[3] == 0 && b4[0] == 1)) // Single Data Transfer Register
			{
			}
			else // Undefined
			{
			}
		}


		else if (b3 == 4) // Block Data Transfer
		{
		}


		else if (b3 == 5) // Branch
		{
			if (b5[4] == 0) // Branch
			{
			}
			else // Branch with Link
			{
			}
		}


		else if (b3 == 6) // Coprocessor Data Transfer
		{
		}


		else
		{
			if (b5[4] == 0)
			{
				if (b4[0] == 0) // Coprocessor Data Operation
				{
				}
				else // Coprocessor Register Transfer
				{
				}
			}
			else // Software Interrupt
			{
			}
		}
	}
}*/


/*vector<int> SDC_Analysis(vector<bitset<10>>& inst)
{
	int i;
	bitset<3> b3;
	bitset<4> b4;
	bitset<5> b5;
	for (i = 0; i < inst.size(); i++)
	{
		b3[2] = inst[i][11];
		b3[1] = inst[i][10];
		b3[0] = inst[i][9];
		b5[4] = inst[i][8];
		b5[3] = inst[i][7];
		b5[2] = inst[i][6];
		b5[1] = inst[i][5];
		b5[0] = inst[i][4];
		b4[3] = inst[i][3];
		b4[2] = inst[i][2];
		b4[1] = inst[i][1];
		b4[0] = inst[i][0];


		if (b3 == 0)
		{
			if (b4 == 9)
			{
				if (b5[4] == 0 && b5[3] == 0) // Multiply
				{
				}
				else if (b5[4] == 0 && b5[3] == 1) // Multiply Long
				{
				}
				else if (b5[4] == 1 && b5[3] == 0) // Single Data Swap
				{
				}
			}

			else if ((b4[0] == 0) || (b4[3] == 0 && b4[0] == 1))
			{
				if ((b4[3] == 0 && b4[0] == 1) && (b5 == 18)) // Branch and Exchange
				{
				}
				else // Data Processing Register
				{
				}
			}

			else if (b4 == 11 || b4 == 13 || b4 == 15) // Half Word Data Transfer
			{
				if (b5[2] == 0) // Register Offset
				{
				}
				else // Immediate Offset
				{
				}
			}
		}


		else if (b3 == 1) // Data Processing Immediate
		{

		}


		else if (b3 == 2) // Single Data Transfer Immediate
		{
		}


		else if (b3 == 3)
		{
			if ((b4[0] == 0) || (b4[3] == 0 && b4[0] == 1)) // Single Data Transfer Register
			{
			}
			else // Undefined
			{
			}
		}


		else if (b3 == 4) // Block Data Transfer
		{
		}


		else if (b3 == 5) // Branch
		{
			if (b5[4] == 0) // Branch
			{
			}
			else // Branch with Link
			{
			}
		}


		else if (b3 == 6) // Coprocessor Data Transfer
		{
		}


		else
		{
			if (b5[4] == 0)
			{
				if (b4[0] == 0) // Coprocessor Data Operation
				{
				}
				else // Coprocessor Register Transfer
				{
				}
			}
			else // Software Interrupt
			{
			}
		}
	}
}*/


int Max_Tick(const vector<MemorySet>& BinaryMemorySet)
{
	int max = 0;
	int i, j, k, z;
	for (i = 0; i < BinaryMemorySet.size(); i++)
	{
		for (j = 0; j < BinaryMemorySet[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemorySet[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemorySet[i].ways[j].lines[k].tick.size(); z++)
				{
					if (BinaryMemorySet[i].ways[j].lines[k].tick[z] > max)
						max = BinaryMemorySet[i].ways[j].lines[k].tick[z];
				}
			}
		}
	}
	return max;
}


vector<unsigned int> Intrinsic_SDC_Analysis(int n)
{
	int i;
	unsigned int temp;
	stringstream temp_str;
	vector<bitset<32>> Instruction_Set;
	typedef pair<int, double> SDC;
	vector<unsigned int> vulnerable_instructions;
	vector<SDC> intrinsic_SDC;
	/*vector<unsigned int> int_Instruction_Set = { 0xf0efffef, 0xf1efffef, 0xf0efff7f, 0xf1efff7f, 0xf1ffffef, 0xf1ffff7f, 0xf2efffff, 0xf3efffff, 0xf3ffffff, 0xf03fff9f,
		0xf0ffff9f, 0xf14ff09f, 0xf12fff1f, 0xf1bff0ff, 0xf1ffffff, 0xf5ffffff, 0xf7ffffef, 0xf7ffff7f, 0xf9ffffff, 0xfbffffff,
		0xfdfff1ff, 0xfefff1ef, 0xfefff1ff, 0xff000000 };*/
	vector<unsigned int> int_Instruction_Set = { 0xf00fffef, 0xf02fffef, 0xf04fffef, 0xf06fffef, 0xf08fffef, 0xf0afffef, 0xf0cfffef, 0xf0efffef, 0xf18fffef, 0xf1afffef, 
		                                         0xf1cfffef, 0xf1efffef, 0xf00fff7f, 0xf02fff7f, 0xf04fff7f, 0xf06fff7f, 0xf08fff7f, 0xf0afff7f, 0xf0cfff7f, 0xf0efff7f,
												 0xf18fff7f, 0xf1afff7f, 0xf1cfff7f, 0xf1efff7f, 0xf01fffef, 0xf03fffef, 0xf05fffef, 0xf07fffef, 0xf09fffef, 0xf0bfffef,
												 0xf0dfffef, 0xf0ffffef, 0xf11fffef, 0xf13fffef, 0xf15fffef, 0xf17fffef, 0xf19fffef, 0xf1bfffef, 0xf1dfffef, 0xf1ffffef,
												 0xf01fff7f, 0xf03fff7f, 0xf05fff7f, 0xf07fff7f, 0xf09fff7f, 0xf0bfff7f, 0xf0dfff7f, 0xf0ffff7f, 0xf11fff7f, 0xf13fff7f, 
												 0xf15fff7f, 0xf17fff7f, 0xf19fff7f, 0xf1bfff7f, 0xf1dfff7f, 0xf1ffff7f, 0xf20fffff, 0xf22fffff, 0xf24fffff, 0xf26fffff, 
												 0xf28fffff, 0xf2afffff, 0xf2cfffff, 0xf2efffff, 0xf38fffff, 0xf3afffff, 0xf3cfffff, 0xf3efffff, 0xf21fffff, 0xf23fffff, 
												 0xf25fffff, 0xf27fffff, 0xf29fffff, 0xf2bfffff, 0xf2dfffff, 0xf2ffffff, 0xf31fffff, 0xf33fffff, 0xf35fffff, 0xf37fffff, 
												 0xf39fffff, 0xf3bfffff, 0xf3dfffff, 0xf3ffffff, 0xf00fff9f, 0xf01fff9f, 0xf02fff9f, 0xf03fff9f, 0xf08fff9f, 0xf09fff9f, 
												 0xf0afff9f, 0xf0bfff9f, 0xf0cfff9f, 0xf0dfff9f, 0xf0efff9f, 0xf0ffff9f, 0xf10ff09f, 0xf14ff09f, 0xf12fff1e, 0xf00ff0ff, 
												 0xf01ff0ff, 0xf02ff0ff, 0xf03ff0ff, 0xf08ff0ff, 0xf09ff0ff, 0xf0aff0ff, 0xf0bff0ff, 0xf10ff0ff, 0xf11ff0ff, 0xf12ff0ff, 
												 0xf13ff0ff, 0xf18ff0ff, 0xf19ff0ff, 0xf1aff0ff, 0xf1bff0ff, 0xf04fffff, 0xf05fffff, 0xf06fffff, 0xf07fffff, 0xf0cfffff, 
												 0xf0dfffff, 0xf0efffff, 0xf0ffffff, 0xf14fffff, 0xf15fffff, 0xf16fffff, 0xf17fffff, 0xf1cfffff, 0xf1dfffff, 0xf1efffff, 
												 0xf1ffffff, 0xf5ffffff, 0xf7ffffef, 0xf7ffff7f, 0xf9ffffff, 0xfbffffff, 0xfdfff1ff, 0xfefff1ef, 0xfefff1ff, 0xff000000 };
	for (i = 0; i < int_Instruction_Set.size(); i++)
	{
		temp_str << std::dec << int_Instruction_Set[i];
		temp_str >> temp;
		Instruction_Set.push_back(int_Instruction_Set[i]);// temp);
	}
	for (i = 0; i < Instruction_Set.size(); i++)
	{
		intrinsic_SDC.resize(intrinsic_SDC.size() + 1);
		intrinsic_SDC[intrinsic_SDC.size() - 1].first = i;
		intrinsic_SDC[intrinsic_SDC.size() - 1].second = (double)SDC_Analysis(Instruction_Set[i]).size() / 32;
		//intrinsic_SDC.push_back((double)SDC_Analysis(Instruction_Set[i]).size() / 32);
	}
	stable_sort(intrinsic_SDC.begin(), intrinsic_SDC.end(), [](SDC a, SDC b){ return (a.second > b.second); });
	for (i = 0; i < n; i++)
		vulnerable_instructions.push_back(int_Instruction_Set[intrinsic_SDC[i].first]);
	return vulnerable_instructions;
}


vector<unsigned int> Aging_aware_SDC_Analysis(vector<MemorySet>& BinaryMemorySet, int n)
{
	int i, j, k, z;
	int max_tick;
	Inst temp_inst;
	bitset<32> bitset_inst;
	vector<unsigned int> vulnerable_instructions;
	vector<Inst> inst;
	vector<unsigned int> int_Instruction_Set = { 0xf00fffef, 0xf02fffef, 0xf04fffef, 0xf06fffef, 0xf08fffef, 0xf0afffef, 0xf0cfffef, 0xf0efffef, 0xf18fffef, 0xf1afffef,
												 0xf1cfffef, 0xf1efffef, 0xf00fff7f, 0xf02fff7f, 0xf04fff7f, 0xf06fff7f, 0xf08fff7f, 0xf0afff7f, 0xf0cfff7f, 0xf0efff7f,
												 0xf18fff7f, 0xf1afff7f, 0xf1cfff7f, 0xf1efff7f, 0xf01fffef, 0xf03fffef, 0xf05fffef, 0xf07fffef, 0xf09fffef, 0xf0bfffef,
												 0xf0dfffef, 0xf0ffffef, 0xf11fffef, 0xf13fffef, 0xf15fffef, 0xf17fffef, 0xf19fffef, 0xf1bfffef, 0xf1dfffef, 0xf1ffffef,
												 0xf01fff7f, 0xf03fff7f, 0xf05fff7f, 0xf07fff7f, 0xf09fff7f, 0xf0bfff7f, 0xf0dfff7f, 0xf0ffff7f, 0xf11fff7f, 0xf13fff7f,
												 0xf15fff7f, 0xf17fff7f, 0xf19fff7f, 0xf1bfff7f, 0xf1dfff7f, 0xf1ffff7f, 0xf20fffff, 0xf22fffff, 0xf24fffff, 0xf26fffff,
												 0xf28fffff, 0xf2afffff, 0xf2cfffff, 0xf2efffff, 0xf38fffff, 0xf3afffff, 0xf3cfffff, 0xf3efffff, 0xf21fffff, 0xf23fffff,
												 0xf25fffff, 0xf27fffff, 0xf29fffff, 0xf2bfffff, 0xf2dfffff, 0xf2ffffff, 0xf31fffff, 0xf33fffff, 0xf35fffff, 0xf37fffff,
												 0xf39fffff, 0xf3bfffff, 0xf3dfffff, 0xf3ffffff, 0xf00fff9f, 0xf01fff9f, 0xf02fff9f, 0xf03fff9f, 0xf08fff9f, 0xf09fff9f,
												 0xf0afff9f, 0xf0bfff9f, 0xf0cfff9f, 0xf0dfff9f, 0xf0efff9f, 0xf0ffff9f, 0xf10ff09f, 0xf14ff09f, 0xf12fff1e, 0xf00ff0ff,
												 0xf01ff0ff, 0xf02ff0ff, 0xf03ff0ff, 0xf08ff0ff, 0xf09ff0ff, 0xf0aff0ff, 0xf0bff0ff, 0xf10ff0ff, 0xf11ff0ff, 0xf12ff0ff,
												 0xf13ff0ff, 0xf18ff0ff, 0xf19ff0ff, 0xf1aff0ff, 0xf1bff0ff, 0xf04fffff, 0xf05fffff, 0xf06fffff, 0xf07fffff, 0xf0cfffff,
												 0xf0dfffff, 0xf0efffff, 0xf0ffffff, 0xf14fffff, 0xf15fffff, 0xf16fffff, 0xf17fffff, 0xf1cfffff, 0xf1dfffff, 0xf1efffff,
												 0xf1ffffff, 0xf5ffffff, 0xf7ffffef, 0xf7ffff7f, 0xf9ffffff, 0xfbffffff, 0xfdfff1ff, 0xfefff1ef, 0xfefff1ff, 0xff000000 };
	for (i = 0; i < int_Instruction_Set.size(); i++)
	{
		temp_inst.inst = int_Instruction_Set[i];
		temp_inst.ResistanceTime = 0;
		temp_inst.ResistanceNumber = 0;
		AddNode(inst, temp_inst);
	}
	max_tick = Max_Tick(BinaryMemorySet);
	for (i = 0; i < BinaryMemorySet.size(); i++)
	{
		for (j = 0; j < BinaryMemorySet[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemorySet[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemorySet[i].ways[j].lines[k].insts.size(); z++)
				{
					InstructionToBitset(BinaryMemorySet[i].ways[j].lines[k].insts[z], bitset_inst);
					temp_inst.inst = static_cast<unsigned int>(bitset_inst.to_ulong());
					if (z == BinaryMemorySet[i].ways[j].lines[k].insts.size() - 1)
						temp_inst.ResistanceTime = max_tick - BinaryMemorySet[i].ways[j].lines[k].tick[z];
					else
						temp_inst.ResistanceTime = BinaryMemorySet[i].ways[j].lines[k].tick[z + 1] - BinaryMemorySet[i].ways[j].lines[k].tick[z];
					temp_inst.ResistanceNumber = 1;
					AddNode(inst, temp_inst);
				}
			}
		}
	}
	stable_sort(inst.begin(), inst.end(), [](Inst a, Inst b){return (((double)a.ResistanceTime / a.ResistanceNumber) > ((double)(b.ResistanceTime / b.ResistanceNumber))); });
	for (i = 0; i < n; i++)
		vulnerable_instructions.push_back(inst[i].inst);
	return vulnerable_instructions;
}


vector<unsigned int> Vulnerable_Instruction_Set_Extraction(vector<MemorySet>& BinaryMemorySet, int n, int n1)
{
	vector<unsigned int> vulnerable_instructions, aging_aware_vulnerable_instructions;
	vulnerable_instructions = Intrinsic_SDC_Analysis(n);
	aging_aware_vulnerable_instructions = Aging_aware_SDC_Analysis(BinaryMemorySet, n1);
	vulnerable_instructions.insert(vulnerable_instructions.end(), aging_aware_vulnerable_instructions.begin(), aging_aware_vulnerable_instructions.end());
	return vulnerable_instructions;
}


void Vulnerable_Bit_Set(vector<unsigned int>& int_vulnerable_instructions, vector<vector<int>>& vulnerable_bits)
{
	int i;
	unsigned int temp;
	stringstream temp_str;
	vector<bitset<32>> vulnerable_instructions;

	for (i = 0; i < int_vulnerable_instructions.size(); i++)
	{
		temp_str << std::dec << int_vulnerable_instructions[i];
		temp_str >> temp;
		vulnerable_instructions.push_back(temp);
	}
	//vulnerable_bits.resize(vulnerable_instructions.size());
	for (i = 0; i < vulnerable_instructions.size(); i++)
	{
		vulnerable_bits.push_back(SDC_Analysis(vulnerable_instructions[i]));
	}
}


struct EDC
{
	bitset<1> EDC1;
	bitset<1> EDC2;
	bitset<1> EDC3;
	bitset<1> EDC4;
	int set;
	int way;
	int line;
	int inst;
	//int start_time;
	//int stop_time;
	vector<int> vulnerable_bits;
};


template <class bitn> void Error_Detection_Coding(bitn instruction, vector<int>& vulnerable_bits, EDC& edc)
{
	int i;
	bitn inst;
	inst = instruction;
	//bitset<1> EDC1, EDC2, EDC3, EDC4;
	
	edc.EDC1 = instruction[0] ^ instruction[1] ^ instruction[2] ^ instruction[3];
	edc.EDC2 = instruction[4] ^ instruction[5] ^ instruction[6] ^ instruction[7];
	edc.EDC3 = instruction[8] ^ instruction[9] ^ instruction[10] ^ instruction[11];
	edc.EDC4 = instruction[12] ^ instruction[13] ^ instruction[14] ^ instruction[15] ^ instruction[16] ^ instruction[17] ^ instruction[18] ^
		instruction[19] ^ instruction[20] ^ instruction[21] ^ instruction[22] ^ instruction[23] ^ instruction[24] ^ instruction[25] ^ instruction[26] ^
		instruction[27] ^ instruction[28] ^ instruction[29] ^ instruction[30] ^ instruction[31];
	/*
	for (i = 13; i < instruction.size() - 1; i++)
	{
		temp1 = instruction[i];
		temp = edc.EDC4 ^ temp1;
		edc.EDC4 = temp;
	}*/
}


template <class bitn> void Error_Detection_Coding(bitn instruction, EDC& edc)
{
	int i;
	bitn inst;
	inst = instruction;
	//bitset<1> EDC1, EDC2, EDC3, EDC4;

	edc.EDC1 = instruction[0] ^ instruction[1] ^ instruction[2] ^ instruction[3];
	edc.EDC2 = instruction[4] ^ instruction[5] ^ instruction[6] ^ instruction[7];
	edc.EDC3 = instruction[8] ^ instruction[9] ^ instruction[10] ^ instruction[11];
	edc.EDC4 = instruction[12] ^ instruction[13] ^ instruction[14] ^ instruction[15] ^ instruction[16] ^ instruction[17] ^ instruction[18] ^
		instruction[19] ^ instruction[20] ^ instruction[21] ^ instruction[22] ^ instruction[23] ^ instruction[24] ^ instruction[25] ^ instruction[26] ^
		instruction[27] ^ instruction[28] ^ instruction[29] ^ instruction[30] ^ instruction[31];
}


vector<EDC> SDC_Optimization(vector<MemoryContent>& MemoryTransactions, vector<Memory>& memory, vector<MemorySet>& BinaryMemory, vector<unsigned int>& vulnerable_instructions, vector<vector<int>>& vulnerable_bits, int assoc, string s, string s1, string s2, int n, int n1)
{
	int i, j, k, z, l;
	unsigned int temp;
	int max_tick;
	//vector<unsigned int> vulnerable_instructions;
	//vector<vector<int>> vulnerable_bits;
	bitset<32> bitset_inst, bitset_vulnerable_instruction, temp1;
	vector<EDC> Error_Detection;
	EDC edc;
	Parser(MemoryTransactions, s, s1, s2);
	MemoryGenerator(memory, MemoryTransactions, assoc);
	MemorySort(memory);
	BinaryMemoryCreator(memory, BinaryMemory);
	vulnerable_instructions = Vulnerable_Instruction_Set_Extraction(BinaryMemory, n, n1);
	Vulnerable_Bit_Set(vulnerable_instructions, vulnerable_bits);
	max_tick = Max_Tick(BinaryMemory);
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					InstructionToBitset(BinaryMemory[i].ways[j].lines[k].insts[z], bitset_inst);
					temp = static_cast<unsigned int>(bitset_inst.to_ulong());
					for (l = 0; l < vulnerable_instructions.size(); l++)
					{
						bitset_vulnerable_instruction = vulnerable_instructions[l];
						temp1 = bitset_inst & bitset_vulnerable_instruction;
						//if (temp == vulnerable_instructions[i])
						if (temp1 == bitset_vulnerable_instruction)
						{
							Error_Detection_Coding<bitset<32>>(vulnerable_instructions[i], vulnerable_bits[l], edc);
							edc.set = i;
							edc.way = j;
							edc.line = k;
							edc.inst = z;
							//edc.start_time = BinaryMemory[i].ways[j].lines[k].tick[z];
							//if (BinaryMemory[i].ways[j].lines[k].tick[z] < BinaryMemory[i].ways[j].lines[k].tick.size() - 1)
								//edc.stop_time = BinaryMemory[i].ways[j].lines[k].tick[z + 1];
							//else
								//edc.stop_time = max_tick;
							edc.vulnerable_bits = vulnerable_bits[l];
							Error_Detection.push_back(edc);
						}
					}
				}
			}
		}
	}
	return Error_Detection;
}