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
    std::cout << "    1 2 3   4 5 6   7 8 9\n"; // column numbers
    std::cout << "  +-------+-------+-------+\n";

    for (int x = 0; x < 9; x++) {
        std::cout << x + 1 << " | ";  // row number

        for (int y = 0; y < 9; y++) {
            if (grid[x][y] == 0)
                std::cout << "  ";  // if 0 in grid, print out "  " 
            else
                std::cout << grid[x][y] << " ";

            // box seperators vertical
            if (y == 2 || y == 5)
                std::cout << "| ";
        }
        std::cout << "|\n";
        if (x == 2 || x == 5) // box separators horizontal
            std::cout << "  +-------+-------+-------+\n";
    }

    std::cout << "  +-------+-------+-------+\n";
}


bool Sudoku::cellContains(const std::vector<short>& cell, short num)
{
    if (cell.empty()) return false;
    return std::find(cell.begin(), cell.end(), num) != cell.end();

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

bool Sudoku::isValidPlacement(const Grid& tempGrid, int row, int col, int num) {
    // Check the row
    for (int i = 0; i < 9; ++i) {
        if (tempGrid[row][i] == num) return false;
    }

    // Check the column
    for (int i = 0; i < 9; ++i) {
        if (tempGrid[i][col] == num) return false;
    }

    // Check the 3x3 box
    int boxRowStart = (row / 3) * 3;
    int boxColStart = (col / 3) * 3;
    for (int r = boxRowStart; r < boxRowStart + 3; ++r) {
        for (int c = boxColStart; c < boxColStart + 3; ++c) {
            if (tempGrid[r][c] == num) return false;
        }
    }

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


void Sudoku::findHints()
{

    for (short x = 0;x < 9;x++) { //for every row
        for (short y = 0; y < 9; y++) { //for every column
            for (short num = 1; num < 10; ++num) { //for every number (1,2,3,...,9)
                if (grid[x][y] != 0) break; //if there is already a number in, break
                if (isPossible(x, y, num) and !cellContains(possibilities[x][y], num)) {
                    possibilities[x][y].push_back(num); //put all possibilities in

                }
            }
        }
    }

}

void Sudoku::clearPossibilities()
{
    short size;
    for (int x = 0; x < 9; ++x) { //resetting the possibility array
        for (int y = 0; y < 9; ++y) {
            size = possibilities[x][y].size();
            if (size != 0)
                for (int i = 0; i < size; i++)
                    possibilities[x][y].pop_back();
        }
    }
}

void Sudoku::printPossibilities() {
    std::cout << "    ----1---- ----2---- ----3----   ----4---- ----5---- ----6----   ----7---- ----8---- ----9----\n";
    std::cout << "  +-------------------------------+-------------------------------+-------------------------------+\n";
    for (int x = 0; x < 9; ++x) {
        std::cout << 1 + x << " "; // row nr signifier
        for (int y = 0; y < 9; ++y) {
            if (y % 3 == 0) std::cout << "| "; // box separators
            const auto& cell = possibilities[x][y];
            std::string display(9, ' '); // "         " (9 spaces)
            if (cell.empty()) {
                std::fill(display.begin(), display.end(), ' '); // fill display with just 9 spaces
            }
            else {
                for (int val : cell) {
                    display[val - 1] = val + '0'; // display is (0,8) and cells have numbers (1-9) so -1
                }
            }
            std::cout << display << " ";
        }
        std::cout << "|\n";
        if (x < 8) {
            if (x % 3 == 2)
                std::cout << "  +-------------------------------+-------------------------------+-------------------------------+\n";
            else
                std::cout << "  |-------------------------------|-------------------------------|-------------------------------|\n";
        }
    }
    std::cout << "  +-------------------------------+-------------------------------+-------------------------------+\n";
}

bool Sudoku::basicHintSolve(int max_steps)
{
    short size;
    short changes;
    bool solved = false;
    for (int k = 0;k <= max_steps;k++) {
        changes = 0; // czy w iteracji byla jakas zmiana
        findHints();
        //printPossibilities();
        //std::cout << "\n-----------------------\n";
        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) {
                size = possibilities[x][y].size();
                if (size == 1) { //only one possibility for a square
                    grid[x][y] = possibilities[x][y][0]; //put it in the grid
                    changes++;
                }
            }
        }

        if (changes == 0) { solved = true; break; }

        clearPossibilities();
    }

    return solved;
}

bool Sudoku::insertNumber(short x, short y, short number)
{
    if (number == 0) { grid[x][y] = number; return true; }
    if (!isPossible(x, y, number)) return false;
    grid[x][y] = number;
    possibilities[x][y] = {};
    // remove hints in row
    for (int y_ = 0; y_ <= 8; y_++) {
        int index{ -1 };
        int size = possibilities[x][y_].size();
        if (size != 0) {
            for (int i = 0; i < size; i++) //iterate through pencil marks
            {
                if (possibilities[x][y_][i] == number) //if it has the number, remove it
                {
                    possibilities[x][y_].erase(possibilities[x][y_].begin() + i); break;
                }
            }
        }

    }
    //remove hints in column
    for (int x_ = 0; x_ <= 8; x_++) {
        int index{ -1 };
        int size = possibilities[x_][y].size();
        if (size != 0) {
            for (int i = 0; i < size; i++) //iterate through pencil marks
            {
                if (possibilities[x_][y][i] == number) //if it has the number, remove it
                {
                    possibilities[x_][y].erase(possibilities[x_][y].begin() + i); break;
                }
            }
        }
    }
    // remove hints in box
    int xBox = (x / 3) * 3; //top of box
    int yBox = (y / 3) * 3; // left of box

    for (int b = 0; b <= 2; b++) {
        for (int a = 0; a <= 2; a++) {
            int size = possibilities[xBox + b][yBox + a].size();
            if (size != 0) {
                for (int i = 0; i < size; i++) //iterate through pencil marks
                {
                    if (possibilities[xBox + b][yBox + a][i] == number) //if it has the number, remove it
                    {
                        possibilities[xBox + b][yBox + a].erase(possibilities[xBox + b][yBox + a].begin() + i); break;
                    }
                }
            }
        }
    }
    return true;

}

void Sudoku::initializeFromUserInput()
{
    std::cout << "Enter your Sudoku puzzle row by row (use '0' for empty cells):\n";
    Grid tempGrid = {}; // temporary grid for input validation

    for (int row = 0; row < 9; ++row) {
        std::string inputRow;
        bool validRow = false;

        while (!validRow) {
            std::cout << "Row " << row + 1 << ": ";
            std::cin >> inputRow;

            // check if the input has exactly 9 characters
            if (inputRow.length() != 9) {
                std::cout << "Invalid input. Each row must have exactly 9 digits. Try again.\n";
                continue;
            }

            // check if all characters are digits
            bool allDigits = true;
            for (char c : inputRow) {
                if (!isdigit(c)) {
                    allDigits = false;
                    break;
                }
            }
            if (!allDigits) {
                std::cout << "Invalid input. Only digits (0-9) are allowed. Try again.\n";
                continue;
            }

            // check for validity of the row within the Sudoku rules
            bool validPlacement = true;
            for (int col = 0; col <= 8; ++col) {
                int num = inputRow[col] - '0'; // convert from char to number
                if (num != 0 and !isValidPlacement(tempGrid, row, col, num)) {
                    std::cout << "Invalid Sudoku. The number " << num << " conflicts with row, column, or box rules. Try again.\n";
                    validPlacement = false;
                    break;
                }
                tempGrid[row][col] = num; // temporarily place the number for validation
            }

            if (validPlacement) validRow = true;
        }
    }

    grid = tempGrid;
    clearPossibilities();
    std::cout << "Sudoku grid initialized successfully.\n";
    printOutTheGrid();
}