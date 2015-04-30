//
//  main.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#include <iostream>
#include "DijkstraGraph.h"
#include "Proj_1_IO.h"

int main(int argc, const char * argv[]) {
    
    DijkstraGraph graph = DijkstraGraph();
    
    char fileName[] = "input.txt";
    DijkstraGraph * graphPtr = &graph;
    char sourceNodeName[100];
    char destinationNodeName[100];
    
    readFile(fileName, graphPtr, sourceNodeName, destinationNodeName);
    
    return 0;
}
