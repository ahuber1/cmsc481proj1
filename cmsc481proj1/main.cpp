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
    
    char inputFileName[] = "/Users/andrew_huber/Dropbox/spring_2015/cmsc481/project1/code/cmsc481proj1/cmsc481proj1/input.txt";
    char outputFileName[] = "/Users/andrew_huber/Dropbox/spring_2015/cmsc481/project1/code/cmsc481proj1/cmsc481proj1/output.txt";
    Graph * graphPtr = new Graph();
    char sourceNodeName[100];
    char destinationNodeName[100];
    
    readFile(inputFileName, graphPtr, sourceNodeName, destinationNodeName);
    ShortestPathData * results = shortestPath(graphPtr, sourceNodeName, destinationNodeName);
    writeFile(outputFileName, results, sourceNodeName, destinationNodeName);
    
    return 0;
}


