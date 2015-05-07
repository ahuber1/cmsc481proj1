//
//  Dijkstra.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/30/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef __cmsc481proj1__Dijkstra__cpp
#define __cmsc481proj1__Dijkstra__cpp

#include "Dijkstra.h"
#include <iostream>

bool compareQueueData(char * left, char * right) {
    return strcmp(left, right) < 0;
}

QueueData * findNextNode(map<char *, QueueData *, bool(*)(char*, char*)> * mapPtr) {
    map<char *, QueueData *,bool(*)(char*,char*)> m = *mapPtr;
    QueueData * nextNode = new QueueData(0);
    
    for (map<char *, QueueData *>::iterator it = m.begin(); it != m.end(); it++) {
        QueueData * currNode = it->second;
        
        if(currNode->lowestCost < nextNode->lowestCost && currNode->visited == false)
            nextNode = currNode;
    }
    
    return nextNode;
}

map<char *, QueueData *,bool(*)(char *,char *)> * dijkstra(Graph * graph, char * startNode) {
    map<char *, QueueData *,bool(*)(char *,char *)> * lowestCostData = new map<char *, QueueData *, bool(*)(char*, char*)>(compareQueueData);
    pair<pair<char *, Node *> *, unsigned int> * graphNodesPair = graph->getAllNodes();
    pair<char *, Node *> * graphNodes = graphNodesPair->first;
    unsigned int numberOfNodes = graphNodesPair->second;
    
    for (int i = 0; i < numberOfNodes; i++) {
        char * first = graphNodes[i].first;
        Node * node = graphNodes[i].second;
        QueueData * second = new QueueData(node);
        lowestCostData->insert(pair<char *, QueueData *>(first, second));
    }
    
    QueueData * currentNodeQueueData = lowestCostData->find(startNode)->second;
    currentNodeQueueData->lowestCost = 0;
    
    for (int a = 0; a < numberOfNodes; a++) {
        
        cout << currentNodeQueueData->node->getNodeName() << ", " << currentNodeQueueData->lowestCost << endl;
        
        currentNodeQueueData->visited = true;
        pair<pair<Node *, unsigned int> *, unsigned int> * linksPair = currentNodeQueueData->node->getLinks();
        pair<Node *, unsigned int> * links = linksPair->first;
        unsigned int numberOfLinks = linksPair->second;

        for (int b = 0; b < numberOfLinks; b++) {
            Node * currentLink = links[b].first;
            unsigned int currentLinkWeight = links[b].second;
            char * currentLinkName = currentLink->getNodeName();
            QueueData * currentLinkQueueData = lowestCostData->find(currentLinkName)->second;
            unsigned int calculatedWeight = currentNodeQueueData->lowestCost + currentLinkWeight;
            
            if (calculatedWeight < currentLinkQueueData->lowestCost) {
                currentLinkQueueData->prev = currentNodeQueueData->node;
                currentLinkQueueData->lowestCost = calculatedWeight;
            }
        }
        
        currentNodeQueueData = findNextNode(lowestCostData);
    }
    
    return lowestCostData;
}

stack<QueueData *> * shortestPath(Graph * graph, char * startNode, char * endNode) {
    stack<QueueData *> * steps = new stack<QueueData *>();
    map<char *, QueueData *,bool(*)(char *,char *)> * results = dijkstra(graph, startNode);
    QueueData * dq = results->find(endNode)->second;
    
    while(strcmp(dq->node->getNodeName(), startNode) != 0) {
        steps->push(dq);
        dq = results->find(dq->prev->getNodeName())->second;
    }
    
    return steps;
}

#endif