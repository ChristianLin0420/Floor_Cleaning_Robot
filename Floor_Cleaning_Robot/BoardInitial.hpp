//
//  BoardInitial.hpp
//  Floor_Cleaning_Robot
//
//  Created by Christian on 2019/11/3.
//  Copyright © 2019 Christian. All rights reserved.
//

#ifndef BoardInitial_hpp
#define BoardInitial_hpp

#include <stdio.h>

char** CreateFloorBoard(int row, int column); // Creating a board filled with 0 according to given row and column
void PrintCurrentBoard(char** currentBoard, int row, int column); // Print out current floor 
#endif /* BoardInitial_hpp */
