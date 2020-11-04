#include <iostream>
#include <vector>
#include <map>
#include <bitset>
using namespace std;


struct Vertex
{
	typedef pair<int, Vertex*> ve;
	vector<ve> adj;
	string opcode;
	Vertex(string s) : opcode(s) {}
};

typedef map<string, Vertex *> graph;
#pragma once
class Graph
{
public:
	Graph();
	~Graph();
	void addvertex(const string&);
	void addedge(const string& from, const string& to);// , double cost);
	bool IsVertex(const string& name);
	graph::const_iterator FindVertex(const string& name);
	graph::const_iterator GraphBegin();
	graph::const_iterator GraphEnd();
	string vertexName(graph::const_iterator);
	int getGraphSize();

private:
	graph OpcodeGraph;
};

