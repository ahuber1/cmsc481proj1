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
    Graph * graphPtr = new Graph(); // make a pointer to an empty graph
    char sourceNodeName[100]; // make a buffer to store the source node name
    char destinationNodeName[100]; // make a buffer to store the destination node name
    
    readFile(inputFileName, graphPtr, sourceNodeName, destinationNodeName); // read the text file
    ShortestPathData * results = shortestPath(graphPtr, sourceNodeName, destinationNodeName); // run Dijkstra's
    writeFile(outputFileName, graphPtr, results, sourceNodeName, destinationNodeName); // write results to file
    
    return 0;
}