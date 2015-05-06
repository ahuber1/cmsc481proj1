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

bool compare(char * left, char * right) {
    char l = *left;
    char r = *right;
    
    return l < r;
}

Graph::Graph() {
    nodes = map<char *, Node *,bool(*)(char *,char *)>(compare);
}

void Graph::addNode(char * nodeName) {
    addNode(new Node(nodeName));
}

Node * Graph::getNode(char * nodeName) {
    
    if(nodes.find(nodeName) == nodes.end())
        return 0;
    else
        return nodes.find(nodeName)->second;
}

pair<pair<char *, Node *> *, unsigned int> * Graph::getAllNodes() {
    pair<char *, Node *> * nodeList = new pair<char *, Node *>[nodes.size()];
    unsigned int i = 0;
    
    for (map<char *, Node *>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        nodeList[i] = pair<char *, Node *>(it->first, it->second);
        i++;
    }
    
    return new pair<pair<char *, Node *> *, unsigned int>(nodeList, i);
}

void Graph::addNode(Node * nodeToAdd) {
    if (nodes.find(nodeToAdd->getNodeName()) == nodes.end())
        nodes.insert(pair<char *, Node *>(nodeToAdd->getNodeName(), nodeToAdd));
    else
        throw 2; // ERROR 2 : node already exists in graph
}

#endif