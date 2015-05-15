//
//  Graph.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/29/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_Graph_cpp
#define cmsc481proj1_Graph_cpp

#include "Graph.h"

// Comparator used by the map
bool compare(char * left, char * right) {
    char l = *left;
    char r = *right;
    
    return l < r;
}

// Makes a new Graph
Graph::Graph() {
    nodes = map<char *, Node *,bool(*)(char *,char *)>(compare);
}

// Adds a node to the graph
void Graph::addNode(char * nodeName) // the name of the node to add
{
    addNode(new Node(nodeName));
}

// Gets a node that matches a certain name
//
// RETURNS: the node corresponding to "codeName" or 0 if it does not exist in the graph

Node * Graph::getNode(char * nodeName) // the name of the node to retrieve
{
    
    if(nodes.find(nodeName) == nodes.end())
        return 0;
    else
        return nodes.find(nodeName)->second;
}

// Gets all the nodes in this graph
//
// RETURNS: a pair pointer (p1) containing an array of pair pointers (p2)
// as the key and an unsigned int containing the length of the array p2. Each pointer
// in p2 contains a char pointer that specifies the name of the node and a Node pointer
// containing the node in the graph with that name

pair<pair<char *, Node *> *, unsigned int> * Graph::getAllNodes() {
    pair<char *, Node *> * nodeList = new pair<char *, Node *>[nodes.size()];
    unsigned int i = 0;
    
    for (map<char *, Node *>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        nodeList[i] = pair<char *, Node *>(it->first, it->second);
        i++;
    }
    
    return new pair<pair<char *, Node *> *, unsigned int>(nodeList, i);
}

// Adds a node to the graph

void Graph::addNode(Node * nodeToAdd) // The node to add to the graph
{
    if (nodes.find(nodeToAdd->getNodeName()) == nodes.end())
        nodes.insert(pair<char *, Node *>(nodeToAdd->getNodeName(), nodeToAdd));
    else
        throw 2; // ERROR 2 : node already exists in graph
}

#endif