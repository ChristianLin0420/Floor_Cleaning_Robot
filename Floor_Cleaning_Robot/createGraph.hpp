//
//  createGraph.hpp
//  Floor_Cleaning_Robot
//
//  Created by Christian on 2019/11/13.
//  Copyright © 2019 Christian. All rights reserved.
//

#ifndef createGraph_hpp
#define createGraph_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

struct path {
    int x;
    int y;
};

struct nodeInfo {
    int x_coordinate;
    int y_coordinate;
    int index; // -1 represents
    bool charging_stop;
    bool isVisited;
};

struct nextState {
    int next_start_index;
    int* parent;
    int isGameOver;
};

class MatrixGraph{
private:
    int** Graph;
    int* dist;
    int* parent;
    int start,destination;
public:
    MatrixGraph();
    MatrixGraph(int start,int destination, int node_count, nodeInfo* array);
    nextState ShortestPath(const int v, int node_count, nodeInfo* array);
    void getPath(int d, int parent[], nodeInfo* array);
    std::vector<path> returnResult();
    int MapAvaliableNodeCount(char** currentMap, int map_row, int map_column);
};

nodeInfo* createNodeInfoArray(char** currentMap, int map_row, int map_column, int node_count);

#endif /* createGraph_hpp */
