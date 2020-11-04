#include "stdafx.h"
#include "Graph.h"
using namespace std;


Graph::Graph()
{
}


Graph::~Graph()
{
}


void Graph::addvertex(const string &name)
{
	graph::iterator itr = OpcodeGraph.find(name);
	if (itr == OpcodeGraph.end())
	{
		Vertex *v;
		v = new Vertex(name);
		v->opcode = name;
		OpcodeGraph[name] = v;
		return;
	}
	cout << "\nVertex already exists!";
}


void Graph::addedge(const string& from, const string& to)//, double cost)
{
	int i;
	bool flag = false;
	Vertex *f = (OpcodeGraph.find(from)->second);
	Vertex *t = (OpcodeGraph.find(to)->second);
	for (i = 0; i < f->adj.size(); i++)
	{
		if (f->adj[i].second == t)
		{
			f->adj[i].first = (get<0>(f->adj[i])++);
			flag = true;
		}
	}
	if (flag == false)
	{
		pair<int, Vertex *> edge = make_pair(1, t);
		f->adj.push_back(edge);
	}
}


bool Graph::IsVertex(const string& name)
{
	graph::iterator itr = OpcodeGraph.find(name);
	if (itr == OpcodeGraph.end())
		return true;
	return false;
}


graph::const_iterator Graph::FindVertex(const string& name)
{
	graph::iterator itr = OpcodeGraph.find(name);
	return itr;
}


graph::const_iterator Graph::GraphBegin()
{
	return OpcodeGraph.cbegin();
}


graph::const_iterator Graph::GraphEnd()
{
	return OpcodeGraph.cend();
}


string Graph::vertexName(graph::const_iterator itr)
{
	return itr->first;
}


int Graph::getGraphSize()
{
	return OpcodeGraph.size();
}
