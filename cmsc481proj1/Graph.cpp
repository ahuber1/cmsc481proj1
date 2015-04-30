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
#include <iostream>

bool compare(char * left, char * right) {
    char l = *left;
    char r = *right;
    
    return l < r;
}

Graph::Graph() {
    nodes = map<char *, Node,bool(*)(char *,char *)>(compare);
}

void Graph::addNode(char * nodeName) {
    addNode(Node(nodeName));
}

Node * Graph::getNode(char * nodeName) {
    
    if(nodes.find(nodeName) == nodes.end())
        return 0;
    else
        return &nodes[nodeName];
}

void Graph::addNode(Node nodeToAdd) {
    if (nodes.find(nodeToAdd.getNodeName()) == nodes.end())
        nodes.insert(pair<char *, Node>(nodeToAdd.getNodeName(), nodeToAdd));
    else
        throw 2; // ERROR 2 : node already exists in graph
}

#endif