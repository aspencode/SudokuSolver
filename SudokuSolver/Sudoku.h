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

    bool cellContains(const std::vector<short>& cell, short num);
    bool boxContainsNumber(short x, short y, short number); 
    bool rowContainsNumber(short row, short number); 
    bool colContainsNumber(short col, short number); 

    bool isPossible(short x, short y, short number);  //checks if a number in col y, row x is possible to be put there

    bool isValidPlacement(const Grid& tempGrid, int row, int col, int num); 

    void removePossibility(int x, int y, short number);


public:

    /* CONSTRUNTORS */
    Sudoku(); // empty Grid (filled with 0s)
    Sudoku(const std::string& sciezka); 
    Sudoku(const Grid& _grid); 

	// TO-DO reading from file checks if puzzle is solvable/correct

    /**/

    bool readFromFile(const std::string& sciezka);
    void printOutTheGrid();

    /* user input */

    void initializeFromUserInput();
    void insertNumberFromUserInput();
    void insertPencilMarkFromUserInput();

    /**/
    void BackTrackSolve();

    int getSolutions();

    /* possibilities */
    void findHints();
    void clearPossibilities();
    void printPossibilities();

    bool basicHintSolve(int max_steps);

    /**/

    bool insertNumber(short x, short y, short number);

    /* HIDDEN SINGLES */

    void hiddenSingleInBox(short x, short y); //needs x,y of any cell that is in that box
    void hiddenSingleInCol(short y); // needs column number (0-8)
    void hiddenSingleInRow(short x); // needs row number (0-8)
    void findAllHiddenSingles();
    
    /* HIDDEN PAIRS */

    void hiddenPairInBox(short x, short y); //needs x,y of any cell that is in that box
    void hiddenPairInCol(short y);
    void hiddenPairInRow(short x);
    void findAllHiddenPairs();

    /* xWing */
    
    void xWing();

    /* POINTING TRIPLES */

    bool pointingTriplesInRow(short x);
    bool pointingTriplesInCol(short y);
    bool findAllPointingTriples();

    /* POINTING DOUBLES */

    bool pointingDoublesInRow(short x);
    bool pointingDoublesInCol(short y);
    bool findAllPointingDoubles();

};