//
//  main.cpp
//  Floor_Cleaning_Robot
//
//  Created by Christian on 2019/11/3.
//  Copyright © 2019 Christian. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "BoardInitial.hpp"
#include "createGraph.hpp"

#define MAX_COMMEND_SIZE 1000
#define MAA_BOARD_INFO_SIZE 15

using namespace std;

FILE* solution_file;

void wirteAnswerToFile(vector<path> path_array, FILE* file) {
    for (int i = 0; i < path_array.size(); i++) {
        fprintf(file, "%d %d\n", path_array[i].x, path_array[i].y);
    }
}

int main() {
    
    // Read Floor.data and receive all data
    ifstream BoardFile;
    string RowInfoArray[MAX_COMMEND_SIZE];
    BoardFile.open("Floor.data");
    solution_file = fopen("floor.output", "w");
    
    // using getline() to store every comment line to GameCommend
    string line;
    int currentStoreIndex = 0;
    
    if (BoardFile.is_open()) {

        while (!BoardFile.eof()) {  // read the file until EOF
            getline(BoardFile, line);
            RowInfoArray[currentStoreIndex++] = line;
        }

        BoardFile.close();
    } else {
        cout << "Cannot read Floor.data!!!" << endl;
    }
    
    int Board_row = 0, Board_column = 0, Battery = 0;
    int Multiplicand = 1;
    int matrix_coordinate_flag = 0;
    
    for (int i = 0; i < MAA_BOARD_INFO_SIZE; i++) {
        if (isdigit(RowInfoArray[0][i]) && matrix_coordinate_flag == 0) { // Board_row
            Board_row *= Multiplicand;
            Multiplicand *= 10;
            Board_row += RowInfoArray[0][i] - '0';
        } else if (isdigit(RowInfoArray[0][i]) && matrix_coordinate_flag == 1) { // Board_column
            Board_column *= Multiplicand;
            Multiplicand *= 10;
            Board_column += RowInfoArray[0][i] - '0';
        } else if (isdigit(RowInfoArray[0][i]) && matrix_coordinate_flag == 2) { // Battery
            Battery *= Multiplicand;
            Multiplicand *= 10;
            Battery += RowInfoArray[0][i] - '0';
        } else {
            Multiplicand = 1;
            matrix_coordinate_flag++;
        }
    }
    
    char** currentFloorBoard = CreateFloorBoard(Board_row, Board_column);
    
    int start_node = 0;
    int node_count = 0;
    
    for (int row = 1; row <= Board_row ; row++) {
        for (int column = 0; column < Board_column; column++) {
            if (RowInfoArray[row][column] == 'R') {
                start_node = node_count;
                currentFloorBoard[row - 1][column] = RowInfoArray[row][column];
                node_count++;
            }
            
            if (isdigit(RowInfoArray[row][column])) {
                currentFloorBoard[row - 1][column] = RowInfoArray[row][column];
                
                if (RowInfoArray[row][column] == '0')
                    node_count++;
            }
        }
    }
    
    bool isGameOver = false;
    int temp_start = start_node;
    nodeInfo* infoArray = createNodeInfoArray(currentFloorBoard, Board_row, Board_column, node_count);
    infoArray[start_node].isVisited = true;
    
    while (!isGameOver) {
        int next = -1;
        for (int i = 0; i < node_count; i++) {
            if (!infoArray[i].isVisited) {
                next = i;
                break;
            }
        }
                
        if (temp_start != start_node) {
            if (next == -1) {
                isGameOver = true;
                break;
            } else {
                MatrixGraph *temp = new MatrixGraph(temp_start, start_node, node_count, infoArray);
                nextState d = temp->ShortestPath(temp_start, node_count, infoArray);
                temp_start = start_node;
                temp->getPath(start_node, d.parent, infoArray);
            }
        } else {
            if (next == -1) {
                isGameOver = true;
                break;
            } else {
                MatrixGraph *temp = new MatrixGraph(temp_start, next, node_count, infoArray);
                nextState d = temp->ShortestPath(temp_start, node_count, infoArray);
                temp_start = next;
                infoArray[temp_start].isVisited = true;
                temp->getPath(next, d.parent, infoArray);
            }
        }
    }
    
    MatrixGraph *temp = new MatrixGraph(temp_start, start_node, node_count, infoArray);
    nextState d = temp->ShortestPath(temp_start, node_count, infoArray);
    temp->getPath(start_node, d.parent, infoArray);
    
    vector<path> result;
    result = temp->returnResult();
    unsigned long int count = result.size() + 1;
    
    fprintf(solution_file, "%lu\n", count);
    fprintf(solution_file, "%d %d\n", infoArray[start_node].x_coordinate, infoArray[start_node].y_coordinate);
    
    wirteAnswerToFile(result, solution_file);
    
    return 0;
}
