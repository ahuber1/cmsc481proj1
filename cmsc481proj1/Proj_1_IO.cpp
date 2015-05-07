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

pair<unsigned int *, unsigned int> * findAllNodesAfterNode(QueueData ** dijkstraData, unsigned int lengthOfDijkstraData, char * nodeName) {
    unsigned int indicies[lengthOfDijkstraData];
    unsigned int index;
    
    for (unsigned int i = 0; i < lengthOfDijkstraData; i++) {
        if (dijkstraData[i]->prev != 0 && strcmp(dijkstraData[i]->prev->getNodeName(), nodeName) == 0) {
            indicies[index] = i;
            index++;
        }
    }
    
    return new pair<unsigned int *, unsigned int>(indicies, index);
}

void updateRouteTable(QueueData ** dijkstraData, QueueData ** routeTable, unsigned int lengthOfDijstraData, Node * node, Node * currNode) {
    pair<unsigned int *, unsigned int> * nextNodePair = findAllNodesAfterNode(dijkstraData, lengthOfDijstraData, currNode->getNodeName());
    unsigned int * indiciesOfNextNodes = nextNodePair->first;
    unsigned int numberOfNextNodes = nextNodePair->second;
    
    for (unsigned int i = 0; i < numberOfNextNodes; i++) {
        if (node == currNode) {
            routeTable[indiciesOfNextNodes[i]]->prev = routeTable[indiciesOfNextNodes[i]]->node;
        }
        else {
            routeTable[indiciesOfNextNodes[i]]->prev = currNode;
        }
        
        updateRouteTable(dijkstraData, routeTable, lengthOfDijstraData, node, routeTable[indiciesOfNextNodes[i]]->node);
    }
}

QueueData ** makeRouteTable(Graph * graph, Node * node, QueueData ** dijkstraData, unsigned int lengthOfRouteTable) {
    pair<pair<char *, Node *> *, unsigned int> * allNodesPair = graph->getAllNodes();
    pair<char *, Node *> * allNodes = allNodesPair->first;
    unsigned int numberOfNodesInGraph = allNodesPair->second;
    QueueData ** routeTable = new QueueData * [numberOfNodesInGraph];
    unsigned int indexOfNode = 0;
    
    for(int i = 0; i < numberOfNodesInGraph; i++) {
        routeTable[i] = new QueueData(allNodes[i].second);
        
        if(strcmp(routeTable[i]->node->getNodeName(), node->getNodeName()) == 0) {
            indexOfNode = i;
        }
    }

    updateRouteTable(dijkstraData, routeTable, lengthOfRouteTable, routeTable[indexOfNode]->node, routeTable[indexOfNode]->node);
    return routeTable;
}

void printRouteTable(Graph * graph, Node * node, QueueData ** dijkstraData, unsigned int lengthOfRouteTable, ostream * outputFile) {
    *outputFile << "Route Table of Node " << node->getNodeName() << " (Format [To, Next Hop, Distance])" << endl;
    QueueData ** routeTable = makeRouteTable(graph, node, dijkstraData, lengthOfRouteTable);
    
    for (unsigned int i = 0; i < lengthOfRouteTable; i++) {
        QueueData * entry = routeTable[i];
        unsigned int distance = dijkstraData[i]->lowestCost;
        
        if (entry->prev != 0) {
            *outputFile << "[" << entry->node->getNodeName() << ", " << entry->prev->getNodeName() << ", " << distance << "]" << endl;
        }
    }
    *outputFile << endl;
}

void writeFile(char * fileName, Graph * graph, ShortestPathData * data, char * sourceNodeName, char * desinationNodeName) {
    ofstream outputFile;
    outputFile.open(fileName);

    if(outputFile.is_open()) {
        const char * separator = "------------------------------------------------";
        
        outputFile << separator << " (beginning of summary)" << endl;
        outputFile << "The shortest path from " << sourceNodeName << " to " << desinationNodeName << " is:" << endl;
        outputFile << "\t";
        
        unsigned int totalDistance = data->shortestPathStack->top()->lowestCost;
        
        while (data->shortestPathStack->size() > 0) {
            QueueData * qd = data->shortestPathStack->top();
            
            data->shortestPathStack->pop();
            
            outputFile << qd->node->getNodeName();
            
            if (data->shortestPathStack->size() > 0) {
                outputFile << " -> ";
            }
            else {
                outputFile << endl;
            }
        }
        
        outputFile << "\tTotal Distance: " << totalDistance << endl;
        outputFile << separator << " (end of summary)" << endl;
        
        QueueData * dijkstraData[(unsigned int) data->dijkstraResults->size()];
        unsigned int index = 0;
        
        for (map<char *, QueueData *,bool(*)(char *,char *)>::iterator it = data->dijkstraResults->begin(); it != data->
             dijkstraResults->end(); it++) {

            dijkstraData[index] = it->second;
        }
        
        for (index = 0; index < data->dijkstraResults->size(); index++) {
            printRouteTable(graph, dijkstraData[index]->node, dijkstraData, (unsigned int) data->dijkstraResults->size(), &outputFile);
        }
        
        outputFile.close();
    }
    else
        throw 5; // ERROR 5: unable to open file
}

#endif