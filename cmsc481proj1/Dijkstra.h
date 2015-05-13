//
//  Dijkstra.h
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/30/2015.
//  Copyright (c) 2015 Andrew Huber. All rights reserved.
//

#ifndef __cmsc481proj1__Dijkstra__
#define __cmsc481proj1__Dijkstra__

#import "Graph.h"
#import <climits>
#import <stack>

using namespace std;

// Used by Dijkstra to get more information about each node. This information is used to find the shortest path.
struct QueueData {
    Node * node; // The node in the graph
    Node * prev; // The previous node along the shortest path
    unsigned int lowestCost; // The lowest cost to get to node
    bool visited; // whether or not this node was "visited"
    
    QueueData(Node * node) {
        this->node = node;
        this->prev = 0;
        this->lowestCost = UINT_MAX; // initialze to infinity
        this->visited = false; // initialize to false
    }
};

// Contains information when the shortest path is found
struct ShortestPathData {
    map<char *, QueueData *,bool(*)(char *,char *)> * dijkstraResults; // the results from Dijkstra
    stack<QueueData *> * shortestPathStack; // when each QueueData pointer is popped, the shortest path from the start to the end is
                                            // revealed
    
    ShortestPathData(map<char *, QueueData *,bool(*)(char *,char *)> * dijkstraResults, stack<QueueData *> * shortestPathStack) {
        this->dijkstraResults = dijkstraResults;
        this->shortestPathStack = shortestPathStack;
    }
};

// Runs the Dijkstra's algorithm
//
// RETURNS: a map with node names as the key and QueueData pointers as the value

map<char *, QueueData *,bool(*)(char *,char *)> * dijkstra(Graph * graph, // the graph to analyze
                                                           
                                                           char * startNode); // the name of the start node

// Uses Dijkstra's algorithm to find the shortest path between a start and end node
//
// RETURNS: a pointer to a ShortestPathData containing information regarding the shortest patch

ShortestPathData * shortestPath(Graph * graph, // a pointer to a Graph
                                
                                char * startNode, // the name of the start node
                                
                                char * endNode);  // the name of the end node

// Uses Dijkstra's algorithm to find the shortest path between a start and end node. Hides the implementation of
// shortestPath(Graph *, char *, char *) from the user
//
// RETURNS: a pointer to a ShortestPathData containing information regarding the shortest path

ShortestPathData * shortestPath(map<char *, QueueData *,bool(*)(char *,char *)> * dijkstraMap, // the results from Dijkstra
                                
                                char * startNode, // the name of the start node
                                
                                char * endNode); // the name of the end node

#endif /* defined(__cmsc481proj1__Dijkstra__) */