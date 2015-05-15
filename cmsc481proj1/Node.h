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
    // Makes a new node and sets this node name to 0 (null)
    Node();
    
    // Creates a new node with a certain node name
    Node(char * nodeName); // the name of the node
    
    // Connects two links: this node is considered Point A
    void addLink(Node * pointB, // the other Node to connect to
                 unsigned int weight); // the weight between the two nodes
    
    // Gets all the nodes that this node is connected to
    //
    // RETURNS: a pair pointer (p1) that contains an array of pair pointers
    // (p2) and an unsigned int (l) that specifies the size of p2. In p2,
    // each pair pointer has a Node pointer as the key and an unsigned int
    // as the value. The Node pointer specifies a Node to which this node is
    // connnected to and the unsigned int specifies the weight of that link.
    pair<pair<Node *, unsigned int> *, unsigned int> * getLinks();
    
    // Tests whether or not this node is connected with "otherNode"
    //
    // RETURNS: true if this node is connected with "otherNode",
    // false if it is not
    bool isLinked(Node * otherNode);
    
    bool operator==(const Node otherNode);
    bool operator==(const Node * otherNode);
    char * getNodeName();
    
private:
    
    // A map containing information about this Node's neighbors
    // (i.e., the other nodes to which this node is connected to).
    // The keys are Node pointers specifying the neighbor and
    // the values are the weights of the link between this node
    // and the other node
    map<Node *, unsigned int, bool(*)(Node *, Node *)> neighbors;
    
    char * nodeName;
};

#endif