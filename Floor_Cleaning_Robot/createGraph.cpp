
//
//  createGraph.cpp
//  Floor_Cleaning_Robot
//
//  Created by Christian on 2019/11/13.
//  Copyright © 2019 Christian. All rights reserved.
//

#include <iostream>
#include <vector>

#include "createGraph.hpp"

#define INFINITY 2000000000

using namespace std;

vector<path> result;

int MatrixGraph::MapAvaliableNodeCount(char** currentMap, int map_row, int map_column) {
    int count = 0 ;
    for (int i = 0; i < map_row; i++) {
        for (int j = 0; j < map_column; j++) {
            if (currentMap[i][j] == '1')
                count++;
        }
    }
        
    return count;
}

MatrixGraph::MatrixGraph(int start, int destination, int node_count, nodeInfo* array) {
    this -> start = start;
    this -> destination = destination;
    
    Graph = new int*[node_count]; // allocate an array of 10 int pointers — these are our rows
    for (int count = 0; count < node_count; ++count)
        Graph[count] = new int[node_count];
    
    dist = new int [node_count];
    parent = new int[node_count];
    
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            Graph[i][j] = INFINITY;
            dist[i] = INFINITY;
        }
        Graph[i][i] = 0;
    }
    
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            if (array[j].x_coordinate == array[i].x_coordinate && array[j].y_coordinate - array[i].y_coordinate == 1 ) {
                Graph[i][j] = 1;
            } else if (array[j].y_coordinate == array[i].y_coordinate && array[j].x_coordinate - array[i].x_coordinate == 1 ) {
                Graph[i][j] = 1;
            }
        }
    }
    
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            if(Graph[i][j] != INFINITY) {
                Graph[j][i] = Graph[i][j];
            }
        }
    }
}

nextState MatrixGraph::ShortestPath(const int start, int node_count, nodeInfo* array) {
    bool isVisted[node_count];
    bool firstCheck = false;
    nextState nextStateInfo;
    
    nextStateInfo.isGameOver = false;
    nextStateInfo.parent = new int[node_count];
    nextStateInfo.next_start_index = 0;
    
    for(int i = 0; i < node_count; i++) {
        nextStateInfo.parent[i] = -1;
        isVisted[i] = false;
        dist[i] = Graph[start][i];
    }

    isVisted[start] = true;
    dist[start] = 0;

    for(int i = 0; i < node_count - 1; i++) {
        int u = 0;
        int temp = 2000;

        for(int j = 0; j < node_count; j++) {
            if (j != start && dist[j] < temp && !isVisted[j]) {
                temp = dist[j];
                u = j;
            }
        }
        
        if (!firstCheck) {
            nextStateInfo.parent[u] = start;
            firstCheck = true;
        }

        isVisted[u] = true;

        for(int w = 0; w < node_count; w++) {
            if(!isVisted[w] && dist[u] + Graph[u][w] < dist[w]) {
                nextStateInfo.parent[w] = u;
                dist[w] = dist[u] + Graph[u][w];
            }
        }
    }
    
    return nextStateInfo;
}

void MatrixGraph::getPath(int destination, int parent[], nodeInfo* array) {
    if (parent[destination] == -1)
        return;
    
    getPath(parent[destination], parent, array);
    
    array[destination].isVisited = true;
    path tmp;
    tmp.x = array[destination].x_coordinate;
    tmp.y = array[destination].y_coordinate;
    result.push_back(tmp);
}

vector<path> MatrixGraph::returnResult() {
    return result;
}

nodeInfo* createNodeInfoArray(char** currentMap, int map_row, int map_column, int node_count) {
    nodeInfo* infoArray = new nodeInfo[node_count];
    int current_index = 0;
    
    for (int i = 0; i < map_row; i++) {
        for (int j = 0; j < map_column; j++) {
            if (currentMap[i][j] != '1') {
                infoArray[current_index].index = current_index;
                infoArray[current_index].isVisited = false;
                infoArray[current_index].charging_stop = (currentMap[i][j] == 'R') ? true : false;
                infoArray[current_index].x_coordinate = j;
                infoArray[current_index++].y_coordinate = i;
            }
        }
    }
    
    return infoArray;
}
