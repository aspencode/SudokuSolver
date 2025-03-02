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

Sudoku::Sudoku(const Grid& _grid)
{
}
