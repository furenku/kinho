//
//  GraphUtils.cpp
//  AbismoTwitterOF
//
//  Created by thiago on 1/23/13.
//
//

#include "GraphUtils.h"
#include "ofLog.h"

ofEvent<GraphNode> GraphNode::addGraphNodeToGraph = ofEvent<GraphNode>();

GraphNode::GraphNode(){

}

void GraphNode::set( const string name_) {
	name = name_;
	distance = 1e9;
	ofNotifyEvent(GraphNode::addGraphNodeToGraph, *this);
}

GraphNode::~GraphNode(){
}

bool GraphNode::operator < (const GraphNode &on) const{
	return distance < on.distance;
}

bool GraphNode::sortComp(GraphNode *n0, GraphNode *n1){
	return *n0 < *n1;
}

void GraphNode::setDistance(float f){
	distance = f;
}
const float GraphNode::getDistance() const{
	return distance;
}
const string GraphNode::getNodeName() const{
	return name;
}
const bool GraphNode::isInQ() const{
	return bInQ;
}
void GraphNode::setInQ(const bool q){
	bInQ = q;
}

void GraphNode::process() const{
	// send my distance to all edges
	for (map<string,Edge*>::const_iterator it=theEdges.begin(); it!=theEdges.end(); ++it){
		(it->second)->setCost(distance);
	}
}

// add edge to map. use name as key.
void GraphNode::addEdge(Edge* e){
	if(theEdges.find(e->getNodeName()) == theEdges.end()){
		theEdges[e->getNodeName()] = e;
		// link back to node...
		e->addGraphNode(this);
	}
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////
ofEvent<GraphNode> Edge::addGraphNodeToQ = ofEvent<GraphNode>();
ofEvent<Edge> Edge::addEdgeToGraph = ofEvent<Edge>();

Edge::Edge(){}
Edge::~Edge(){}


void Edge::set(const string name_, const int cost_){
	name = name_;
	cost = cost_;
	minCost = 1e9;
	ofNotifyEvent(Edge::addEdgeToGraph, *this);
}

bool Edge::operator < (const Edge &oe) const{
	return minCost < oe.minCost;
}

bool Edge::sortComp(Edge *e0, Edge *e1){
	return *e0 < *e1;
}

void Edge::setCost(const float td){
	// if there's a shorter way to get here, update minCost
	if(td+avgCost < minCost){
		minCost = td+avgCost;

		// send new cost to all nodes
		for (map<string,GraphNode*>::const_iterator it=theGraphNodes.begin(); it!=theGraphNodes.end(); ++it){
			if(minCost+avgCost < (it->second)->getDistance()){
				(it->second)->setDistance(minCost+avgCost);
				// Add node to graph Q
				(it->second)->setInQ(true);
				ofNotifyEvent(Edge::addGraphNodeToQ, *(it->second));
			}
		}
	}
}

void Edge::resetMinCost(){
	minCost = 1e9;
}

string Edge::getNodeName() const{
	return name;
}
float Edge::getCost() const{
	return minCost;
}

void Edge::addGraphNode(GraphNode* n){
	if(theGraphNodes.find(n->getNodeName()) == theGraphNodes.end()){
		theGraphNodes[n->getNodeName()] = n;
		avgCost = cost/theGraphNodes.size();
	}
}

//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

// adds every created node and edge to graph using listeners. ????
Graph::Graph(){
	ofAddListener(Edge::addGraphNodeToQ, this, &Graph::addGraphNodeToQ);
	ofAddListener(GraphNode::addGraphNodeToGraph, this, &Graph::addGraphNodeToGraph);
	ofAddListener(Edge::addEdgeToGraph, this, &Graph::addEdgeToGraph);
}

Graph::~Graph(){
	for (map<string,GraphNode*>::const_iterator it=theGraphNodes.begin(); it!=theGraphNodes.end(); ++it){
		delete it->second;
	}
	for (map<string,Edge*>::const_iterator it=theEdges.begin(); it!=theEdges.end(); ++it){
		delete it->second;
	}
}

void Graph::addGraphNodeToGraph(GraphNode& n){
	theGraphNodes[n.getNodeName()] = &n;
	orderedGraphNodes.push_back(&n);
}
void Graph::addEdgeToGraph(Edge& e){
	theEdges[e.getNodeName()] = &e;
	orderedEdges.push_back(&e);
}

void Graph::addGraphNodeToQ(GraphNode& n){
	// add to Q
	theQ.push(&n);
}

void Graph::calculateDists(GraphNode& fromGraphNode){
	// clear costs from nodes
	for (map<string,GraphNode*>::const_iterator it=theGraphNodes.begin(); it!=theGraphNodes.end(); ++it){
		(it->second)->setDistance(1e9);
	}
	// clear minDist from edges
	for (map<string,Edge*>::const_iterator it=theEdges.begin(); it!=theEdges.end(); ++it){
		(it->second)->resetMinCost();
	}

	// push root calculate dists.
	fromGraphNode.setDistance(0);
	theQ.push(&fromGraphNode);

	while(!theQ.empty()){
		GraphNode n = *(theQ.front());
		n.setInQ(false);
		theQ.pop();
		n.process();
	}
}

void Graph::orderGraph(){
	// check sizes
	if(orderedGraphNodes.size() != theGraphNodes.size()){
		ofLogWarning("orderedGraphNodes and theGraphNodes are inconsistent");
		orderedGraphNodes.clear();
		for (map<string,GraphNode*>::const_iterator it=theGraphNodes.begin(); it!=theGraphNodes.end(); ++it){
			orderedGraphNodes.push_back(it->second);
		}
	}
	if(orderedEdges.size() != theEdges.size()){
		ofLogWarning("orderedEdges and theEdges are inconsistent");
		orderedEdges.clear();
		for (map<string,Edge*>::const_iterator it=theEdges.begin(); it!=theEdges.end(); ++it){
			orderedEdges.push_back(it->second);
		}
	}
	// sort
	sort(orderedGraphNodes.begin(), orderedGraphNodes.end(), GraphNode::sortComp);
	sort(orderedEdges.begin(), orderedEdges.end(), Edge::sortComp);
}

// for debug
void Graph::calculateDists(){

    /*
	int mi = (int)ofRandom(theGraphNodes.size());
	int i = 0;
	GraphNode *n0 = NULL;
	for (map<string,GraphNode*>::const_iterator it=theGraphNodes.begin(); it!=theGraphNodes.end()&&i<mi; ++it,++i){
		n0 = it->second;
	}
	if(n0){
//		long long unsigned int t0 = AbsoluteToDuration(UpTime());
		calculateDists(*n0);
//		long long unsigned int et = AbsoluteToDuration(UpTime())-t0;
		cout << "calculated from: " << n0->getNodeName()+ " in: " << et << " millis"<<endl;
	}

	*/
}

// for debug
void Graph::printGraph() const{
	ofLogWarning("GraphNodes:")<< "";
	for (map<string,GraphNode*>::const_iterator it=theGraphNodes.begin(); it!=theGraphNodes.end(); ++it){
		ofLogWarning() << it->first << ": " << (it->second)->getDistance();
	}
	ofLogWarning("Edges:") << "";
	for (map<string,Edge*>::const_iterator it=theEdges.begin(); it!=theEdges.end(); ++it){
		ofLogWarning() << it->first << ": " << (it->second)->getCost();
	}
}
