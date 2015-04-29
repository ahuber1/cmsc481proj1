//
//  DijkstraGraph.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/29/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#include <stdio.h>
#include "DijkstraGraph.h"
#include "DijkstraNode.h"

DijkstraGraph::DijkstraGraph() : Graph() {
    // No need to do anything additional
}

void Graph::addNode(char *nodeName) {
    addNode(DijkstraNode(nodeName));
}