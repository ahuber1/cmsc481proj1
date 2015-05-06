//
//  Node.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_Node_h
#define cmsc481proj1_Node_h

#include <map>

using namespace std;

class Node {
    
public:
    Node();
    Node(char * nodeName);
    void addLink(Node * pointB, unsigned int weight);
    pair<pair<Node *, unsigned int> *, unsigned int> * getLinks();
    bool isLinked(Node * otherNode);
    bool operator==(const Node otherNode);
    bool operator==(const Node * otherNode);
    char * getNodeName();
    
private:
    map<Node *, unsigned int, bool(*)(Node *, Node *)> neighbors;
    char * nodeName;
};

#endif