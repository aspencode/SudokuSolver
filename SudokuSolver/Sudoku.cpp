#include "Sudoku.h"

Sudoku::Sudoku()
{

    grid =
    { { {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0}	} };

}

Sudoku::Sudoku(const std::string& sciezka)
{
    std::ifstream inputFile(sciezka);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return; // Exit
    }

    std::string line;
    int lineNr = 0;

    while (std::getline(inputFile, line))
    {
        for (int i = 0; i < line.size(); i++) {

            grid[lineNr][i] = line[i] - '0';
        }
        //std::cout << line <<"\t"<<lineNr<<'\n';
        lineNr++;
    }
}

Sudoku::Sudoku(const Grid& _grid) : grid(_grid)
{
}

bool Sudoku::readFromFile(const std::string& sciezka)
{
    std::ifstream inputFile(sciezka);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return false; // Exit with an error code
    }

    std::string line;
    int lineNr = 0;

    while (std::getline(inputFile, line))
    {
        for (int i = 0; i < line.size(); i++) {

            grid[lineNr][i] = line[i] - '0';
        }
        //std::cout << line <<"\t"<<lineNr<<'\n';
        lineNr++;
    }
    return true;
}

void Sudoku::printOutTheGrid()
{
    
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            std::cout << grid[x][y];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    
}

bool Sudoku::boxContainsNumber(short x, short y, short number)
{
    int xBox = (x / 3) * 3; //top of box
    int yBox = (y / 3) * 3; // left of box
    for (int a = 0; a <= 2; a++) {
        for (int b = 0; b <= 2; b++) {
            if (grid[xBox + a][yBox + b] == number) return true;
        }
    }
    return false;
}

bool Sudoku::rowContainsNumber(short row, short number)
{
    for (int col = 0; col <= 8; col++) {
        if (grid[row][col] == number) return true;
    }
    return false;
}

bool Sudoku::colContainsNumber(short col, short number)
{
    for (int row = 0; row <= 8; row++) {
        if (grid[row][col] == number) return true;
    }
    return false;
}

bool Sudoku::isPossible(short x, short y, short number)
{
    if (number == 0) return true;
    if (grid[x][y] == number) return true;
    // Checking columns and rows
    for (short i = 0; i < 9; i++) {
        if (grid[x][i] == number || grid[i][y] == number) return false;
    }
    // Checking the box it's in

    if (boxContainsNumber(x, y, number)) return false;

    return true;
}


void Sudoku::BackTrackSolve()
{
    for (short x = 0; x < 9; x++) {
        for (short y = 0; y < 9; y++) {
            if (grid[x][y] == 0) {
                for (short n = 1; n <= 9; n++) {  // numbers from 1 to 9, 0 is empty
                    if (isPossible(x, y, n)) {
                        grid[x][y] = n;
                        BackTrackSolve();
                        grid[x][y] = 0;
                    }
                }
                return;
            }
        }
    }
    solutions++;
    printOutTheGrid();
}


