#include <stdio.h>

int flag = 0;

int checkForBlock(int (*table)[9], int blockY, int blockX, int checkY, int checkX) {
    int startRow = blockY - blockY % 3;
    int startCol = blockX - blockX % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int row = startRow + i;
            int col = startCol + j;
            if (!(row == checkY && col == checkX) && table[row][col] == table[checkY][checkX]) {
                return 0;
            }
        }
    }
    return 1;
}

int checkCell(int (*table)[9], int checkY, int checkX) {
    for (int k = 0; k < 9; k++) {
        if ((table[checkY][k] == table[checkY][checkX] && k != checkX) || (table[k][checkX] == table[checkY][checkX] && k != checkY)) {
            return 0;
        }
    }

    if (!checkForBlock(table, checkY, checkX, checkY, checkX)) {
        return 0;
    }

    return 1;
}

void solveSudoku(int (*table)[9], int checkY, int checkX) {
    if (checkY == 9) {
        flag = 1;
        return;
    }

    if (table[checkY][checkX] == 0) {
        for (int j = 1; j <= 9; j++) {
            if (flag == 1) {
                return;
            }
            table[checkY][checkX] = j;
            if (checkCell(table, checkY, checkX)) {
                if (checkX == 8) {
                    solveSudoku(table, checkY + 1, 0);
                } else {
                    solveSudoku(table, checkY, checkX + 1);
                }
                if (flag != 1) {
                    table[checkY][checkX] = 0;
                }
            } else {
                table[checkY][checkX] = 0;
            }
        }
        return;
    } else {
        if (checkX == 8) {
            solveSudoku(table, checkY + 1, 0);
        } else {
            solveSudoku(table, checkY, checkX + 1);
        }
    }
}

int main() 
{
    int sudokuGrid[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    solveSudoku(sudokuGrid, 0, 0);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", sudokuGrid[i][j]);
        }
        printf("\n");
    }
    return 0;
}