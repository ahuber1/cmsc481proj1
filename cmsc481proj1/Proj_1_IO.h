//
//  Proj_1_IO.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/30/2015.
//
//  Performs the I/O operations for this project
//

#ifndef __cmsc481proj1__Proj_1_IO__
#define __cmsc481proj1__Proj_1_IO__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include "Graph.h"
#include "Dijkstra.h"

// Writes the results of Dijkstra to an output file

void writeFile(char * fileName, // the name of the output file
               
               Graph * graph, // the graph to which Dijkstra's was applied
               
               ShortestPathData * data, // the information returned by Dijkstra's
               
               char * sourceNodeName, // the name of the source node
               
               char * desinationNodeName); // the name of the destination node

// Reads the input file and constructs a graph

void readFile(char * fileName, // the name of the input file
              
              Graph * graph, // the graph to which we will add nodes
              
              char * sourceNodeName, // a char pointer that will be updated to contain the name of the source node
              
              char * destinationNodeName) // a char pointer that will be updated to contain the name of the destination node
#endif