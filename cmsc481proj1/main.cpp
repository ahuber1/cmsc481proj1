//
//  main.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include "Proj_1_IO.h"
#include "Dijkstra.h"

int main(int argc, const char * argv[]) {
    
    char fileName[] = "/Users/andrew_huber/Dropbox/spring_2015/cmsc481/project1/code/cmsc481proj1/cmsc481proj1/input.txt";
    Graph * graphPtr = new Graph();
    char sourceNodeName[100];
    char destinationNodeName[100];
    
    readFile(fileName, graphPtr, sourceNodeName, destinationNodeName);
    stack<QueueData *> * results = shortestPath(graphPtr, sourceNodeName, destinationNodeName);
    
    
    
    return 0;
}


