//
//  Proj_1_IO.cpp
//  cmsc481proj1
//
//  Created by Andrew Huber on 4/30/2015.
//
// Performs the I/O operations for this project
//

#ifndef __cmsc481proj1__Proj_1_IO
#define __cmsc481proj1__Proj_1_IO

#include "Proj_1_IO.h"
#include <iomanip>

// After a line of the input file is read and the string is separated into tokens, this function analyzes the tokens by either
// adding node(s) to the graph, adding link(s) to the graph, and/or setting sourceNodeName or destinationNodeName

void processTokens(string * tokens, // a string array containing the tokens
                   
                   Graph * graph, // a pointer to the Graph being built
                   
                   char * sourceNodeName, // a char pointer that will be altered if the tokens indicate that the source node is being
                                          // specified
                   
                   char * destinationNodeName) // a char pointer that will be altered if the tokens indicate that the source node
                                               // is being specified
{
    
    for(int a = 0; a < 3; a++) { // For every token
        
        for(int b = 0; b < tokens[a].length(); b++) { // For every character in the token

            tokens[a][b] = (char) tolower(tokens[a][b]); // Convert the character to lowercase and store it back
            
        }
    }
    
    if (tokens[0].compare("source") == 0)
        strcpy(sourceNodeName, tokens[1].c_str());
    else if(tokens[0].compare("destination") == 0)
        strcpy(destinationNodeName, tokens[1].c_str());
    else {
        const char * POINT_A_NAME = tokens[0].c_str();
        const char * POINT_B_NAME = tokens[1].c_str();
        const char * WEIGHT_STR   = tokens[2].c_str();
        
        char * pointAname = new char[100];
        char * pointBname = new char[100];
        
        strcpy(pointAname, POINT_A_NAME);
        strcpy(pointBname, POINT_B_NAME);
        
        int  weight = atoi(WEIGHT_STR);
        
        // See if Point A and Point B already exist in the graph
        Node * pointA = graph->getNode(pointAname);
        Node * pointB = graph->getNode(pointBname);
        
        // If Point A does not exist in the graph
        if(pointA == 0) {
            graph->addNode(pointAname); // add Point A to the graph
            pointA = graph->getNode(pointAname); // get the point that was just added
        }
        // If Point B does not exist in the graph
        if(pointB == 0) {
            graph->addNode(pointBname); // add Point B to the graph
            pointB = graph->getNode(pointBname); // get the point that was just added
        }
        
        
        if (pointA->isLinked(pointB) || pointB->isLinked(pointA)) { // if Point A is linked with Point B or vice versa
            throw 3; // ERROR 3: nodes are already linked
        }
        else {
            pointA->addLink(pointB, weight);
            pointB->addLink(pointA, weight);
        }
    }
}

// This separates the contents of the char buffer containing the contents of one line of the input file. It then sends
// the list of tokens it collected to processTokens(string *, Graph *, char *, char *)

void processBuffer(char * buffer, // the buffer to process
                   
                   const int BUFFER_SIZE, // the size of the buffer
                
                   Graph * graph, // the graph we are constructing
                
                   char * sourceNodeName, // a pointer to the name of the source node; will be altered in
                                          // processTokens(string *, Graph *, char *, char *) if needed
                   
                   char * destinationNodeName) // a pointer to the name of the destination node; will be altered in
                                               // processTokens(string *, Graph *, char *, char *) if needed
{
    
    string tokens[3];
    
    tokens[0] = "";
    tokens[1] = "";
    tokens[2] = "";
    
    int tokenIndex = 0;
    
    for (int bufferInd = 0; bufferInd < BUFFER_SIZE; bufferInd++) {
        if (buffer[bufferInd] == 0) { // if the null character is found in the buffer
            tokenIndex = 0;
            processTokens(tokens, graph, sourceNodeName, destinationNodeName);
            bufferInd = BUFFER_SIZE;
        }
        else if (buffer[bufferInd] == '$') // if the separator has been found
            tokenIndex++;
        else
            tokens[tokenIndex] += buffer[bufferInd]; // append the current character
    }
}

// Reads the contents of the file line by line. Then, for each line read, the line is sent to void
// processBuffer(char *, const int, Graph *, char *, char *)

void readFile(char * fileName, // the name of the input file
              
              Graph * graph, // the graph to which we will add nodes
              
              char * sourceNodeName, // a char pointer that will be updated to contain the name of the source node
              
              char * destinationNodeName) // a char pointer that will be updated to contain the name of the destination node
{
    ifstream file;
    file.open(fileName);
    const int BUFFER_SIZE = 100;
    
    if(file.is_open()) {
        char buffer[BUFFER_SIZE];
        while (!file.eof()) {
            file >> buffer; // read line
            processBuffer(buffer, BUFFER_SIZE, graph, sourceNodeName, destinationNodeName); // process line
        }
    }
    else {
        printf("Unable to open %s\n", fileName);
        throw 4; // ERROR 4: unable to open file
    }
}

// Finds all immediate neighbors along the shortest path AWAY from the source node
//
// RETURNS: a pair containing an array of unsigned ints as the first argument and the length of the array as the second argument

pair<unsigned int *, unsigned int> * findAllImmediateAndSubsequentNeighbors(QueueData ** dijkstraData, // An array of QueueData pointers
                                                                                                       // containing all the vital data
                                                                                                       // from when Dijkstra was performed
                                                                            
                                                                            unsigned int lengthOfDijkstraData, // length of dijkstraData
                                                                            
                                                                            char * nodeName) // the nodes AFTER nodeName will be checked
{
    unsigned int * indicies = new unsigned int[lengthOfDijkstraData]; // will store indicies of the subsequent nodes in djikstraData
    unsigned int index = 0;
    
    for (unsigned int i = 0; i < lengthOfDijkstraData; i++) {
        if (dijkstraData[i]->prev != 0) { // if the dijkstra algorithm stored the previous node
            
            // if the dijkstra algorithm stored nodeName as the subsequent node, store the index "i" in indicies
            if(strcmp(dijkstraData[i]->prev->getNodeName(), nodeName) == 0) {
                indicies[index] = i;
                index++;
            }
        }
    }
    
    return new pair<unsigned int *, unsigned int>(indicies, index);
}

// Finds the next hop for every node along the shortest path from a particular node
//
// RETURNS: a pointer to a Node that contains the next hop

Node * updateNextHops(QueueData ** dijkstraData, // an array of QueueData pointers containing the vital data from when Dijkstra was performed
                      
                      QueueData ** routeTable, // the route table being constructed
                      
                      unsigned int length, // the length of dijkstraData, which should be the same as the length of the route table
                      
                      Node * node, // used to indicate the original node
                      
                      Node * currNode) // used to progress through the tree
{
    // Find all nodes following currNode
    pair<unsigned int *, unsigned int> * nextNodePair =
        findAllImmediateAndSubsequentNeighbors(dijkstraData, length, currNode->getNodeName());
    
    // Pull out the data from the pair
    unsigned int * indiciesOfNextNodes = nextNodePair->first;
    unsigned int numberOfNextNodes = nextNodePair->second;
    
    // For every subsequent node
    for (unsigned int i = 0; i < numberOfNextNodes; i++) {
        
        Node * prev = 0;
        
        // If the node == currNode, then a recursive call has not been made yet. This means that we need to recursively call
        // this function with node = routeTable[indiciesOfNextNodes[i]]
        if(node == currNode) {
            prev = updateNextHops(dijkstraData, routeTable, length, routeTable[indiciesOfNextNodes[i]]->node,
                                  routeTable[indiciesOfNextNodes[i]]->node);
        }
        
        // If the node != currNode, then a recursive call has been made. This means that we need to recursively call this function
        // WITHOUT changing the value of node
        else {
            prev = updateNextHops(dijkstraData, routeTable, length, node, routeTable[indiciesOfNextNodes[i]]->node);
        }

        routeTable[indiciesOfNextNodes[i]]->prev = prev; // update the route table with the correct information
    }
    
    return node; // return node so previous nodes can be properly updated
}

// Makes the route table
//
// RETURNS: the route table; every prev entry in every QueueData pointer contains the next hop

QueueData ** makeRouteTable(Graph * graph, // the to which Dijkstra was applied
                            
                            Node * node, // node's route table will be made in this method

                            QueueData ** dijkstraData, // an array of QueueData pointers containing the vital data from when Dijkstra
                                                       // was performed
                            
                            unsigned int lengthOfDijkstraData) // length of dijkstraData
{
    pair<pair<char *, Node *> *, unsigned int> * allNodesPair = graph->getAllNodes(); // get all nodes in graph

    // Extract information from allNodesPair
    pair<char *, Node *> * allNodes = allNodesPair->first;
    unsigned int numberOfNodesInGraph = allNodesPair->second;
    
    // Make the route table
    QueueData ** routeTable = new QueueData * [numberOfNodesInGraph];
    
    // Will contain the index of node in allNodes
    unsigned int indexOfNode = 0;
    
    // For all the nodes in the table
    for(int i = 0; i < numberOfNodesInGraph; i++) {
        routeTable[i] = new QueueData(allNodes[i].second); // Create a new QueueData object using the ith node in the graph
        routeTable[i]->lowestCost = dijkstraData[i]->lowestCost; // Copy the lowest cost calculated in Dijkstra to the route table
        
        if(strcmp(routeTable[i]->node->getNodeName(), node->getNodeName()) == 0) { // if node is located at index i
            indexOfNode = i;
        }
    }

    // Call updateNextHops(Graph *, Node *, QueueData **, unsigned int)
    updateNextHops(dijkstraData, routeTable, lengthOfDijkstraData, routeTable[indexOfNode]->node, routeTable[indexOfNode]->node);
    
    // return the route table that updateNextHops(Graph *, Node *, QueueData **, unsigned int) created
    return routeTable;
}

// Writes the route table to the output file

void writeRouteTable(Graph * graph, // the graph to which Dijkstra was applied
                     
                     Node * node, // the node whose route table will be printed
                     
                     QueueData ** dijkstraData, // an array of QueueData pointers that contains vital data when Dijkstra was performed
                     
                     unsigned int lengthOfDijkstraData, // the length of dijkstraData
                     
                     ostream * outputFile) // ostream pointer that will allow writeRouteTable to write to the output file
{
    *outputFile << "Route Table of Node " << node->getNodeName() << endl << endl;
    
    QueueData ** routeTable = makeRouteTable(graph, node, dijkstraData, lengthOfDijkstraData);
    bool atLeastOneEntry = false;
    
    for (unsigned int i = 0; i < lengthOfDijkstraData; i++) {
        QueueData * entry = routeTable[i];
        unsigned int distance = dijkstraData[i]->lowestCost;
        
        if (entry->prev != 0) { // if entry follows node
            
            if(strcmp(entry->node->getNodeName(), node->getNodeName()) != 0) {
                
                if(!atLeastOneEntry) {
                    *outputFile << "\tTO    NEXT HOP    DISTANCE" << endl;
                }
                
                *outputFile << "\t" << setw(2) << entry->node->getNodeName() << setw(0) << "    ";
                *outputFile << setw(8) << entry->prev->getNodeName() << setw(0) << "    ";
                *outputFile << setw(8) << distance << setw(0) << endl;
                atLeastOneEntry = true;
            }
        }
    }
    
    if(!atLeastOneEntry) {
        *outputFile << "\tEMPTY" << endl;
    }
    
    *outputFile << endl;
}

// Writes the results of Dijkstra's to the output file

void writeFile(char * fileName, // the name of the output file
               
               Graph * graph, // the graph to which Dijkstra's was applied
               
               ShortestPathData * data, // the information returned by Dijkstra's
               
               char * sourceNodeName, // the name of the source node
               
               char * desinationNodeName) // the name of the destination node
{
    ofstream outputFile;
    outputFile.open(fileName);

    if(outputFile.is_open()) {
        const char * separator = "------------------------------------------------";
        
        // Print summary
        outputFile << separator << " (beginning of summary)" << endl;
        outputFile << "The shortest path from " << sourceNodeName << " to " << desinationNodeName << " is:" << endl;
        outputFile << "\t";
        
        unsigned int totalDistance = 0;
        
        while (data->shortestPathStack->size() > 0) {
            totalDistance = data->shortestPathStack->top()->lowestCost;
            
            QueueData * qd = data->shortestPathStack->top();
            
            data->shortestPathStack->pop();
            
            outputFile << qd->node->getNodeName();
            
            if (data->shortestPathStack->size() > 0) {
                outputFile << " -> ";
            }
            else {
                outputFile << endl;
            }
        }
        
        outputFile << "\tTotal Distance: " << totalDistance << endl;
        outputFile << separator << " (end of summary)" << endl;
        
        // Compile a list of QueueData pointers to be used in constructing the route table
        QueueData * dijkstraData[(unsigned int) data->dijkstraResults->size()];
        unsigned int index = 0;
        
        for (map<char *, QueueData *,bool(*)(char *,char *)>::iterator it = data->dijkstraResults->begin(); it != data->
             dijkstraResults->end(); it++) {

            dijkstraData[index] = it->second;
            index++;
        }
        
        // Write the route table for each node
        for (index = 0; index < data->dijkstraResults->size(); index++) {
            writeRouteTable(graph, dijkstraData[index]->node, dijkstraData, (unsigned int) data->dijkstraResults->size(), &outputFile);
        }
        
        outputFile.close();
    }
    else
        throw 5; // ERROR 5: unable to open file
}

#endif