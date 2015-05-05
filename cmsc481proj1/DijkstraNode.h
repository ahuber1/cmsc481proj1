//
//  DijkstraNode.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_DijkstraNode_h
#define cmsc481proj1_DijkstraNode_h

#include "Node.h"

class DijkstraNode : public Node {
    
public:
    DijkstraNode();
    DijkstraNode(char * nodeName);
    pair<pair<Node *, unsigned int> *, unsigned int> getUnvisitedLinks();
    void setShortestNeighbor(pair<Node *, unsigned int> * shortestNeighbor);
    pair<Node *,unsigned int> getShortestNeighbor();
    
private:
    bool visited;
    pair<Node *, unsigned int> * shortestNeighbor;
};

#endif
