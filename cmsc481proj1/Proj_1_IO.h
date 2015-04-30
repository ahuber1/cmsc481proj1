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
#include "DijkstraGraph.h"

void readFile(char * fileName, DijkstraGraph * graph, char * sourceNodeName, char * destinationNodeName);
void processBuffer(char * buffer, const int BUFFER_SIZE, DijkstraGraph * graph, char * sourceNodeName, char * destinationNodeName);
void processTokens(string * tokens, DijkstraGraph * graph, char * sourceNodeName, char * destinationNodeName);

#endif /* defined(__cmsc481proj1__Proj_1_IO__) */