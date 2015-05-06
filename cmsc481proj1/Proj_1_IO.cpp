//
//  Proj_1_IO.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/30/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef __cmsc481proj1__Proj_1_IO
#define __cmsc481proj1__Proj_1_IO

#include "Proj_1_IO.h"

void processTokens(string * tokens, Graph * graph, char * sourceNodeName, char * destinationNodeName) {
    
    for(int a = 0; a < 3; a++) {
        for(int b = 0; b < tokens[a].length(); b++) {
            tokens[a][b] = (char) tolower(tokens[a][b]);
        }
    }
    
    if (tokens[0].compare("source") == 0)
        strcpy(sourceNodeName, tokens[1].c_str());
    else if(tokens[0].compare("destination") == 0)
        strcpy(destinationNodeName, tokens[1].c_str());
    else {
        const char * POINT_A_NAME = tokens[0].c_str();
        const char * POINT_B_NAME = tokens[1].c_str();
        const char * WEIGHT_STR   = tokens[2].c_str();
        
        char * pointAname = new char[100];
        char * pointBname = new char[100];
        
        strcpy(pointAname, POINT_A_NAME);
        strcpy(pointBname, POINT_B_NAME);
        
        int  weight = atoi(WEIGHT_STR);
        
        Node * pointA = graph->getNode(pointAname);
        Node * pointB = graph->getNode(pointBname);
        
        if(pointA == 0) {
            graph->addNode(pointAname);
            pointA = graph->getNode(pointAname);
        }
        if(pointB == 0) {
            graph->addNode(pointBname);
            pointB = graph->getNode(pointBname);
        }
        
        if (pointA->isLinked(pointB) || pointB->isLinked(pointA)) {
            throw 3; // ERROR 3: nodes are already linked
        }
        else {
            pointA->addLink(pointB, weight);
            pointB->addLink(pointA, weight);
        }
    }
}

void processBuffer(char * buffer, const int BUFFER_SIZE, Graph * graph, char * sourceNodeName, char * destinationNodeName) {
    
    string tokens[3];
    
    tokens[0] = "";
    tokens[1] = "";
    tokens[2] = "";
    
    int tokenIndex = 0;
    
    for (int bufferInd = 0; bufferInd < BUFFER_SIZE; bufferInd++) {
        if (buffer[bufferInd] == 0) {
            tokenIndex = 0;
            processTokens(tokens, graph, sourceNodeName, destinationNodeName);
            bufferInd = BUFFER_SIZE;
        }
        else if (buffer[bufferInd] == '$')
            tokenIndex++;
        else
            tokens[tokenIndex] += buffer[bufferInd];
    }
}

void readFile(char * fileName, Graph * graph, char * sourceNodeName, char * destinationNodeName) {
    
    ifstream file;
    file.open(fileName);
    const int BUFFER_SIZE = 100;
    
    if(file.is_open()) {
        while (!file.eof()) {
            char buffer[BUFFER_SIZE];
            file >> buffer;
            processBuffer(buffer, BUFFER_SIZE, graph, sourceNodeName, destinationNodeName);
        }
    }
    else
        throw 4; // ERROR 4: unable to open file
}

#endif