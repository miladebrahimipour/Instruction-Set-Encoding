// Instruction_Encoding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Functions.h"
#include "Memory.h"
#include "Graph.h"
#include "Instruction.h"
#include "SNM.h"
#include "SDC_Optimization.h"
#include "Noise_Injection.h"
using namespace std;

/*
enum Opt{ opcodes, fields, registers };
typedef pair<graph::const_iterator, int> Node;
typedef pair<bitset<3>, bitset<3>> Opcode;
typedef pair<bitset<4>, bitset<4>> Register;
typedef pair<bitset<5>, bitset<5>> Field;
typedef pair<bitset<8>, bitset<8>> Opcode_8bit;
typedef pair<int, int> NumOfAccess;
*/


const int instruction_size = 32;
const int numberOfMonteCarloNoiseInjectionIterations = 5000;
const int numberOfNoiseInEachIteration = 1000;
int _tmain(int argc, _TCHAR* argv[])
{
	int assoc = 2;
	double Initial_SP, Initial_SNM, Lifetime_SP, Lifetime_SNM;
	string s = "ARM_Cache_Trace1.out";
	string s1 = "ARM_Cache_Trace_gcc.out";
	string s2 = "ARM_Cache_Trace_mcf.out";
	string s3 = "ARM_Cache_Trace_bzip2_8k_32.out";
	vector<MemoryContent> MemoryTransactions;
	vector<Memory> memory;
	//vector<vector<vector<string>>> StringBinaryMemory;
	//vector<vector<vector<vector<bitset<32>>>>> BinaryMemory;
	//vector<vector<vector<Instructions>>> InstructionMemory;
	vector<MemorySet> BinaryMemory;
	vector<Opcode> opcode_3bit;
	vector<Register> opcode_4bit, register_opcode;
	vector<Field> opcode_5bit;
	vector<Opcode_8bit> opcode_8bit;
	vector<MemoryProbability> BinaryMemoryProbability;
	vector<bitset<8>> SDC_opcode;
	vector<Noise> noise;
	vector<EDC> edc;
	vector<unsigned int> vulnerable_instructions;
	vector<vector<int>> vulnerable_bits;
	srand(time(NULL));

	Parser(MemoryTransactions, s, s1, s2);
	MemoryGenerator(memory, MemoryTransactions, assoc);
	MemorySort(memory);
	//BinaryMemoryCreator(memory, BinaryMemory, 2);
	BinaryMemoryCreator(memory, BinaryMemory);
	//InstructionExtraction(BinaryMemory, InstructionMemory);
	Opcode_3bit_Optimization(BinaryMemory, opcode_3bit);
	Opcode_4bit_Optimization(BinaryMemory, opcode_4bit, 31);
	Opcode_5bit_Optimization(BinaryMemory, opcode_5bit);
	//Opcode_8bit_Graph_Optimization(BinaryMemory, opcode_8bit);
	Register_Optimization(BinaryMemory, register_opcode);
	//*******************************************************************************************************************************
	/*
	MemoryTransactions.clear();
	memory.clear();
	BinaryMemory.clear();
	Parser(MemoryTransactions, s3);
	MemoryGenerator(memory, MemoryTransactions, assoc);
	MemorySort(memory);
	BinaryMemoryCreator(memory, BinaryMemory);
	//*******************************************************************************************************************************
	*/
	Initial_SP = SignalProbabilityCalculation(BinaryMemory, BinaryMemoryProbability);
	Initial_SNM = SNM_Table(Initial_SP);
	Random_Noise_Generator(BinaryMemory, noise, instruction_size, numberOfMonteCarloNoiseInjectionIterations, numberOfNoiseInEachIteration);
	Noise_Calculation(noise, "Noise.txt");
	Initial_Memory_SDC_Analysis(BinaryMemory, BinaryMemoryProbability, noise, instruction_size, numberOfMonteCarloNoiseInjectionIterations, numberOfNoiseInEachIteration);
	//*******************************************************************************************************************************
	New_Instruction_Memory(BinaryMemory, opcode_3bit, opcode_4bit, register_opcode, opcode_5bit);
	//New_Instruction_Memory(BinaryMemory, opcode_4bit, register_opcode, opcode_8bit);
	//SDC_Graph_Extraction(BinaryMemory, SDC_opcode, 10);
	Lifetime_SP = SignalProbabilityCalculation(BinaryMemory, BinaryMemoryProbability);
	Lifetime_SNM = SNM_Table(Lifetime_SP);
	//*******************************************************************************************************************************
	MemoryTransactions.clear();
	memory.clear();
	BinaryMemory.clear();
	edc = SDC_Optimization(MemoryTransactions, memory, BinaryMemory, vulnerable_instructions, vulnerable_bits, assoc, s, s1, s2, 100, 50);
	Optimized_Memory_SDC_Analysis(BinaryMemory, BinaryMemoryProbability, vulnerable_instructions, noise, edc, instruction_size, numberOfMonteCarloNoiseInjectionIterations, numberOfNoiseInEachIteration);
	return 0;
}