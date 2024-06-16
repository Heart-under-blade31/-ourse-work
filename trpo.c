#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 4

void initializeBoard(int board[SIZE][SIZE]) {
    int numbers[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        numbers[i] = i;
    }

    srand(time(0));
    for (int i = SIZE * SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = numbers[index++];
        }
    }
}

void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("   ");
            } else {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
    }
}

void findEmpty(int board[SIZE][SIZE], int *x, int *y) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

bool moveTile(int board[SIZE][SIZE], int x, int y) {
    int emptyX, emptyY;
    findEmpty(board, &emptyX, &emptyY);

    if ((abs(emptyX - x) == 1 && emptyY == y) || (abs(emptyY - y) == 1 && emptyX == x)) {
        board[emptyX][emptyY] = board[x][y];
        board[x][y] = 0;
        return true;
    }
    return false;
}

bool isSolved(int board[SIZE][SIZE]) {
    int correctValue = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1) {
                return board[i][j] == 0;
            }
            if (board[i][j] != correctValue++) {
                return false;
            }
        }
    }
    return true;
}

bool isSolvable(int board[SIZE][SIZE]) {
    int inversions = 0;
    int flatBoard[SIZE * SIZE];
    int k = 0;
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            flatBoard[k++] = board[i][j];
        }
    }

    for (int i = 0; i < SIZE * SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE * SIZE; j++) {
            if (flatBoard[i] && flatBoard[j] && flatBoard[i] > flatBoard[j]) {
                inversions++;
            }
        }
    }

    int emptyRow;
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] == 0) {
                emptyRow = SIZE - i;
                break;
            }
        }
    }

    if (SIZE % 2 == 1) {
        return inversions % 2 == 0;
    } else {
        return inversions % 2 == 0 && emptyRow % 2 != 0;
        return inversions % 2 != 0 && emptyRow % 2 == 0;
    }
}

void shuffleBoard(int board[SIZE][SIZE]) {
    do {
        initializeBoard(board);
    } while (!isSolvable(board));
}

int main() {
    int board[SIZE][SIZE];
    shuffleBoard(board);

    while (!isSolved(board)) {
        printBoard(board);

        int x, y;
        printf("Введите координаты плитки для перемещения (строка и столбец): ");
        scanf("%d %d", &x, &y);

        if (x >= 1 && x <= SIZE && y >= 1 && y <= SIZE) {
            if (!moveTile(board, x - 1, y - 1)) {
                printf("Недопустимый ход! Попробуйте снова.\n");
            }
        } else {
            printf("Недопустимые координаты! Попробуйте снова.\n");
        }
    }

    printBoard(board);
    printf("Поздравляю! Вы решили пятнашки!\n");
    return 0;
}
