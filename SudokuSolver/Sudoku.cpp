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

void Sudoku::hiddenSingleInBox(short x, short y)
{
    // Checking the box it's in
    int xBox = (x / 3) * 3; //top of box
    int yBox = (y / 3) * 3; // left of box

    int xLocation;
    int yLocation;
    int iLocation;
    short cnt = 0;
    for (short number = 1; number < 10; number++) {
        cnt = 0;
        for (int b = 0;b <= 2;b++) {
            for (int a = 0;a <= 2;a++) {
                int size = possibilities[xBox + b][yBox + a].size();
                if (size != 0) {
                    for (int i = 0; i < size; i++) //iterate through pencil marks
                    {

                        if (possibilities[xBox + b][yBox + a][i] == number) //if it has the number, save its location and up cnt
                        {
                            xLocation = xBox + b;
                            yLocation = yBox + a;
                            iLocation = i;
                            cnt++;
                        }


                    }
                }

            }
        }
        if (cnt == 1) // if there is a hidden single (only found 1 pencil mark in box)
        {
            insertNumber(xLocation, yLocation, number);
            cnt = 0;

        }
    }

}

void Sudoku::hiddenSingleInCol(short y)
{
    int xLocation, iLocation;
    for (int number = 1;number <= 9;number++) {
        short cnt = 0;
        for (int x = 0; x <= 8; x++) {
            int size = possibilities[x][y].size();
            for (int i = 0; i < size; i++) //iterate through pencil marks
            {
                if (possibilities[x][y].size() != 0) {
                    if (possibilities[x][y][i] == number) //if it has the number, save its location and up cnt
                    {
                        xLocation = x;
                        iLocation = i;
                        cnt++;
                    }
                }

            }
        }
        if (cnt == 1) {
            insertNumber(xLocation, y, number);
        }
    }
}

void Sudoku::hiddenSingleInRow(short x)
{
    int yLocation, iLocation;
    for (int number = 1; number <= 9; number++) {
        short cnt = 0;
        for (int y = 0; y <= 8; y++) {
            int size = possibilities[x][y].size();
            if (size != 0) {
                for (int i = 0; i < size; i++) //iterate through pencil marks
                {

                    if (possibilities[x][y][i] == number) //if it has the number, save its location and up cnt
                    {

                        yLocation = y;
                        iLocation = i;
                        cnt++;
                    }


                }
            }
        }
        if (cnt == 1) {
            insertNumber(x, yLocation, number);
        }
    }
}

void Sudoku::findAllHiddenSingles()
{
    for (int a = 0; a <= 6; a = a + 3) {
        hiddenSingleInBox(a, 0);
        hiddenSingleInBox(a, 3);
        hiddenSingleInBox(a, 6);
    }
    //clearPossibilities(); findHints();
    for (int a = 0; a <= 8; a++) {
        hiddenSingleInRow(a);
    }
    //clearPossibilities(); findHints();
    for (int a = 0; a <= 8; a++) {
        hiddenSingleInCol(a);
    }
    //clearPossibilities(); findHints();


}

void Sudoku::hiddenPairInBox(short x, short y)
{
    int num1Counter, num2Counter;
    int num1Loc1X{ -1 }, num1Loc1Y{ -1 }, num1Loc2X{ -1 }, num1Loc2Y{ -1 };
    int num2Loc1X{ -1 }, num2Loc1Y{ -1 }, num2Loc2X{ -1 }, num2Loc2Y{ -1 };

    int xBox = (x / 3) * 3; //top of box
    int yBox = (y / 3) * 3; // left of box
    for (short num1 = 1; num1 <= 9; num1++) {
        for (short num2 = 1; num2 <= 9; num2++) {

            if (num2 != num1 and boxContainsNumber(x, y, num1) == 0 and boxContainsNumber(x, y, num2) == 0) {
                num1Counter = 0; num2Counter = 0;
                num1Loc1X = -1; num1Loc1Y = -1; num1Loc2X = -1; num1Loc2Y = -1;
                num2Loc1X = -1; num2Loc1Y = -1; num2Loc2X = -1; num2Loc2Y = -1;
                for (int b = 0; b <= 2; b++) {
                    for (int a = 0; a <= 2; a++) {
                        int size = possibilities[xBox + b][yBox + a].size();
                        if (size != 0) {
                            for (int i = 0; i < size; i++) //iterate through pencil marks
                            {
                                if (possibilities[xBox + b][yBox + a][i] == num1) {
                                    num1Counter++;
                                    if (num1Counter == 1) {
                                        num1Loc1X = xBox + b;
                                        num1Loc1Y = yBox + a;
                                    }
                                    else if (num1Counter == 2) {
                                        num1Loc2X = xBox + b;
                                        num1Loc2Y = yBox + a;
                                    }
                                }
                                if (possibilities[xBox + b][yBox + a][i] == num2) {

                                    num2Counter++;
                                    if (num2Counter == 1) {
                                        num2Loc1X = xBox + b;
                                        num2Loc1Y = yBox + a;
                                    }
                                    else if (num2Counter == 2) {
                                        num2Loc2X = xBox + b;
                                        num2Loc2Y = yBox + a;
                                    }
                                }
                            }
                        }
                    }
                }
                if (num1Counter == 2 and num2Counter == 2) {
                    if (num1Loc1X == num2Loc1X and num1Loc1Y == num2Loc1Y and num1Loc2X == num2Loc2X and num1Loc2Y == num2Loc2Y) {
                        // found hidden pair
                        possibilities[num1Loc1X][num1Loc1Y] = { num1, num2 };
                        possibilities[num2Loc2X][num2Loc2Y] = { num1, num2 };
                    }
                }
            }
        }
    }
}

void Sudoku::hiddenPairInCol(short y)
{
    int num1Counter, num2Counter;
    int num1Loc1X{ -1 }, num1Loc2X{ -1 };
    int num2Loc1X{ -1 }, num2Loc2X{ -1 };
    for (short num1 = 1; num1 <= 9; num1++) {
        for (short num2 = 1; num2 <= 9; num2++) {
            if (num1 != num2) {
                num1Counter = 0; num2Counter = 0;
                num1Loc1X = -1;  num1Loc2X = -1;
                num2Loc1X = -1;  num2Loc2X = -1;
                for (int x = 0; x <= 8; x++) { //iterate column
                    int size = possibilities[x][y].size();
                    if (size != 0) {
                        for (int i = 0; i < size; i++) //iterate through pencil marks
                        {
                            if (possibilities[x][y][i] == num1) {
                                num1Counter++;
                                if (num1Counter == 1)
                                    num1Loc1X = x;
                                else if (num1Counter == 2)
                                    num1Loc2X = x;


                            }
                            if (possibilities[x][y][i] == num2) {
                                num2Counter++;
                                if (num2Counter == 1)
                                    num2Loc1X = x;
                                else if (num2Counter == 2)
                                    num2Loc2X = x;


                            }
                        }
                    }
                }

                if (num1Counter == 2 and num2Counter == 2) {
                    if (num1Loc1X == num2Loc1X and num1Loc2X == num2Loc2X) {
                        // found hidden pair
                        possibilities[num1Loc1X][y] = { num1, num2 };
                        possibilities[num2Loc2X][y] = { num1, num2 };
                    }
                }
            }

        }
    }
}

void Sudoku::hiddenPairInRow(short x)
{
    int num1Counter, num2Counter;
    int num1Loc1Y{ -1 }, num1Loc2Y{ -1 };
    int num2Loc1Y{ -1 }, num2Loc2Y{ -1 };
    for (short num1 = 1; num1 <= 9; num1++) {
        for (short num2 = 1; num2 <= 9; num2++) {
            if (num1 != num2) {
                num1Counter = 0; num2Counter = 0;
                num1Loc1Y = -1;  num1Loc2Y = -1;
                num2Loc1Y = -1;  num2Loc2Y = -1;
                for (int y = 0; y <= 8; y++) { //iterate row
                    int size = possibilities[x][y].size();
                    if (size != 0) {
                        for (int i = 0; i < size; i++) //iterate through pencil marks
                        {
                            if (possibilities[x][y][i] == num1) {
                                num1Counter++;
                                if (num1Counter == 1)
                                    num1Loc1Y = y;
                                else if (num1Counter == 2)
                                    num1Loc2Y = y;


                            }
                            if (possibilities[x][y][i] == num2) {
                                num2Counter++;
                                if (num2Counter == 1)
                                    num2Loc1Y = y;
                                else if (num2Counter == 2)
                                    num2Loc2Y = y;


                            }
                        }
                    }
                }

                if (num1Counter == 2 and num2Counter == 2) {
                    if (num1Loc1Y == num2Loc1Y and num1Loc2Y == num2Loc2Y) {
                        // found hidden pair
                        possibilities[x][num1Loc1Y] = { num1, num2 };
                        possibilities[x][num2Loc2Y] = { num1, num2 };
                    }
                }
            }

        }
    }
}

void Sudoku::findAllHiddenPairs()
{
    for (int a = 0; a <= 6; a = a + 3) {
        hiddenPairInBox(a, 0);
        hiddenPairInBox(a, 3);
        hiddenPairInBox(a, 6);
    }

    for (int a = 0; a <= 8; a++) {
        hiddenPairInRow(a);
    }

    for (int a = 0; a <= 8; a++) {
        hiddenPairInCol(a);
    }

}

void Sudoku::xWing() {
    // iterate through all pairs of rows
    for (short h1 = 0; h1 < 9; ++h1) {
        for (short h2 = h1 + 1; h2 < 9; ++h2) {
            // iterate through all pairs of columns
            for (short v1 = 0; v1 < 9; ++v1) {
                for (short v2 = v1 + 1; v2 < 9; ++v2) {

                    // check if the corners of the rectangle have any pencil marks
                    if (possibilities[h1][v1].size() > 0 and possibilities[h1][v2].size() > 0 and
                        possibilities[h2][v1].size() > 0 and possibilities[h2][v2].size() > 0) {

                        // find common candidates (pencil marks) in the four corners
                        std::vector<short> candidates;
                        for (short val : possibilities[h1][v1]) { //iterate over possibilities for [h1][v1]
                            if (cellContains(possibilities[h1][v2], val) and
                                cellContains(possibilities[h2][v1], val) and
                                cellContains(possibilities[h2][v2], val))
                            {

                                candidates.push_back(val);
                            }
                        }

                        // process each candidate to see if it satisfies the X-Wing condition
                        for (short candidate : candidates) {
                            bool validXWing = true;

                            // check how many times candidate appears in h1 and h2
                            short count_h1 = 0, count_h2 = 0;
                            for (short col = 0; col < 9; ++col) {
                                if (std::find(possibilities[h1][col].begin(), possibilities[h1][col].end(), candidate) != possibilities[h1][col].end())
                                    ++count_h1;
                                if (std::find(possibilities[h2][col].begin(), possibilities[h2][col].end(), candidate) != possibilities[h2][col].end())
                                    ++count_h2;
                            }

                            // we good if its exactly two times in both
                            if (count_h1 != 2 or count_h2 != 2)
                                validXWing = false;


                            // if valid X-Wing, eliminate the candidate from other cells in columns v1 and v2
                            if (validXWing) {
                                for (short row = 0; row < 9; ++row) {
                                    if (row != h1 and row != h2) {
                                        // Remove the candidate from columns 
                                        possibilities[row][v1].erase(std::remove(possibilities[row][v1].begin(), possibilities[row][v1].end(), candidate), possibilities[row][v1].end());
                                        possibilities[row][v2].erase(std::remove(possibilities[row][v2].begin(), possibilities[row][v2].end(), candidate), possibilities[row][v2].end());
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}