#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>


    /* --- Grid and possibilities ---*/
    
    // 0 means the cell is empty, number from 1 to 9 means that the number is there

    // possibilities is a 9x9xN grid which holds possible numbers for each cell, 
    // it's like pencil marks in regular sudoku

    // the grid is.. the grid. 
    // Y is columns from left to right and X is rows from top to bottom. 
    // its from 0 to 8
    // so top right would be [0][8]

using Grid = std::array<std::array<short, 9>, 9>;
class Sudoku
{
private:
    std::array<std::array<std::vector<short>, 9>, 9> possibilities;
    Grid grid;
    int solutions = 0;
public:

    /* CONSTRUNTORS */
    Sudoku(); // empty Grid (filled with 0s)

    Sudoku(const std::string& sciezka);

    Sudoku(const Grid& _grid);
};