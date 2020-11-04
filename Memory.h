#include <vector>
#include <string>
using namespace std;


struct Block
{
	vector<vector<int>> BlockData;
	int Tick;
	vector<double> SignalProbability;
	int wayID;
};
//typedef vector<vector<int>> Block;


#pragma once
class Memory
{
public:
	Memory();
	~Memory();

	/*struct Set
	{
		vector<Way> set;
	};*/
	//typedef vector<Block> way;
	//typedef vector<way> Set;

	void setSetID(int i);
	int getSetID();

	void setBlock(Block block, int wayID);
	Block getBlock(int wayID, int BlockID);

	void setAssociativity(int assoc);
	int getAssociativity();

	void setBlockTick(int Tick, int wayID, int BlockID);
	int getBlockTick(int wayID, int BlockID);

	void setSet(int assoc);

	int getWayBlockNumbers(int wayID);

	/*
	void setBlockWay(int i);
	int getBlockWay();

	void setBlockTick(int i);
	int getBlockTick();

	void setBlockData(vector<vector<int>> BlockData);
	vector<vector<int>>& getBlockData();
	

	void getWay(int i);


	void Set(int assoc, int blockdata);

	void setSet(int i, Block s);
	Block getSet(int i);
	
	void Set(int assoc, int blockdata);

	static void setAssociativity(int assoc);

	void setWayID(int id, int block_index);
	int getWayID(int block_index);


	void setSet(int i, Block s);
	Block getSet(int i);
	*/

private:
	struct Way
	{
		vector<Block> way;
	};
	int associativity;
	int setID;
	vector<Way> set;
/*
public:
	Memory();
	~Memory();

	void Set(int assoc, int blockdata);

	static void setAssociativity(int assoc);

	void setWayID(int id, int block_index);
	int getWayID(int block_index);

	void setSetID(int i);
	int getSetID();

	void setSet(int i, Block s);
	Block getSet(int i);
private:
	static int associativity;
	int setID;
	vector<Block> set;
	*/
};

