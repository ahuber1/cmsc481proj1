//
//  DijkstraGraph.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//
#ifndef cmsc481proj1_DijkstraGraph_h
#define cmsc481proj1_DijkstraGraph_h

#include "Graph.h"

class DijkstraGraph : public Graph {
    
public:
    DijkstraGraph();
    void addNode(char *nodeName);
};

#endif
