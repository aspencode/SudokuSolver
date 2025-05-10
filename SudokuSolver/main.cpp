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

	Sudoku sudoku;
 //   sudoku.initializeFromUserInput();
	//sudoku.printOutTheGrid();
	//sudoku.saveToFile();

	sudoku.readFromFile("1746897797.txt", true);
    sudoku.printOutTheGrid();
	return 0;
}