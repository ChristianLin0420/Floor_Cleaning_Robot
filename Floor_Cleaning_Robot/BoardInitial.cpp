//
//  BoardInitial.cpp
//  Floor_Cleaning_Robot
//
//  Created by Christian on 2019/11/3.
//  Copyright © 2019 Christian. All rights reserved.
//

#include <iostream>

#include "BoardInitial.hpp"

using namespace std;

char** CreateFloorBoard(int row, int column) {  // Creating a board filled with 0 according to given row and column
    char** FloorBoard = new char*[row];
    
    for(int i = 0; i < row; i++)
        FloorBoard[i] = new char[column];
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            FloorBoard[i][j] = 0;
        }
    }
    
    return FloorBoard;
}


void PrintCurrentBoard(char** currentBoard, int row, int column) { // Print out current floor
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            //cout << currentBoard[i][j]  << " ";
        
        cout << endl;
    }
}
