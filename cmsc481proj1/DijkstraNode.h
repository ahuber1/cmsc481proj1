//
//  DijkstraNode.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_DijkstraNode_h
#define cmsc481proj1_DijkstraNode_h

class DijkstraNode : public Node {
    
public:
    Pair<Node,int>[] getUnvisitedLinks();
    void setShortestNeighbor(Pair<Node, int> shortestNeighbor);
    Pair<Node, int> getShortestNeighbor();
    
private:
    bool visited;
    Pair<Node, int> shortestNeighbor;
};

#endif
