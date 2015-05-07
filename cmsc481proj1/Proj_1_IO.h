//
//  Proj_1_IO.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/30/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
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

void readFile(char * fileName, Graph * graph, char * sourceNodeName, char * destinationNodeName);
void writeFile(char * fileName, stack<QueueData *> * results, char * sourceNodeName, char * desinationNodeName);

#endif