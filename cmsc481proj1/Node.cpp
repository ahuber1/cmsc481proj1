//
//  Node.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//
//
//

#ifndef cmsc481proj1_Node_cpp
#define cmsc481proj1_Node_cpp

#include "Node.h"

using namespace std;

// A custom comparator used in the map
bool comparator(Node * left, Node * right) {
    char * l_name_ptr = left->getNodeName();
    char * r_name_ptr = right->getNodeName();
    char l_name = *l_name_ptr;
    char r_name = *r_name_ptr;
    
    return l_name < r_name;
}

// Makes a new node and sets this node name to 0 (null)
Node::Node() {
    Node(0);
}

// Creates a new node with a certain node name
Node::Node(char * nodeName) // the name of the node
{
    this->nodeName = nodeName;
    neighbors = map<Node *, unsigned int, bool(*)(Node *, Node *)>(comparator);
}

// Connects two nodes: this node is considered to be point A
void Node::addLink(Node * pointB, // the other Node to connect to
                   unsigned int weight) // the weight between the two nodes
{
    
    if (neighbors.find(pointB) == neighbors.end())
        neighbors.insert(pair<Node *, int>(pointB, weight));
    else
        throw 1; // ERROR 1: duplicate links
}


// Tests whether or not this node is connected with "otherNode"
//
// RETURNS: true if this node is connected with "otherNode",
// false if it is not
bool Node::isLinked(Node *otherNode) {
    pair<pair<Node *, unsigned int> *, unsigned int> * linksPair = getLinks();
    
    for (int i = 0; i < linksPair->second; i++) {
        if (*linksPair->first[i].first == *otherNode)
            return true;
    }
    
    return false;
}

// Gets all the nodes that this node is connected to
//
// RETURNS: a pair pointer (p1) that contains an array of pair pointers
// (p2) and an unsigned int (l) that specifies the size of p2. In p2,
// each pair pointer has a Node pointer as the key and an unsigned int
// as the value. The Node pointer specifies a Node to which this node is
// connnected to and the unsigned int specifies the weight of that link.
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