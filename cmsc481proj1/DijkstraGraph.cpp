//
//  DijkstraGraph.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/29/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_DijkstraGraph_cpp
#define cmsc481proj1_DijkstraGraph_cpp

#include <stdio.h>
#include "DijkstraGraph.h"
#include "DijkstraNode.h"

DijkstraGraph::DijkstraGraph() : Graph() {
    // No need to do anything additional
}

void DijkstraGraph::addNode(char *nodeName) {
    Graph::addNode(DijkstraNode(nodeName));
}

#endif