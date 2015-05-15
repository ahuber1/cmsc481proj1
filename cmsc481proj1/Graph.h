//
//  Graph.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_Graph_h
#define cmsc481proj1_Graph_h

#include "Node.h"

using namespace std;

class Graph {
    
public:
    // Makes a new graph
    Graph();
    
    // Adds a node to the graph
    void addNode(char * nodeName); // the name of the node to add
    
    // Gets a node that matches a certain name
    //
    // RETURNS: the node corresponding to "codeName" or 0 if it does not exist in the graph
    Node * getNode(char * nodeName); // the name of the node to retrieve
    
    // Gets all the nodes in this graph
    //
    // RETURNS: a pair pointer (p1) containing an array of pair pointers (p2)
    // as the key and an unsigned int containing the length of the array p2. Each pointer
    // in p2 contains a char pointer that specifies the name of the node and a NOde pointer
    // containing the node in the graph with that name
    pair<pair<char *, Node *> *, unsigned int> * getAllNodes();
    
protected:
    
    // Adds a node to the graph
    void addNode(Node * nodeToAdd); // The node to add to the graph
    
private:
    
    // A map that contains char pointers as the key and Node objects as
    // the value. The keys contain the node names and the Node pointers
    // are the actual nodes that correspond to the node names
    map<char *, Node *, bool(*)(char*,char*)> nodes;
};

#endif
