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
#include "SDC_Optimization.h"
using namespace std;


double Noise_Table(double DCR, int mode = 0)
{
	if (mode == 0)
		return 1.33;
	else
	{
		if (DCR == 0)
			return 0.6;
		else if (DCR <= 0.1)
			return 0.7;
		else if (DCR <= 0.2)
			return 0.8;
		else if (DCR <= 0.3)
			return 0.9;
		else if (DCR <= 0.4)
			return 1.1;
		else if (DCR <= 0.5)
			return 1.3;
		else if (DCR <= 0.6)
			return 1.15;
		else if (DCR <= 0.7)
			return 0.95;
		else if (DCR <= 0.8)
			return 0.85;
		else if (DCR <= 0.9)
			return 0.75;
		else if (DCR <= 1)
			return 0.65;
	}
}


#pragma once
struct Noise
{
	int set;
	int way;
	int line;
	int inst;
	int bit;
	double noise;
};


bool SDC_Occured(bitset<32> instruction)
{
	int i;
	bitset<32> inst, temp_inst;
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
		inst = int_Instruction_Set[i];
		temp_inst = instruction & inst;
		if (temp_inst == inst)
			return true;
	}
	return false;
}


bool SDC_Occured_Selective(bitset<32> instruction, EDC edc)
{
	int i;
	bitset<32> inst, temp_inst;
	EDC edc1;
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
		inst = int_Instruction_Set[i];
		temp_inst = instruction & inst;
		if (temp_inst == inst)
		{
			Error_Detection_Coding<bitset<32>>(instruction, edc.vulnerable_bits, edc1);
			if ((edc.EDC1 != edc1.EDC1) || (edc.EDC2 != edc1.EDC2) || (edc.EDC3 != edc1.EDC3) || (edc.EDC4 != edc1.EDC4))
				return true;
		}
	}
	return false;
}


bool SDC_Occured(bitset<32> instruction, EDC edc)
{
	int i;
	bitset<32> inst, temp_inst;
	EDC edc1;
	Error_Detection_Coding<bitset<32>>(instruction, edc.vulnerable_bits, edc1);
	if ((edc.EDC1 != edc1.EDC1) || (edc.EDC2 != edc1.EDC2) || (edc.EDC3 != edc1.EDC3) || (edc.EDC4 != edc1.EDC4))
		return true;
	return false;
}


double Noise_Injector(vector<MemorySet> BinaryMemory, const vector<MemoryProbability>& memoryProbability, vector<Noise>& noise, int iterationNumber, int numberOfNoise, int mode = 0)
{
	int i;
	double DCR;
	bitset<32> bitset_inst;
	int count = 0;

	for (i = iterationNumber * numberOfNoise; i < (iterationNumber + 1) * numberOfNoise; i++)
	{
		switch (noise[i].bit)
		{
		case 0:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[0];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[0].flip();
			break;
		case 1:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[1];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[1].flip();
			break;
		case 2:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[2];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[2].flip();
			break;
		case 3:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[3];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[3].flip();
			break;
		case 4:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[4];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[0].flip();
			break;
		case 5:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[5];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[1].flip();
			break;
		case 6:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[6];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[2].flip();
			break;
		case 7:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[7];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[3].flip();
			break;
		case 8:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[8];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[0].flip();
			break;
		case 9:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[9];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[1].flip();
			break;
		case 10:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[10];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[2].flip();
			break;
		case 11:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[11];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[3].flip();
			break;
		case 12:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[12];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[0].flip();
			break;
		case 13:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[13];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[1].flip();
			break;
		case 14:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[14];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[2].flip();
			break;
		case 15:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[15];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[3].flip();
			break;
		case 16:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[16];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[0].flip();
			break;
		case 17:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[17];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[1].flip();
			break;
		case 18:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[18];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[2].flip();
			break;
		case 19:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[19];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[3].flip();
			break;
		case 20:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[20];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[0].flip();
			break;
		case 21:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[21];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[1].flip();
			break;
		case 22:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[22];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[2].flip();
			break;
		case 23:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[23];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[3].flip();
			break;
		case 24:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[24];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[4].flip();
			break;
		case 25:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[25];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[0].flip();
			break;
		case 26:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[26];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[1].flip();
			break;
		case 27:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[27];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[2].flip();
			break;
		case 28:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[28];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[0].flip();
			break;
		case 29:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[29];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[1].flip();
			break;
		case 30:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[30];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[2].flip();
			break;
		case 31:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[31];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[3].flip();
			break;
		default:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[0];
			if (noise[i].noise >= Noise_Table(DCR, mode))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[0].flip();
			break;
		}
		InstructionToBitset(BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst], bitset_inst);
		if (SDC_Occured(bitset_inst))
			count++;
	}
	return ((double)count / numberOfNoise);
}


double Noise_Injector(vector<MemorySet> BinaryMemory, const vector<MemoryProbability>& memoryProbability, vector<unsigned int>& vulnerable_instructions, vector<Noise>& noise, vector<EDC>& edc, int iterationNumber, int numberOfNoise)
{
	int i, j;
	double DCR;
	bitset<32> bitset_inst;
	int count = 0;
	bool flag = false;

	for (i = iterationNumber * numberOfNoise; i < (iterationNumber + 1) * numberOfNoise; i++)
	{
		switch (noise[i].bit)
		{
		case 0:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[0];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[0].flip();
			break;
		case 1:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[1];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[1].flip();
			break;
		case 2:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[2];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[2].flip();
			break;
		case 3:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[3];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[3].flip();
			break;
		case 4:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[4];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[0].flip();
			break;
		case 5:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[5];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[1].flip();
			break;
		case 6:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[6];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[2].flip();
			break;
		case 7:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[7];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[3].flip();
			break;
		case 8:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[8];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[0].flip();
			break;
		case 9:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[9];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[1].flip();
			break;
		case 10:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[10];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[2].flip();
			break;
		case 11:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[11];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[3].flip();
			break;
		case 12:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[12];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[0].flip();
			break;
		case 13:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[13];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[1].flip();
			break;
		case 14:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[14];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[2].flip();
			break;
		case 15:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[15];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[3].flip();
			break;
		case 16:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[16];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[0].flip();
			break;
		case 17:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[17];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[1].flip();
			break;
		case 18:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[18];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[2].flip();
			break;
		case 19:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[19];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[3].flip();
			break;
		case 20:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[20];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[0].flip();
			break;
		case 21:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[21];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[1].flip();
			break;
		case 22:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[22];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[2].flip();
			break;
		case 23:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[23];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[3].flip();
			break;
		case 24:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[24];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[4].flip();
			break;
		case 25:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[25];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[0].flip();
			break;
		case 26:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[26];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[1].flip();
			break;
		case 27:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[27];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[2].flip();
			break;
		case 28:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[28];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[0].flip();
			break;
		case 29:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[29];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[1].flip();
			break;
		case 30:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[30];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[2].flip();
			break;
		case 31:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[31];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[3].flip();
			break;
		default:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[0];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[0].flip();
			break;
		}
		flag = false;
		for (j = 0; j < edc.size(); j++)
		{
			if ((edc[j].set == noise[i].set) && (edc[j].way == noise[i].way) && (edc[j].line == noise[i].line) && (edc[j].inst == noise[i].inst))
			{
				flag = true;
				break;
			}
		}
		if (flag == true)
		{
			InstructionToBitset(BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst], bitset_inst);
			if (SDC_Occured_Selective(bitset_inst, edc[j]))
				count++;
		}
		else
			count++;
	}
	return ((double)count / numberOfNoise);
}


double Noise_Injector(vector<MemorySet> BinaryMemory, const vector<MemoryProbability>& memoryProbability, vector<Noise>& noise, vector<EDC>& edc, int iterationNumber, int numberOfNoise)
{
	int i, j;
	double DCR;
	bitset<32> bitset_inst;
	int count = 0;

	for (i = iterationNumber * numberOfNoise; i < (iterationNumber + 1) * numberOfNoise; i++)
	{
		switch (noise[i].bit)
		{
		case 0:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[0];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[0].flip();
			break;
		case 1:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[1];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[1].flip();
			break;
		case 2:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[2];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[2].flip();
			break;
		case 3:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[3];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[3].flip();
			break;
		case 4:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[4];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[0].flip();
			break;
		case 5:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[5];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[1].flip();
			break;
		case 6:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[6];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[2].flip();
			break;
		case 7:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[7];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_7_4[3].flip();
			break;
		case 8:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[8];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[0].flip();
			break;
		case 9:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[9];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[1].flip();
			break;
		case 10:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[10];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[2].flip();
			break;
		case 11:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[11];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_11_8[3].flip();
			break;
		case 12:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[12];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[0].flip();
			break;
		case 13:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[13];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[1].flip();
			break;
		case 14:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[14];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[2].flip();
			break;
		case 15:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[15];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_15_12[3].flip();
			break;
		case 16:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[16];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[0].flip();
			break;
		case 17:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[17];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[1].flip();
			break;
		case 18:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[18];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[2].flip();
			break;
		case 19:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[19];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_19_16[3].flip();
			break;
		case 20:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[20];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[0].flip();
			break;
		case 21:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[21];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[1].flip();
			break;
		case 22:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[22];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[2].flip();
			break;
		case 23:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[23];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[3].flip();
			break;
		case 24:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[24];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_24_20[4].flip();
			break;
		case 25:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[25];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[0].flip();
			break;
		case 26:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[26];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[1].flip();
			break;
		case 27:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[27];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_27_25[2].flip();
			break;
		case 28:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[28];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[0].flip();
			break;
		case 29:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[29];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[1].flip();
			break;
		case 30:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[30];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[2].flip();
			break;
		case 31:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[31];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_31_28[3].flip();
			break;
		default:
			DCR = memoryProbability[noise[i].set].ways[noise[i].way].lines[noise[i].line].signalProbability[0];
			if (noise[i].noise >= Noise_Table(DCR, 1))
				BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst].opcode_3_0[0].flip();
			break;
		}
		for (j = 0; j < edc.size(); j++)
		{
			if ((edc[j].set == noise[i].set) && (edc[j].way == noise[i].way) && (edc[j].line == noise[i].line) && (edc[j].inst == noise[i].inst))
				break;
		}
		InstructionToBitset(BinaryMemory[noise[i].set].ways[noise[i].way].lines[noise[i].line].insts[noise[i].inst], bitset_inst);
		if (SDC_Occured(bitset_inst, edc[j]))
			count++;
	}
	return ((double)count / numberOfNoise);
}


void Random_Noise_Generator(const vector<MemorySet>& BinaryMemory, vector<Noise>& noise, int instruction_size, int numberOfIteration, int numberOfNoise)
{
	int i, j, k, z, l, m;
	int max_tick, rand_time;
	Noise rand_noise;
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	normal_distribution<double> nd(1.33, 0.9);
	uniform_int_distribution<int> set(0, BinaryMemory.size() - 1);
	uniform_int_distribution<int> way(0, BinaryMemory[0].ways.size() - 1);
	uniform_int_distribution<int> line(0, BinaryMemory[0].ways[0].lines.size() - 1);
	max_tick = Max_Tick(BinaryMemory);
	uniform_int_distribution<int> time(0, max_tick);
	uniform_int_distribution<int> bit(0, instruction_size);
	for (i = 0; i < numberOfIteration; i++)
	{
		for (j = 0; j < numberOfNoise; j++)
		{
			rand_noise.set = set(e);
			rand_noise.way = way(e);
			rand_noise.line = line(e);
			rand_time = time(e);
			rand_noise.bit = bit(e);
			rand_noise.noise = nd(e);
			for (k = 0; k < BinaryMemory[rand_noise.set].ways[rand_noise.way].lines[rand_noise.line].tick.size(); k++)
			{
				if (k < BinaryMemory[rand_noise.set].ways[rand_noise.way].lines[rand_noise.line].tick.size() - 1)
				{
					if ((BinaryMemory[rand_noise.set].ways[rand_noise.way].lines[rand_noise.line].tick[k] <= rand_time) && (BinaryMemory[rand_noise.set].ways[rand_noise.way].lines[rand_noise.line].tick[k + 1]))
						break;
				}
				else
				{
					k = BinaryMemory[rand_noise.set].ways[rand_noise.way].lines[rand_noise.line].tick.size() - 1;
					break;
				}
			}
			rand_noise.inst = k;
			noise.push_back(rand_noise);
			//Noise_Injector(BinaryMemory, memoryProbability, e, nd, rand_set, rand_way, rand_line, k, rand_bit, mode);
		}
	}
}


void Initial_Memory_SDC_Analysis(vector<MemorySet>& BinaryMemory, const vector<MemoryProbability>& memoryProbability, vector<Noise>& noise, int instruction_size, int numberOfIteration, int numberOfNoise)
{
	int i;
	double initial_SDC = 0, Aging_SDC = 0;
	fstream outfile;
	outfile.open("Noise_Injection.txt", ios::out | ios::app);
	//Random_Noise_Generator(BinaryMemory, noise, instruction_size, numberOfIteration, numberOfNoise);
	for (i = 0; i < numberOfIteration; i++)
		initial_SDC += Noise_Injector(BinaryMemory, memoryProbability, noise, i, numberOfNoise, 0);
	outfile << "Initial_SDC: " << initial_SDC << endl;
	for (i = 0; i < numberOfIteration; i++)
		Aging_SDC += Noise_Injector(BinaryMemory, memoryProbability, noise, i, numberOfNoise, 1);
	outfile << "Aging_SDC: " << Aging_SDC << endl;
}


void Noise_Calculation(vector<Noise>& noise, string FileName)
{
	int i;
	int count_init = 0, count0 = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0, count9 = 0, count10 = 0;
	fstream outfile;
	outfile.open(FileName, ios::out | ios::app);
	for (i = 0; i < noise.size(); i++)
	{
		if (fabs(noise[i].noise - 1.33) <= 0.0001)
			count_init++;
		else if (fabs(noise[i].noise - 0.6) <= 0.0001)
			count0++;
		else if (fabs(noise[i].noise - 0.7) <= 0.0001)
			count1++;
		else if (fabs(noise[i].noise - 0.8) <= 0.0001)
			count2++;
		else if (fabs(noise[i].noise - 0.9) <= 0.0001)
			count3++;
		else if (fabs(noise[i].noise - 1.1) <= 0.0001)
			count4++;
		else if (fabs(noise[i].noise - 1.3) <= 0.0001)
			count5++;
		else if (fabs(noise[i].noise - 1.15) <= 0.0001)
			count6++;
		else if (fabs(noise[i].noise - 0.95) <= 0.0001)
			count7++;
		else if (fabs(noise[i].noise - 0.85) <= 0.0001)
			count8++;
		else if (fabs(noise[i].noise - 0.75) <= 0.0001)
			count9++;
		else if (fabs(noise[i].noise - 0.65) <= 0.0001)
			count10++;

	}
	outfile << "count_init: " << count_init << "\t" << "%count" << ((double)count_init / noise.size()) << endl;
	outfile << "count0: " << count0 << "\t" << "%count" << ((double)count0 / noise.size()) << endl;
	outfile << "count1: " << count1 << "\t" << "%count" << ((double)count1 / noise.size()) << endl;
	outfile << "count2: " << count2 << "\t" << "%count" << ((double)count2 / noise.size()) << endl;
	outfile << "count3: " << count3 << "\t" << "%count" << ((double)count3 / noise.size()) << endl;
	outfile << "count4: " << count4 << "\t" << "%count" << ((double)count4 / noise.size()) << endl;
	outfile << "count5: " << count5 << "\t" << "%count" << ((double)count5 / noise.size()) << endl;
	outfile << "count6: " << count6 << "\t" << "%count" << ((double)count6 / noise.size()) << endl;
	outfile << "count7: " << count7 << "\t" << "%count" << ((double)count7 / noise.size()) << endl;
	outfile << "count8: " << count8 << "\t" << "%count" << ((double)count8 / noise.size()) << endl;
	outfile << "count9: " << count9 << "\t" << "%count" << ((double)count9 / noise.size()) << endl;
	outfile << "count10: " << count10 << "\t" << "%count" << ((double)count10 / noise.size()) << endl;
}


void Optimized_Memory_SDC_Analysis(vector<MemorySet>& BinaryMemory, const vector<MemoryProbability>& memoryProbability, vector<unsigned int>& vulnerable_instructions, vector<Noise>& noise, vector<EDC>& edc, int instruction_size, int numberOfIteration, int numberOfNoise)
{
	int i, j, k, z;
	bitset<32> bitset_inst;
	EDC e;
	double Optimized_Aging_SDC = 0, Optimized_Aging_Selective_EDC_SDC = 0, Optimized_Aging_EDC_SDC = 0;
	fstream outfile;
	outfile.open("Noise_Injection.txt", ios::out | ios::app);
	for (i = 0; i < numberOfIteration; i++)
		Optimized_Aging_SDC += Noise_Injector(BinaryMemory, memoryProbability, noise, i, numberOfNoise, 1);
	outfile << "Optimized_Aging_SDC: " << Optimized_Aging_SDC << endl;
	for (i = 0; i < numberOfIteration; i++)
		Optimized_Aging_Selective_EDC_SDC += Noise_Injector(BinaryMemory, memoryProbability, vulnerable_instructions, noise, edc, i, numberOfNoise);
	outfile << "Optimized_Aging_Selective_EDC_SDC: " << Optimized_Aging_Selective_EDC_SDC << endl;
	edc.clear();
	for (i = 0; i < BinaryMemory.size(); i++)
	{
		for (j = 0; j < BinaryMemory[i].ways.size(); j++)
		{
			for (k = 0; k < BinaryMemory[i].ways[j].lines.size(); k++)
			{
				for (z = 0; z < BinaryMemory[i].ways[j].lines[k].insts.size(); z++)
				{
					InstructionToBitset(BinaryMemory[i].ways[j].lines[k].insts[z], bitset_inst);
					e.set = i;
					e.way = j;
					e.line = k;
					e.inst = z;
					Error_Detection_Coding<bitset<32>>(bitset_inst, e);
					edc.push_back(e);
				}
			}
		}
	}
	for (i = 0; i < numberOfIteration; i++)
		Optimized_Aging_EDC_SDC += Noise_Injector(BinaryMemory, memoryProbability, noise, edc, i, numberOfNoise);
	outfile << "Optimized_Aging_EDC_SDC: " << Optimized_Aging_EDC_SDC;
	outfile.close();
}