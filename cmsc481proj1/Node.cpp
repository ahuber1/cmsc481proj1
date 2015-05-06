//
//  Node.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_Node_cpp
#define cmsc481proj1_Node_cpp

#include "Node.h"

using namespace std;

bool comparator(Node * left, Node * right) {
    char * l_name_ptr = left->getNodeName();
    char * r_name_ptr = right->getNodeName();
    char l_name = *l_name_ptr;
    char r_name = *r_name_ptr;
    
    return l_name < r_name;
}

Node::Node() {
    Node(0);
}

Node::Node(char * nodeName) {
    this->nodeName = nodeName;
    neighbors = map<Node *, unsigned int, bool(*)(Node *, Node *)>(comparator);
}

void Node::addLink(Node * pointB, unsigned int weight) {
    
    if (neighbors.find(pointB) == neighbors.end())
        neighbors.insert(pair<Node *, int>(pointB, weight));
    else
        throw 1; // ERROR 1: duplicate links
}

bool Node::isLinked(Node *otherNode) {
    pair<pair<Node *, unsigned int> *, unsigned int> * linksPair = getLinks();
    
    for (int i = 0; i < linksPair->second; i++) {
        if (*linksPair->first[i].first == *otherNode)
            return true;
    }
    
    return false;
}

pair<pair<Node *, unsigned int> *, unsigned int> * Node::getLinks() {
    
    pair<Node *, unsigned int> * links = new pair<Node *, unsigned int>[neighbors.size()];
    unsigned int i = 0;
    
    for (map<Node *, unsigned int>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
        links[i] = pair<Node *, unsigned int>(it->first, it->second);
        i++;
    }
    
    return new pair<pair<Node *, unsigned int> *, unsigned int>(links, i);
}

bool Node::operator==(const Node otherNode) {
    return strcmp(nodeName, otherNode.nodeName) == 0;
}

bool Node::operator==(const Node *otherNode) {
    return strcmp(nodeName, otherNode->nodeName) == 0;
}

char * Node::getNodeName() {
    return nodeName;
}

#endif