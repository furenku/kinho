#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

//
//  GraphUtils.h
//  AbismoTwitterOF
//
//  Created by thiago on 1/23/13.
//
//

//#pragma once

#include "ofConstants.h"
#include "ofEvents.h"
#include<map>
#include<queue>

class Edge;

class GraphNode {
	public:
		GraphNode();
		~GraphNode();

		void set( const string _string );
		void setDistance(float f);
		const float getDistance() const;
		const string getNodeName() const;
		const bool isInQ() const;
		void setInQ(const bool q);
		void process() const;
		void addEdge(Edge* e);
		static ofEvent<GraphNode> addGraphNodeToGraph;
		bool operator < (const GraphNode &on) const;
		static bool sortComp(GraphNode *n0, GraphNode *n1);
	protected:
		float distance;
		map<string, Edge*> theEdges;
		string name;
		bool bInQ;
};

class Edge {
public:
	Edge();
	~Edge();
	void set( const string name_, const int cost_ );
	void setCost(const float td);
	void resetMinCost();
	string getNodeName() const;
	float getCost() const;
	static ofEvent<GraphNode> addGraphNodeToQ;
	static ofEvent<Edge> addEdgeToGraph;
	bool operator < (const Edge &oe) const;
	static bool sortComp(Edge *e0, Edge *e1);

	void addGraphNode(GraphNode* n);

protected:
	float minCost, cost, avgCost;
	map< string, GraphNode* > theGraphNodes;
	string name;
};

class Graph {
public:
	Graph();
	~Graph();
	void addGraphNodeToGraph(GraphNode& n);
	void addEdgeToGraph(Edge& e);
	void addGraphNodeToQ(GraphNode& n);
	void calculateDists(GraphNode& fromGraphNode);
	void orderGraph();
	// debug
	void printGraph() const;
	void calculateDists();
protected:
	map<string, GraphNode*> theGraphNodes;
	map<string, Edge*> theEdges;
	vector<GraphNode*> orderedGraphNodes;
	vector<Edge*> orderedEdges;
	queue<GraphNode*> theQ;
};


#endif
