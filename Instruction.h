#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include "Memory.h"
#include "Graph.h"
using namespace std;


#pragma once
struct Instructions
{
	bitset<4> opcode_31_28;
	bitset<3> opcode_27_25;
	bitset<5> opcode_24_20;
	bitset<4> opcode_19_16;
	bitset<4> opcode_15_12;
	bitset<4> opcode_11_8;
	bitset<4> opcode_7_4;
	bitset<4> opcode_3_0;
};


#pragma once
struct MemorySet
{
	struct MemoryLine
	{
		vector<Instructions> insts;
		vector<int> tick;
	};
	struct MemoryWay
	{
		vector<MemoryLine> lines;
	};
	vector<MemoryWay> ways;
};


void Bitset_to_Instruction_converter(bitset<32> bitset_inst, Instructions& inst)
{
	bitset<4> a;
	bitset<3> b;
	bitset<5> c;

	a[3] = bitset_inst[31];
	a[2] = bitset_inst[30];
	a[1] = bitset_inst[29];
	a[0] = bitset_inst[28];
	inst.opcode_31_28 = a;
	b[2] = bitset_inst[27];
	b[1] = bitset_inst[26];
	b[0] = bitset_inst[25];
	inst.opcode_27_25 = b;
	c[4] = bitset_inst[24];
	c[3] = bitset_inst[23];
	c[2] = bitset_inst[22];
	c[1] = bitset_inst[21];
	c[0] = bitset_inst[20];
	inst.opcode_24_20 = c;
	a[3] = bitset_inst[19];
	a[2] = bitset_inst[18];
	a[1] = bitset_inst[17];
	a[0] = bitset_inst[16];
	inst.opcode_19_16 = a;
	bitset_inst[15];
	bitset_inst[14];
	bitset_inst[13];
	bitset_inst[12];
	inst.opcode_15_12 = a;
	a[3] = bitset_inst[11];
	a[2] = bitset_inst[10];
	a[1] = bitset_inst[9];
	a[0] = bitset_inst[8];
	inst.opcode_11_8 = a;
	a[3] = bitset_inst[7];
	a[2] = bitset_inst[6];
	a[1] = bitset_inst[5];
	a[0] = bitset_inst[4];
	inst.opcode_7_4 = a;
	a[3] = bitset_inst[3];
	a[2] = bitset_inst[2];
	a[1] = bitset_inst[1];
	a[0] = bitset_inst[0];
	inst.opcode_3_0 = a;
}


void InstructionToBitset(const Instructions& inst, bitset<32>& b)
{
	int i;
	bitset<3> b3;
	bitset<4> b4;
	bitset<5> b5;
	b4 = inst.opcode_31_28;
	b[31] = b4[3];
	b[30] = b4[2];
	b[29] = b4[1];
	b[28] = b4[0];
	b3 = inst.opcode_27_25;
	b[27] = b3[2];
	b[26] = b3[1];
	b[25] = b3[0];
	b5 = inst.opcode_24_20;
	b[24] = b5[4];
	b[23] = b5[3];
	b[22] = b5[2];
	b[21] = b5[1];
	b[20] = b5[0];
	b4 = inst.opcode_19_16;
	b[19] = b4[3];
	b[18] = b4[2];
	b[17] = b4[1];
	b[16] = b4[0];
	b4 = inst.opcode_15_12;
	b[15] = b4[3];
	b[14] = b4[2];
	b[13] = b4[1];
	b[12] = b4[0];
	b4 = inst.opcode_11_8;
	b[11] = b4[3];
	b[10] = b4[2];
	b[9] = b4[1];
	b[8] = b4[0];
	b4 = inst.opcode_7_4;
	b[7] = b4[3];
	b[6] = b4[2];
	b[5] = b4[1];
	b[4] = b4[0];
	b4 = inst.opcode_3_0;
	b[3] = b4[3];
	b[2] = b4[2];
	b[1] = b4[1];
	b[0] = b4[0];
}


void BinaryMemoryCreator(vector<Memory>& memory, vector<MemorySet>& BinaryMemorySet)
{
	int i, j, k, z, m, n, l;
	Instructions inst;
	string STRING, str;
	bitset<8> b;
	bitset<32> instr;

	/*BinaryMemorySet.resize(memory.size());
	for (i = 0; i < BinaryMemorySet.size(); i++)
	{
		BinaryMemorySet[i].ways.resize(memory[i].getAssociativity());
		for (j = 0; j < BinaryMemorySet[i].ways.size(); j++)
		{
			BinaryMemorySet[i].ways[j].lines.resize(memory[i].getBlock(0, 0).BlockData[0].size() / 4);
			for (k = 0; k < BinaryMemorySet[i].ways[j].lines.size(); k++)
			{
			}
		}
	}
	*/
	BinaryMemorySet.resize(memory.size());
	for (i = 0; i < memory.size(); i++)
	{
		BinaryMemorySet[i].ways.resize(memory[i].getAssociativity());
		for (j = 0; j < memory[i].getAssociativity(); j++)
		{
			BinaryMemorySet[i].ways[j].lines.resize(memory[i].getBlock(0, 0).BlockData[0].size() / 4);
			for (k = 0; k < memory[i].getWayBlockNumbers(j); k++)
			{
				for (z = 0, l = 0; z < memory[i].getBlock(j, k).BlockData[0].size() / 4; z++, l += 4)
				{
					STRING.clear();
					for (m = 0; m < 4; m++)
					{
						str.clear();
						str = to_string(memory[i].getBlock(j, k).BlockData[0][m + l] & 255);
						b = bitset<8>(stoi(str));
						str.clear();
						str = b.template to_string<char, char_traits<char>, allocator<char> >();
						STRING += str;
					}
					instr = bitset<32>(STRING.c_str());
					Bitset_to_Instruction_converter(instr, inst);
					BinaryMemorySet[i].ways[j].lines[z].insts.push_back(inst);
					BinaryMemorySet[i].ways[j].lines[z].tick.push_back(memory[i].getBlockTick(j, k));
				}
			}
		}
	}
}


/*void InstructionExtraction(vector<vector<vector<bitset<32>>>>& BinaryMemory, vector<Instructions>& instructions)
{
	int i, j, k, z;
	bitset<4> a;
	bitset<3> b;
	bitset<5> c;
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].size(); j++)
		{
			for (k = 0; k < BinaryMemory[i][j].size(); k++)
			{
				instructions.resize(instructions.size() + 1);
				a[3] = BinaryMemory[i][j][k][31];
				a[2] = BinaryMemory[i][j][k][30];
				a[1] = BinaryMemory[i][j][k][29];
				a[0] = BinaryMemory[i][j][k][28];
				instructions[instructions.size() - 1].opcode_31_28 = a;
				b[2] = BinaryMemory[i][j][k][27];
				b[1] = BinaryMemory[i][j][k][26];
				b[0] = BinaryMemory[i][j][k][25];
				instructions[instructions.size() - 1].opcode_27_25 = b;
				c[4] = BinaryMemory[i][j][k][24];
				c[3] = BinaryMemory[i][j][k][23];
				c[2] = BinaryMemory[i][j][k][22];
				c[1] = BinaryMemory[i][j][k][21];
				c[0] = BinaryMemory[i][j][k][20];
				instructions[instructions.size() - 1].opcode_24_20 = c;
				a[3] = BinaryMemory[i][j][k][19];
				a[2] = BinaryMemory[i][j][k][18];
				a[1] = BinaryMemory[i][j][k][17];
				a[0] = BinaryMemory[i][j][k][16];
				instructions[instructions.size() - 1].opcode_19_16 = a;
				a[3] = BinaryMemory[i][j][k][15];
				a[2] = BinaryMemory[i][j][k][14];
				a[1] = BinaryMemory[i][j][k][13];
				a[0] = BinaryMemory[i][j][k][12];
				instructions[instructions.size() - 1].opcode_15_12 = a;
				a[3] = BinaryMemory[i][j][k][11];
				a[2] = BinaryMemory[i][j][k][10];
				a[1] = BinaryMemory[i][j][k][9];
				a[0] = BinaryMemory[i][j][k][8];
				instructions[instructions.size() - 1].opcode_11_8 = a;
				a[3] = BinaryMemory[i][j][k][7];
				a[2] = BinaryMemory[i][j][k][6];
				a[1] = BinaryMemory[i][j][k][5];
				a[0] = BinaryMemory[i][j][k][4];
				instructions[instructions.size() - 1].opcode_7_4 = a;
				a[3] = BinaryMemory[i][j][k][3];
				a[2] = BinaryMemory[i][j][k][2];
				a[1] = BinaryMemory[i][j][k][1];
				a[0] = BinaryMemory[i][j][k][0];
				instructions[instructions.size() - 1].opcode_3_0 = a;
				instructions[instructions.size() - 1].set = i;
				instructions[instructions.size() - 1].way = j;
			}
		}
	}
}*/


/*void InstructionExtraction(vector<vector<vector<bitset<32>>>>& BinaryMemory, vector<vector<vector<Instructions>>>& InstructionMemory)
{
	int i, j, k;
	bitset<4> a;
	bitset<3> b;
	bitset<5> c;
	Instructions instr;
	InstructionMemory.resize(BinaryMemory.size());
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		InstructionMemory[i].resize(BinaryMemory[i].size());
		for (j = 0; j < BinaryMemory[i].size(); j++)
		{
			InstructionMemory[i][j].resize(BinaryMemory[i][j].size());
			for (k = 0; k < BinaryMemory[i][j].size(); k++)
			{
				a[3] = BinaryMemory[i][j][k][31];
				a[2] = BinaryMemory[i][j][k][30];
				a[1] = BinaryMemory[i][j][k][29];
				a[0] = BinaryMemory[i][j][k][28];
				instr.opcode_31_28 = a;
				//InstructionMemory[InstructionMemory.size() - 1].opcode_31_28 = a;
				b[2] = BinaryMemory[i][j][k][27];
				b[1] = BinaryMemory[i][j][k][26];
				b[0] = BinaryMemory[i][j][k][25];
				instr.opcode_27_25 = b;
				//instructions[instructions.size() - 1].opcode_27_25 = b;
				c[4] = BinaryMemory[i][j][k][24];
				c[3] = BinaryMemory[i][j][k][23];
				c[2] = BinaryMemory[i][j][k][22];
				c[1] = BinaryMemory[i][j][k][21];
				c[0] = BinaryMemory[i][j][k][20];
				instr.opcode_24_20 = c;
				//instructions[instructions.size() - 1].opcode_24_20 = c;
				a[3] = BinaryMemory[i][j][k][19];
				a[2] = BinaryMemory[i][j][k][18];
				a[1] = BinaryMemory[i][j][k][17];
				a[0] = BinaryMemory[i][j][k][16];
				instr.opcode_19_16 = a;
				//instructions[instructions.size() - 1].opcode_19_16 = a;
				a[3] = BinaryMemory[i][j][k][15];
				a[2] = BinaryMemory[i][j][k][14];
				a[1] = BinaryMemory[i][j][k][13];
				a[0] = BinaryMemory[i][j][k][12];
				instr.opcode_15_12 = a;
				//instructions[instructions.size() - 1].opcode_15_12 = a;
				a[3] = BinaryMemory[i][j][k][11];
				a[2] = BinaryMemory[i][j][k][10];
				a[1] = BinaryMemory[i][j][k][9];
				a[0] = BinaryMemory[i][j][k][8];
				instr.opcode_11_8 = a;
				//instructions[instructions.size() - 1].opcode_11_8 = a;
				a[3] = BinaryMemory[i][j][k][7];
				a[2] = BinaryMemory[i][j][k][6];
				a[1] = BinaryMemory[i][j][k][5];
				a[0] = BinaryMemory[i][j][k][4];
				instr.opcode_7_4 = a;
				//instructions[instructions.size() - 1].opcode_7_4 = a;
				a[3] = BinaryMemory[i][j][k][3];
				a[2] = BinaryMemory[i][j][k][2];
				a[1] = BinaryMemory[i][j][k][1];
				a[0] = BinaryMemory[i][j][k][0];
				instr.opcode_3_0 = a;
				//instructions[instructions.size() - 1].opcode_3_0 = a;
				InstructionMemory[i][j].push_back(instr);
				//instructions[instructions.size() - 1].set = i;
				//instructions[instructions.size() - 1].way = j;
			}
		}
	}
}*/


void Opcode_4bit_graph(vector<vector<vector<Instructions>>>& InstructionMemory, Graph& opcodeGraph, int EndofOpcode)
{
	int i, j, k;
	bitset<4> opcode;
	string s;
	for (i = 0; i < InstructionMemory.size(); i++)
	{
		for (j = 0; j < InstructionMemory[i].size(); j++)
		{
			for (k = 0; k < InstructionMemory[i][j].size(); k++)
			{
				if (EndofOpcode == 31)
					opcode = InstructionMemory[i][j][k].opcode_31_28;
				else if (EndofOpcode == 19)
					opcode = InstructionMemory[i][j][k].opcode_19_16;
				else if (EndofOpcode == 15)
					opcode = InstructionMemory[i][j][k].opcode_15_12;
				else if (EndofOpcode == 11)
					opcode = InstructionMemory[i][j][k].opcode_11_8;
				else if (EndofOpcode == 7)
					opcode = InstructionMemory[i][j][k].opcode_7_4;
				else if (EndofOpcode == 3)
					opcode = InstructionMemory[i][j][k].opcode_3_0;
				else
					throw "Wrong Opcode";
				s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
				opcodeGraph.addvertex(s);
			}
		}
	}
	for (graph::const_iterator itr = opcodeGraph.GraphBegin(); itr != opcodeGraph.GraphEnd(); itr++)
	{
		s = opcodeGraph.vertexName(itr);
		opcode = bitset<4>(s.c_str());
		for (i = 0; i < InstructionMemory.size(); i++)
		{
			for (j = 0; j < InstructionMemory[i].size(); j++)
			{
				for (k = 0; k < InstructionMemory[i][j].size(); k++)
				{
					if (EndofOpcode == 31)
						if (opcode == InstructionMemory[i][j][k].opcode_31_28)
							opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_31_28.template to_string<char, char_traits<char>, allocator<char> >());
					
					else if (EndofOpcode == 19)
						if (opcode == InstructionMemory[i][j][k].opcode_19_16)
							opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_19_16.template to_string<char, char_traits<char>, allocator<char> >());

					else if (EndofOpcode == 15)
						if (opcode == InstructionMemory[i][j][k].opcode_15_12)
							opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_15_12.template to_string<char, char_traits<char>, allocator<char> >());

					else if (EndofOpcode == 11)
						if (opcode == InstructionMemory[i][j][k].opcode_11_8)
							opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_11_8.template to_string<char, char_traits<char>, allocator<char> >());

					else if (EndofOpcode == 7)
						if (opcode == InstructionMemory[i][j][k].opcode_7_4)
							opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_31_28.template to_string<char, char_traits<char>, allocator<char> >());

					else if (EndofOpcode == 3)
						if (opcode == InstructionMemory[i][j][k].opcode_3_0)
							opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_31_28.template to_string<char, char_traits<char>, allocator<char> >());
				}
			}
		}
	}
}


void Opcode_4bit_graph(vector<MemorySet>& BinaryMemory, Graph& opcodeGraph, int EndofOpcode)
{
	int i, j, k, z;
	bitset<4> opcode;
	string s, s1;
	graph::const_iterator itr;

	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					if (EndofOpcode == 31)
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_31_28;
					else if (EndofOpcode == 19)
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_19_16;
					else if (EndofOpcode == 15)
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_15_12;
					else if (EndofOpcode == 11)
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_11_8;
					else if (EndofOpcode == 7)
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_7_4;
					else if (EndofOpcode == 3)
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_3_0;
					else
						throw "Wrong Opcode";
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
					if (z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size())
					{
						if (EndofOpcode == 31)
							opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_31_28;
						else if (EndofOpcode == 19)
							opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_19_16;
						else if (EndofOpcode == 15)
							opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_15_12;
						else if (EndofOpcode == 11)
							opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_11_8;
						else if (EndofOpcode == 7)
							opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_7_4;
						else
							opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_3_0;
						s1 = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s1);
						opcodeGraph.addedge(s, s1);
					}
				}
			}
		}
	}
}


void Opcode_3bit_graph(vector<vector<vector<Instructions>>>& InstructionMemory, Graph& opcodeGraph)
{
	int i, j, k;
	bitset<3> opcode;
	string s;
	for (i = 0; i < InstructionMemory.size(); i++)
	{
		for (j = 0; j < InstructionMemory[i].size(); j++)
		{
			for (k = 0; k < InstructionMemory[i][j].size(); k++)
			{
				opcode = InstructionMemory[i][j][k].opcode_27_25;
				s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
				opcodeGraph.addvertex(s);
			}
		}
	}
	for (graph::const_iterator itr = opcodeGraph.GraphBegin(); itr != opcodeGraph.GraphEnd(); itr++)
	{
		s = opcodeGraph.vertexName(itr);
		opcode = bitset<3>(s.c_str());
		for (i = 0; i < InstructionMemory.size(); i++)
		{
			for (j = 0; j < InstructionMemory[i].size(); j++)
			{
				for (k = 0; k < InstructionMemory[i][j].size(); k++)
				{
					if (opcode == InstructionMemory[i][j][k].opcode_27_25)
						opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_27_25.template to_string<char, char_traits<char>, allocator<char> >());
				}
			}
		}
	}
}


void Opcode_3bit_graph(vector<MemorySet>& BinaryMemory, Graph& opcodeGraph)
{
	int i, j, k, z;
	bitset<3> opcode;
	string s, s1;
	graph::const_iterator itr;

	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25;
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
					if (z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size())
					{
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25;
						s1 = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s1);
						opcodeGraph.addedge(s, s1);
					}
				}
			}
		}
	}
}


void Opcode_5bit_graph(vector<vector<vector<Instructions>>>& InstructionMemory, Graph& opcodeGraph)
{
	int i, j, k;
	bitset<5> opcode;
	string s;
	for (i = 0; i < InstructionMemory.size(); i++)
	{
		for (j = 0; j < InstructionMemory[i].size(); j++)
		{
			for (k = 0; k < InstructionMemory[i][j].size(); k++)
			{
				opcode = InstructionMemory[i][j][k].opcode_24_20;
				s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
				opcodeGraph.addvertex(s);
			}
		}
	}
	for (graph::const_iterator itr = opcodeGraph.GraphBegin(); itr != opcodeGraph.GraphEnd(); itr++)
	{
		s = opcodeGraph.vertexName(itr);
		opcode = bitset<5>(s.c_str());
		for (i = 0; i < InstructionMemory.size(); i++)
		{
			for (j = 0; j < InstructionMemory[i].size(); j++)
			{
				for (k = 0; k < InstructionMemory[i][j].size(); k++)
				{
					if (opcode == InstructionMemory[i][j][k].opcode_24_20)
						opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_24_20.template to_string<char, char_traits<char>, allocator<char> >());
				}
			}
		}
	}
}


void Opcode_5bit_graph(vector<MemorySet>& BinaryMemory, Graph& opcodeGraph)
{
	int i, j, k, z;
	bitset<5> opcode;
	string s, s1;
	graph::const_iterator itr;

	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_24_20;
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
					if (z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size())
					{
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_24_20;
						s1 = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s1);
						opcodeGraph.addedge(s, s1);
					}
				}
			}
		}
	}
}


void Register_Opcode_graph(vector<vector<vector<Instructions>>>& InstructionMemory, Graph& opcodeGraph)
{
	int i, j, k;
	bool x, x1;
	bitset<5> b, b1;
	bitset<4> opcode, opcode1, c, c1;
	string s, s1;
	for (i = 0; i < InstructionMemory.size(); i++)
	{
		for (j = 0; j < InstructionMemory[i].size(); j++)
		{
			for (k = 0; k < InstructionMemory[i][j].size(); k++)
			{
				b = InstructionMemory[i][j][k].opcode_24_20;
				b1 = InstructionMemory[i][j][k + 1].opcode_24_20;
				c = InstructionMemory[i][j][k].opcode_7_4;
				c1 = InstructionMemory[i][j][k + 1].opcode_7_4;
				x = ((InstructionMemory[i][j][k].opcode_27_25 == 000) && (InstructionMemory[i][j][k].opcode_24_20 == 10010) &&
					(InstructionMemory[i][j][k].opcode_19_16 == 1111) && (InstructionMemory[i][j][k].opcode_15_12 == 1111) &&
					(InstructionMemory[i][j][k].opcode_11_8 == 1111) && (InstructionMemory[i][j][k].opcode_7_4 == 0001));
				x1 = ((InstructionMemory[i][j][k + 1].opcode_27_25 == 000) && (InstructionMemory[i][j][k + 1].opcode_24_20 == 10010) &&
					(InstructionMemory[i][j][k + 1].opcode_19_16 == 1111) && (InstructionMemory[i][j][k + 1].opcode_15_12 == 1111) &&
					(InstructionMemory[i][j][k + 1].opcode_11_8 == 1111) && (InstructionMemory[i][j][k + 1].opcode_7_4 == 0001));
				if (!(x || ((InstructionMemory[i][j][k].opcode_27_25 == 111) && b[4] == 1) || (InstructionMemory[i][j][k].opcode_27_25 == 101)))
				{
					opcode = InstructionMemory[i][j][k].opcode_19_16;
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
					//***************************************************************************************************
					if (!(x1 || ((InstructionMemory[i][j][k + 1].opcode_27_25 == 111) && b1[4] == 1) || (InstructionMemory[i][j][k + 1].opcode_27_25 == 101)))
					{
						opcode1 = InstructionMemory[i][j][k + 1].opcode_19_16;
						s1 = opcode1.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s1);
						opcodeGraph.addedge(s, s1);
					}
					//***************************************************************************************************
					if (InstructionMemory[i][j][k].opcode_27_25 != 100)
					{
						opcode = InstructionMemory[i][j][k].opcode_15_12;
						s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s);
						//***************************************************************************************************
						if (!(x1 || ((InstructionMemory[i][j][k + 1].opcode_27_25 == 111) && b1[4] == 1) || (InstructionMemory[i][j][k + 1].opcode_27_25 == 101)))
						{
							if (InstructionMemory[i][j][k + 1].opcode_27_25 != 100)
							{
								opcode1 = InstructionMemory[i][j][k + 1].opcode_15_12;
								s1 = opcode1.template to_string<char, char_traits<char>, allocator<char> >();
								opcodeGraph.addvertex(s1);
								opcodeGraph.addedge(s, s1);
							}
						}
						//***************************************************************************************************
					}
				}

				if ((InstructionMemory[i][j][k].opcode_27_25 == 000) || ((InstructionMemory[i][j][k].opcode_27_25 == 000) && b[4] == 0))
				{
					opcode = InstructionMemory[i][j][k].opcode_3_0;
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
					//***************************************************************************************************
					if ((InstructionMemory[i][j][k + 1].opcode_27_25 == 000) || ((InstructionMemory[i][j][k + 1].opcode_27_25 == 000) && b1[4] == 0))
					{
						opcode1 = InstructionMemory[i][j][k + 1].opcode_3_0;
						s1 = opcode1.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s1);
						opcodeGraph.addedge(s, s1);
					}
					//***************************************************************************************************
				}

				if (((InstructionMemory[i][j][k].opcode_27_25 == 000) && (!x) && (c[3] == 0 && c[0] == 1)))
				{
					opcode = InstructionMemory[i][j][k].opcode_11_8;
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
					//***************************************************************************************************
					if (((InstructionMemory[i][j][k + 1].opcode_27_25 == 000) && (!x1) && (c1[3] == 0 && c1[0] == 1)))
					{
						opcode1 = InstructionMemory[i][j][k + 1].opcode_11_8;
						s1 = opcode1.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s1);
						opcodeGraph.addedge(s, s1);
					}
					//***************************************************************************************************
				}
			}
		}
	}
	/*
	for (graph::const_iterator itr = opcodeGraph.GraphBegin(); itr != opcodeGraph.GraphEnd(); itr++)
	{
		s = opcodeGraph.vertexName(itr);
		opcode = bitset<4>(s.c_str());
		for (i = 0; i < InstructionMemory.size(); i++)
		{
			for (j = 0; j < InstructionMemory[i].size(); j++)
			{
				for (k = 0; k < InstructionMemory[i][j].size(); k++)
				{
					if (opcode == InstructionMemory[i][j][k].opcode_24_20)
						opcodeGraph.addedge(opcodeGraph.vertexName(itr), InstructionMemory[i][j][k + 1].opcode_24_20.template to_string<char, char_traits<char>, allocator<char> >());
				}
			}
		}
	}
	*/
}


void Register_Opcode_graph(vector<MemorySet>& BinaryMemory, Graph& opcodeGraph)
{
	int i, j, k, z;
	bool x, x1;
	bitset<5> b, b1;
	bitset<4> opcode, opcode1, c, c1;
	string s, s1;

	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					b = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_24_20;
					b1 = bitset<5>(0);
					c = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_7_4;
					c1 = bitset<4>(0);
					x = ((BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25 == 000) && (BinaryMemory[i].ways[j].lines[k].insts[z].opcode_24_20 == 10010) &&
						(BinaryMemory[i].ways[j].lines[k].insts[z].opcode_19_16 == 1111) && (BinaryMemory[i].ways[j].lines[k].insts[z].opcode_15_12 == 1111) &&
						(BinaryMemory[i].ways[j].lines[k].insts[z].opcode_11_8 == 1111) && (BinaryMemory[i].ways[j].lines[k].insts[z].opcode_7_4 == 0001));
					x1 = false;
					if (z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size())
					{
						b1 = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_24_20;
						c1 = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_7_4;
						x1 = ((BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 == 000) && (BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_24_20 == 10010) &&
							(BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_19_16 == 1111) && (BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_15_12 == 1111) &&
							(BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_11_8 == 1111) && (BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_7_4 == 0001));
					}
					if (!(x || ((BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25 == 111) && b[4] == 1) || (BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25 == 101)))
					{
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_19_16;
						s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s);
						//***************************************************************************************************
						if ((z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size()) && 
							(!(x1 || ((BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 == 111) && b1[4] == 1) || (BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 == 101))))
						{
							opcode1 = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_19_16;
							s1 = opcode1.template to_string<char, char_traits<char>, allocator<char> >();
							opcodeGraph.addvertex(s1);
							opcodeGraph.addedge(s, s1);
						}
						//***************************************************************************************************
						if (BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25 != 100)
						{
							opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_15_12;
							s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
							opcodeGraph.addvertex(s);
							//***************************************************************************************************
							if ((z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size()) && 
								(!(x1 || ((BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 == 111) && b1[4] == 1) || (BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 == 101))))
							{
								if (BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 != 100)
								{
									opcode1 = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_15_12;
									s1 = opcode1.template to_string<char, char_traits<char>, allocator<char> >();
									opcodeGraph.addvertex(s1);
									opcodeGraph.addedge(s, s1);
								}
							}
							//***************************************************************************************************
						}
					}

					if ((BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25 == 000) || ((BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25 == 000) && b[4] == 0))
					{
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_3_0;
						s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s);
						//***************************************************************************************************
						if ((z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size()) &&
							((BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 == 000) || ((BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 == 000) && b1[4] == 0)))
						{
							opcode1 = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_3_0;
							s1 = opcode1.template to_string<char, char_traits<char>, allocator<char> >();
							opcodeGraph.addvertex(s1);
							opcodeGraph.addedge(s, s1);
						}
						//***************************************************************************************************
					}

					if (((BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25 == 000) && (!x) && (c[3] == 0 && c[0] == 1)))
					{
						opcode = BinaryMemory[i].ways[j].lines[k].insts[z].opcode_11_8;
						s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s);
						//***************************************************************************************************
						if ((z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size()) &&
							(((BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25 == 000) && (!x1) && (c1[3] == 0 && c1[0] == 1))))
						{
							opcode1 = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_11_8;
							s1 = opcode1.template to_string<char, char_traits<char>, allocator<char> >();
							opcodeGraph.addvertex(s1);
							opcodeGraph.addedge(s, s1);
						}
						//***************************************************************************************************
					}
				}
			}
		}
	}
}


/*void Register_Opcode_graph(vector<vector<vector<Instructions>>>& InstructionMemory, Graph opcodeGraph)
{
	int i, j, k;
	bool x;
	bitset<5> b;
	bitset<4> opcode, opcode1, c;
	string s, s1;
	for (i = 0; i < InstructionMemory.size(); i++)
	{
		for (j = 0; j < InstructionMemory[i].size(); j++)
		{
			for (k = 0; k < InstructionMemory[i][j].size(); k++)
			{
				b = InstructionMemory[i][j][k].opcode_24_20;
				c = InstructionMemory[i][j][k].opcode_7_4;
				x = ((InstructionMemory[i][j][k].opcode_27_25 == 000) && (InstructionMemory[i][j][k].opcode_24_20 == 10010) &&
					(InstructionMemory[i][j][k].opcode_19_16 == 1111) && (InstructionMemory[i][j][k].opcode_15_12 == 1111) &&
					(InstructionMemory[i][j][k].opcode_11_8 == 1111) && (InstructionMemory[i][j][k].opcode_7_4 == 0001));
				if (!(x || ((InstructionMemory[i][j][k].opcode_27_25 == 111) && b[4] == 1) || (InstructionMemory[i][j][k].opcode_27_25 == 101)))
				{
					opcode = InstructionMemory[i][j][k].opcode_19_16;
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
					if (InstructionMemory[i][j][k].opcode_27_25 != 100)
					{
						opcode = InstructionMemory[i][j][k].opcode_15_12;
						s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						opcodeGraph.addvertex(s);
					}
				}

				if ((InstructionMemory[i][j][k].opcode_27_25 == 000) || ((InstructionMemory[i][j][k].opcode_27_25 == 000) && b[4] == 0))
				{
					opcode = InstructionMemory[i][j][k].opcode_3_0;
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
				}
				if (((InstructionMemory[i][j][k].opcode_27_25 == 000) && (!x) && (c[3] == 0 && c[0] == 1)))
				{
					opcode = InstructionMemory[i][j][k].opcode_11_8;
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					opcodeGraph.addvertex(s);
				}
			}
		}
	}
}*/


template <class bitset, class bitset1, class bitset2> bitset2 Add(const bitset& a, const bitset1& b)
{
	string s, s1;
	s = a.template to_string<char, char_traits<char>, allocator<char> >();
	s1 = b.template to_string<char, char_traits<char>, allocator<char> >();
	s = s + s1;
	return bitset2(s);
}


void SDC_graph(vector<MemorySet>& BinaryMemory, Graph& OpcodeGraph)
{
	int i, j, k, z;
	bitset<8> opcode;
	string s, s1;
	graph::const_iterator itr;

	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					opcode = Add<bitset<3>, bitset<5>, bitset<8>>(BinaryMemory[i].ways[j].lines[k].insts[z].opcode_27_25, BinaryMemory[i].ways[j].lines[k].insts[z].opcode_24_20);
					s = opcode.template to_string<char, char_traits<char>, allocator<char> >();
					OpcodeGraph.addvertex(s);
					if (z + 1 < BinaryMemory[i].ways[j].lines[k].insts.size())
					{
						//opcode = BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25;
						opcode = Add<bitset<3>, bitset<5>, bitset<8>>(BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_27_25, BinaryMemory[i].ways[j].lines[k].insts[z + 1].opcode_24_20);
						s1 = opcode.template to_string<char, char_traits<char>, allocator<char> >();
						OpcodeGraph.addvertex(s1);
						OpcodeGraph.addedge(s, s1);
					}
				}
			}
		}
	}
}