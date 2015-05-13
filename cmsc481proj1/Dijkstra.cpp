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

// A comparator used in the map
bool compareQueueData(char * left, char * right) {
    return strcmp(left, right) < 0;
}

// Finds the next unvisited node that has the shortest cumulative length
//
// RETURNS: the next node in the form of a QueueData pointer containing an actual pointer to a Node object

QueueData * findNextNode(map<char *, QueueData *, bool(*)(char*, char*)> * mapPtr) // the map containing the data from Dijkstra
{
    map<char *, QueueData *,bool(*)(char*,char*)> m = *mapPtr;
    QueueData * nextNode = new QueueData(0);
    
    for (map<char *, QueueData *>::iterator it = m.begin(); it != m.end(); it++) {
        QueueData * currNode = it->second;
        
        if(currNode->lowestCost < nextNode->lowestCost && currNode->visited == false)
            nextNode = currNode;
    }
    
    return nextNode;
}

// Runs the Dijkstra's algorithm
//
// RETURNS: a map with node names as the key and QueueData pointers as the value

map<char *, QueueData *,bool(*)(char *,char *)> * dijkstra(Graph * graph, // the graph to analyze
                                                           
                                                           char * startNode) // the name of the start node
{
    map<char *, QueueData *,bool(*)(char *,char *)> * lowestCostData =
        new map<char *, QueueData *, bool(*)(char*, char*)>(compareQueueData);
    
    // Gets all nodes in the graph
    pair<pair<char *, Node *> *, unsigned int> * graphNodesPair = graph->getAllNodes();
    
    // Extract the contents of graphNodesPair
    pair<char *, Node *> * graphNodes = graphNodesPair->first;
    unsigned int numberOfNodes = graphNodesPair->second;
    
    // Fill lowestCostData with data
    for (int i = 0; i < numberOfNodes; i++) {
        char * first = graphNodes[i].first;
        Node * node = graphNodes[i].second;
        QueueData * second = new QueueData(node);
        lowestCostData->insert(pair<char *, QueueData *>(first, second));
    }
    
    // Find the QueueData pointer that corresponds with startNode
    QueueData * currentNodeQueueData = lowestCostData->find(startNode)->second;
    currentNodeQueueData->lowestCost = 0;
    
    for (int a = 0; a < numberOfNodes; a++) {        
        currentNodeQueueData->visited = true; // set the current node as visited
        
        // Get the current node's links
        pair<pair<Node *, unsigned int> *, unsigned int> * linksPair = currentNodeQueueData->node->getLinks();
        
        // Extract the contents of linksPair
        pair<Node *, unsigned int> * links = linksPair->first;
        unsigned int numberOfLinks = linksPair->second;

        // For every link
        for (int b = 0; b < numberOfLinks; b++) {
            // Extract the contents of links[b]
            Node * currentLink = links[b].first;
            unsigned int currentLinkWeight = links[b].second;
            
            char * currentLinkName = currentLink->getNodeName(); // get link's name
            QueueData * currentLinkQueueData = lowestCostData->find(currentLinkName)->second; // find the link's corresponding
                                                                                              // QueueData pointer
            
            unsigned int calculatedWeight = currentNodeQueueData->lowestCost + currentLinkWeight; // calculate the sum of the length of the
                                                                                                  // current link and current node
            
            if (calculatedWeight < currentLinkQueueData->lowestCost) { // if calculatedWeight is less than the lowest cost of the current link
                // update the current link's prev reference and lowest cost
                currentLinkQueueData->prev = currentNodeQueueData->node;
                currentLinkQueueData->lowestCost = calculatedWeight;
            }
        }
        
        currentNodeQueueData = findNextNode(lowestCostData); // find the next node with the lowest cost
    }
    
    return lowestCostData;
}

// Uses Dijkstra's algorithm to find the shortest path between a start and end node
//
// RETURNS: a pointer to a ShortestPathData containing information regarding the shortest patch

ShortestPathData * shortestPath(Graph * graph, // a pointer to a Graph
                                char * startNode, // the name of the start node
                                char * endNode) { // the name of the end node
    return shortestPath(dijkstra(graph, startNode), startNode, endNode);
}

// Uses Dijkstra's algorithm to find the shortest path between a start and end node. Hides the implementation of
// shortestPath(Graph *, char *, char *) from the user
//
// RETURNS: a pointer to a ShortestPathData containing information regarding the shortest path

ShortestPathData * shortestPath(map<char *, QueueData *,bool(*)(char *,char *)> * dijkstraMap, char * startNode, char * endNode) {

    // This stack will contain the steps that one will take along the shortest path. When each QueueData pointer is popped, each step
    // from startNode to endNode is revealed
    stack<QueueData *> * steps = new stack<QueueData *>();
    
    // Find the destination node from the results of Dijkstra
    QueueData * dq = dijkstraMap->find(endNode)->second;
    
    // Until we reach the start node
    while(strcmp(dq->node->getNodeName(), startNode) != 0) {
        steps->push(dq); // push the node onto the stack
        dq = dijkstraMap->find(dq->prev->getNodeName())->second; // move closer to the start node
    }
    
    steps->push(dq); // push the start node onto the map
    
    return new ShortestPathData(dijkstraMap, steps);
}

#endif