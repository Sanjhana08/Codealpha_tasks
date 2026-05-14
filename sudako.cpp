#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

const int SIZE = 9;

int steps = 0;

// ==========================================
//          PRINT BEAUTIFUL GRID
// ==========================================
void printGrid(int grid[SIZE][SIZE]) {

    cout << "\n";
    cout << "=================================================\n";
    cout << "              AI SUDOKU SOLUTION                 \n";
    cout << "=================================================\n";

    for(int row = 0; row < SIZE; row++) {

        if(row % 3 == 0)
            cout << "-------------------------------------------------\n";

        for(int col = 0; col < SIZE; col++) {

            if(col % 3 == 0)
                cout << "| ";

            if(grid[row][col] == 0)
                cout << ". ";
            else
                cout << grid[row][col] << " ";
        }

        cout << "|\n";
    }

    cout << "-------------------------------------------------\n";
}

// ==========================================
//         CHECK SAFE PLACEMENT
// ==========================================
bool isSafe(int grid[SIZE][SIZE],
            int row,
            int col,
            int num) {

    // Row Check
    for(int x = 0; x < SIZE; x++) {

        if(grid[row][x] == num)
            return false;
    }

    // Column Check
    for(int x = 0; x < SIZE; x++) {

        if(grid[x][col] == num)
            return false;
    }

    // 3x3 Grid Check
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for(int i = 0; i < 3; i++) {

        for(int j = 0; j < 3; j++) {

            if(grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// ==========================================
//        FIND EMPTY LOCATION
// ==========================================
bool findEmpty(int grid[SIZE][SIZE],
               int &row,
               int &col) {

    for(row = 0; row < SIZE; row++) {

        for(col = 0; col < SIZE; col++) {

            if(grid[row][col] == 0)
                return true;
        }
    }

    return false;
}

// ==========================================
//         SUDOKU VALIDATION
// ==========================================
bool validateGrid(int grid[SIZE][SIZE]) {

    for(int row = 0; row < SIZE; row++) {

        for(int col = 0; col < SIZE; col++) {

            int num = grid[row][col];

            if(num != 0) {

                grid[row][col] = 0;

                if(!isSafe(grid, row, col, num)) {

                    return false;
                }

                grid[row][col] = num;
            }
        }
    }

    return true;
}

// ==========================================
//       AI BACKTRACKING SOLVER
// ==========================================
bool solveSudoku(int grid[SIZE][SIZE]) {

    int row, col;

    if(!findEmpty(grid, row, col))
        return true;

    for(int num = 1; num <= 9; num++) {

        if(isSafe(grid, row, col, num)) {

            grid[row][col] = num;

            steps++;

            // Optional animation
            system("cls");
            printGrid(grid);

            cout << "\n🤖 AI Solving...";
            cout << "\n🔄 Steps Processed : " << steps << endl;

            this_thread::sleep_for(milliseconds(20));

            if(solveSudoku(grid))
                return true;

            // Backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

// ==========================================
//          INPUT CUSTOM GRID
// ==========================================
void customInput(int grid[SIZE][SIZE]) {

    cout << "\n";
    cout << "Enter Sudoku Puzzle\n";
    cout << "(Use 0 for empty cells)\n\n";

    for(int row = 0; row < SIZE; row++) {

        for(int col = 0; col < SIZE; col++) {

            cin >> grid[row][col];
        }
    }
}

// ==========================================
//            DIFFICULTY LEVELS
// ==========================================
void loadEasy(int grid[SIZE][SIZE]) {

    int temp[SIZE][SIZE] = {

        {3,0,6,5,0,8,4,0,0},
        {5,2,0,0,0,0,0,0,0},
        {0,8,7,0,0,0,0,3,1},
        {0,0,3,0,1,0,0,8,0},
        {9,0,0,8,6,3,0,0,5},
        {0,5,0,0,9,0,6,0,0},
        {1,3,0,0,0,0,2,5,0},
        {0,0,0,0,0,0,0,7,4},
        {0,0,5,2,0,6,3,0,0}
    };

    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            grid[i][j]=temp[i][j];
}

// ==========================================
//                 MAIN
// ==========================================
int main() {

    system("color 0A");

    int grid[SIZE][SIZE];

    int choice;

    cout << "\n";
    cout << "=================================================\n";
    cout << "          🧠 AI POWERED SUDOKU SOLVER            \n";
    cout << "=================================================\n";

    cout << "\n1. Load Demo Puzzle";
    cout << "\n2. Enter Custom Puzzle";

    cout << "\n\nEnter Choice : ";
    cin >> choice;

    if(choice == 1) {

        loadEasy(grid);
    }
    else {

        customInput(grid);
    }

    cout << "\n📋 Initial Sudoku Board\n";

    printGrid(grid);

    // Validate Puzzle
    if(!validateGrid(grid)) {

        cout << "\n❌ INVALID SUDOKU INPUT!\n";
        return 0;
    }

    cout << "\n🚀 Starting AI Solver...\n";

    auto start = high_resolution_clock::now();

    bool solved = solveSudoku(grid);

    auto stop = high_resolution_clock::now();

    auto duration =
    duration_cast<milliseconds>(stop - start);

    // ==========================================
    //            FINAL OUTPUT
    // ==========================================

    if(solved) {

        system("cls");

        printGrid(grid);

        cout << "\n=========================================\n";
        cout << "          🎉 SUDOKU SOLVED!\n";
        cout << "=========================================\n";

        cout << "🤖 AI Steps Used      : "
             << steps << endl;

        cout << "⚡ Solving Time       : "
             << duration.count()
             << " ms\n";

        cout << "🧠 Algorithm Used     : Backtracking AI\n";

        cout << "📈 Success Rate       : 100%\n";

        cout << "\n🏆 Puzzle Solved Successfully!\n";
    }
    else {

        cout << "\n❌ No Solution Exists!\n";
    }

    cout << "\n=================================================\n";
    cout << "         THANK YOU FOR USING AI SOLVER           \n";
    cout << "=================================================\n";

    return 0;
}