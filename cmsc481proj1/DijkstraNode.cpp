//
//  DijkstraNode.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_DijkstraNode_cpp
#define cmsc481proj1_DijkstraNode_cpp

#include <stdio.h>
#include "DijkstraNode.h"

using namespace std;

DijkstraNode::DijkstraNode() : Node() {
    visited = false;
    shortestNeighbor = 0;
}

DijkstraNode::DijkstraNode(char * nodeName) : Node(nodeName) {
    visited = false;
    shortestNeighbor = 0;
}

pair<pair<Node *, unsigned int> *, unsigned int> DijkstraNode::getUnvisitedLinks() {
    pair<pair<Node *, unsigned int> *, unsigned int> allLinksPair = getLinks();
    pair<Node *, unsigned int> * allLinks = allLinksPair.first;
    int arrayLen = allLinksPair.second;
    pair<Node *, unsigned int> * unvisitedLinks = new pair<Node *, unsigned int>[arrayLen];
    int all = 0;
    int unvisited = 0;
    
    while(all < arrayLen) {
        pair<Node *, int> link = allLinks[all];
        Node * node = link.first;
        DijkstraNode * dnPtr = static_cast<DijkstraNode *>(node);
        
        if (dnPtr->visited == true) {
            unvisitedLinks[unvisited] = link;
            unvisited++;
        }
        
        all++;
    }
    
    return pair<pair<Node *, unsigned int> *, unsigned int>(unvisitedLinks, unvisited);
}

void DijkstraNode::setShortestNeighbor(pair<Node *, unsigned int> * shortestNeighbor) {
    this->shortestNeighbor = shortestNeighbor;
}

pair<Node *, unsigned int> DijkstraNode::getShortestNeighbor() {
    return *shortestNeighbor;
}

#endif