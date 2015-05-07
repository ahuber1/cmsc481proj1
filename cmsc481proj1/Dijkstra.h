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

struct QueueData {
    Node * node;
    Node * prev;
    unsigned int lowestCost;
    bool visited;
    
    QueueData(Node * node) {
        this->node = node;
        this->prev = 0;
        this->lowestCost = UINT_MAX;
        this->visited = false;
    }
};

struct ShortestPathData {
    map<char *, QueueData *,bool(*)(char *,char *)> * dijkstraResults;
    stack<QueueData *> * shortestPathStack;
    
    ShortestPathData(map<char *, QueueData *,bool(*)(char *,char *)> * dijkstraResults, stack<QueueData *> * shortestPathStack) {
        this->dijkstraResults = dijkstraResults;
        this->shortestPathStack = shortestPathStack;
    }
};

map<char *, QueueData *,bool(*)(char *,char *)> * dijkstra(Graph * graph, char * startNode);
ShortestPathData * shortestPath(Graph * graph, char * startNode, char * endNode);
ShortestPathData * shortestPath(map<char *, QueueData *,bool(*)(char *,char *)> *  dijkstraMap, char * startNode, char * endNode);

#endif /* defined(__cmsc481proj1__Dijkstra__) */