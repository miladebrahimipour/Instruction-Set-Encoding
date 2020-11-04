#include "stdafx.h"
#include "Memory.h"


Memory::Memory()
{
}


Memory::~Memory()
{
}


void Memory::setSetID(int i)
{
	setID = i;
}


int Memory::getSetID()
{
	return setID;
}


void Memory::setBlock(Block block, int wayID)
{
	set[wayID].way.push_back(block);
}


Block Memory::getBlock(int wayID, int BlockID)
{
	return set[wayID].way[BlockID];
}


void Memory::setAssociativity(int assoc)
{
	associativity = assoc;
	set.resize(associativity);
}


int Memory::getAssociativity()
{
	return associativity;
}


void Memory::setBlockTick(int Tick, int wayID, int BlockID)
{
	set[wayID].way[BlockID].Tick = Tick;
}


int Memory::getBlockTick(int wayID, int BlockID)
{
	return set[wayID].way[BlockID].Tick;
}


void Memory::setSet(int assoc)
{
	associativity = assoc;
	set.resize(associativity);
}


int Memory::getWayBlockNumbers(int wayID)
{
	return set[wayID].way.size();
}


/*
void Memory::Set(int assoc, int blockdata)
{
	if (assoc == 0)
		throw "please set Memory Associativity";
	else if (blockdata == 0)
		throw "please set Memory Block Size";
	associativity = assoc;
	set.resize(assoc);
	for (int i = 0; i < set.size(); i++)
		set[i].BlockData.resize(blockdata);
}


void Memory::setWayID(int id, int block_index)
{
	if (id > associativity)
		throw "wrong way ID";
	set[block_index].wayID = id;
}


int Memory::getWayID(int block_index)
{
	return set[block_index].wayID;
}


void Memory::setSet(int blockId, Block s)
{
	set[blockId].Tick = s.Tick;
	set[blockId].wayID = s.wayID;
	set[blockId].BlockData.push_back(s.BlockData[0]);
}


Block Memory::getSet(int i)
{
	return set[i];
}
*/