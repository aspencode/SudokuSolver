#include "Sudoku.h"

std::vector<Sudoku> readMultipleSudokusFromFile(const std::string& path)
{
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return {};
    }

    std::vector<Sudoku> sudokuList;
    std::string puzzleString;

    while (inputFile >> puzzleString) {
        if (puzzleString.size() != 81) {
            std::cerr << "Warning: Skipping puzzle due to incorrect size ("
                << puzzleString.size() << " characters).\n";
            continue;
        }

        Grid grid;
        bool valid = true;

        for (size_t i = 0; i < 81; ++i) {
            if (!isdigit(puzzleString[i])) {
                std::cerr << "Warning: Skipping puzzle due to non-digit character.\n";
                valid = false;
                break;
            }
            grid[i / 9][i % 9] = puzzleString[i] - '0';
        }

        if (valid) {
            sudokuList.emplace_back(grid);
        }
    }

    return sudokuList;
}


int main() {


    Grid grid =
    { { {2, 1, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0},
     {0, 0, 0, 0, 0, 0, 0, 0 ,0}	} };

	Sudoku sudoku(grid);
	sudoku.printOutTheGrid();
	if (sudoku.isGridCorrect())
	{
		std::cout << "Grid is correct\n";
	}
	else
	{
		std::cout << "Grid is NOT correct\n";
	}

	return 0;
}