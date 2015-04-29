//
//  Node.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#include <stdio.h>
#include "Node.h"

using namespace std;

Node::Node(char * nodeName) {
    
    if (nodeName == 0)
        throw 0; // nodeName is null
    
    this->nodeName = nodeName;
    neighbors = map<Node, int>();
}

void Node::addLink(Node pointB, int weight) {
    if (neighbors.find(pointB) == neighbors.end())
        neighbors.insert(pair<Node, int>(pointB, weight));
    else
        throw 1; // ERROR 1: duplicate links
}

pair<pair<Node, int> *, int> Node::getLinks() {
    
    pair<Node, int> * links = new pair<Node,int>[neighbors.size()];
    int i = 0;
    
    for (map<Node, int>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
        links[i] = pair<Node, int>(it->first, it->second);
        i++;
    }
    
    return pair<pair<Node, int> *, int>(links, i);
}

bool Node::operator==(const Node otherNode) {
    return strcmp(nodeName, otherNode.nodeName) == 0;
}

bool Node::operator==(const Node *otherNode) {
    return strcmp(nodeName, otherNode->nodeName) == 0;
}