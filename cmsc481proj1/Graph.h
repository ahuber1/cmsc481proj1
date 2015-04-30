//
//  Graph.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_Graph_h
#define cmsc481proj1_Graph_h

#include "Node.h"

using namespace std;

class Graph {
    
public:
    Graph();
    void addNode(char * nodeName);
    Node * getNode(char * nodeName);
    
protected:
    void addNode(Node nodeToAdd);
    
private:
    map<char *, Node, bool(*)(char*,char*)> nodes;
};

#endif
