//
//  Dijkstra.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/30/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#include "Dijkstra.h"
#include "DijkstraNode.h"

void dijkstra(Node * currentNode) {
    DijkstraNode * dnCurrentNode = static_cast<DijkstraNode *>(currentNode);
    pair<pair<Node *, unsigned int> *, unsigned int> dnCurrentNodeUnvisitedLinksPair = dnCurrentNode->getUnvisitedLinks();
    pair<Node *, unsigned int> * unvisitedLinks = dnCurrentNodeUnvisitedLinksPair.first;
    unsigned int dnCurrentNodeNumberOfUnvisitedLinks = dnCurrentNodeUnvisitedLinksPair.second;
    
    DijkstraNode * nextNode = 0;
    
    for (int i = 0; i < dnCurrentNodeNumberOfUnvisitedLinks; i++) {
        pair<Node *, unsigned int> unvisitedLinkPair = unvisitedLinks[i];
        Node * unvisitedLink = unvisitedLinkPair.first;
        DijkstraNode * dnUnvisitedLink = static_cast<DijkstraNode *>(unvisitedLink);
        unsigned int weightOfUnvisitedLink = unvisitedLinkPair.second;
        
        pair<Node *, unsigned int> shortestLinkOfUnvisitedLinkPair = dnUnvisitedLink->getShortestNeighbor();
        unsigned int weightOfShortestLinkOfUnvisitedLink = shortestLinkOfUnvisitedLinkPair.second;
        
        pair<Node *, unsigned int> shortestLinkOfCurrentNodePair = dnCurrentNode->getShortestNeighbor();
        unsigned int weightOfShortestLink = shortestLinkOfCurrentNodePair.second;
        
        unsigned int calculatedWeight = weightOfUnvisitedLink + weightOfShortestLink;
        if (weightOfShortestLinkOfUnvisitedLink > calculatedWeight) {
            dnUnvisitedLink->setShortestNeighbor(new pair<Node *, unsigned int>(currentNode, calculatedWeight));
        }
        
        if (nextNode == 0) {
            nextNode = dnUnvisitedLink;
        }
        else if(dnUnvisitedLink->getShortestNeighbor().second < nextNode->getShortestNeighbor().second) {
            Node * newNextNode = dnUnvisitedLink->getShortestNeighbor().first;
            DijkstraNode * dnNewNextNode = static_cast<DijkstraNode *>(newNextNode);
            nextNode = dnNewNextNode;
        }
    }
    
    if (nextNode != 0) {
        dijkstra(currentNode);
    }
}

void dijkstra(DijkstraGraph * graph, char * startNode) {
    Node * startNodePtr = graph->getNode(startNode);
    DijkstraNode * dnStartNode = static_cast<DijkstraNode *>(startNodePtr);
    dnStartNode->setShortestNeighbor(new pair<Node *, unsigned int>(0, 0));
    dijkstra(dnStartNode);
}