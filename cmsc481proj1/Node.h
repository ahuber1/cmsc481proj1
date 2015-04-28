//
//  Node.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/28/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef cmsc481proj1_Node_h
#define cmsc481proj1_Node_h

using namespace std;

class Node {
    
public:
    Node(char * nodeName);
    void addLink(Node pointB, int weight);
    Pair<Char *, int>[] getLinks();
    
private:
    template<typedef K, typedef V>
    struct Pair {
        K key;
        V value;
    };
    
    map<Node, int> neighbors;
    char * nodeName;
};

#endif
