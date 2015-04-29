//
//  DijkstraNode.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#include <stdio.h>
#include "DijkstraNode.h"

using namespace std;

DijkstraNode::DijkstraNode(char * nodeName) : Node(nodeName){
    visited = false;
    shortestNeighbor = 0;
}

pair<pair<Node, int> *, int> DijkstraNode::getUnvisitedLinks() {
    pair<pair<Node, int> *, int> allLinksPair = getLinks();
    pair<Node, int> * allLinks = allLinksPair.first;
    int arrayLen = allLinksPair.second;
    pair<Node, int> * unvisitedLinks = new pair<Node,int>[arrayLen];
    int all = 0;
    int unvisited = 0;
    
    while(all < arrayLen) {
        pair<Node, int> link = allLinks[all];
        Node node = link.first;
        DijkstraNode * dnPtr = static_cast<DijkstraNode *>(&node);
        
        if (dnPtr->visited == true) {
            unvisitedLinks[unvisited] = link;
            unvisited++;
        }
        
        all++;
    }
    
    return pair<pair<Node, int> *, int>(unvisitedLinks, unvisited);
}

void DijkstraNode::setShortestNeighbor(pair<Node, int> * shortestNeighbor) {
    this->shortestNeighbor = shortestNeighbor;
}

pair<Node, int> DijkstraNode::getShortestNeighbor() {
    return *shortestNeighbor;
}