//
//  Graph.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/29/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#include <stdio.h>
#include "Graph.h"

Graph::Graph() {
    nodes = map<char *, Node>();
}

void Graph::addNode(char *nodeName) {
    addNode(Node(nodeName));
}

Node Graph::getNode(char * nodeName) {
    
    if(nodes.find(nodeName) == nodes.end())
        return Node(0);
    else
        return nodes[nodeName];
}

void Graph::addNode(Node nodeToAdd) {
    if (nodes.find(nodeToAdd.getNodeName()) == nodes.end())
        throw 2; // ERROR 2 : node already exists in graph
    else
        nodes.insert(pair<char *, Node>(nodeToAdd.getNodeName(), nodeToAdd));
}