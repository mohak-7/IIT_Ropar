#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>

#define PLAYER 'X'
#define COMPUTER 'O'

char board[3][3];
int cursorX = 0, cursorY = 0;

void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard() {
    system("clear");
    printf("\n\nUse arrow keys to move between the cells. Enter to select the cell.   \n\n");
	printf(" ---  OR  ---  if you want to quit, use the   q  (Letter Q) key to Quit........\n\n\n\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == cursorY && j == cursorX)
                printf("[ %c ]", board[i][j]);
            else
                printf("  %c  ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf(" ----+-----+----\n");
    }
}

int checkWin(char player) {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
    for (int i = 0; i < 3; i++)
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;
    return 0;
}

int isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void computerMove() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                if (checkWin(COMPUTER))
                    return;
                board[i][j] = ' ';
            }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = PLAYER;
                if (checkWin(PLAYER)) {
                    board[i][j] = COMPUTER;
                    return;
                }
                board[i][j] = ' ';
            }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                return;
            }
}

void readInput() {
    char ch;
    while (1) {
        ch = getchar(); 
		
		if (ch == 'q') { exit(0);} // Exit the program if 'q' is pressed.
        else if (ch == -32) {
            switch (getchar()) {
                case 72: cursorY = (cursorY + 2) % 3; break; // Up
                case 80: cursorY = (cursorY + 1) % 3; break; // Down
                case 77: cursorX = (cursorX + 1) % 3; break; // Right
                case 75: cursorX = (cursorX + 2) % 3; break; // Left
            }
        } else if (ch == '\r') {
            if (board[cursorY][cursorX] == ' ') {
                board[cursorY][cursorX] = PLAYER;
                break;
            }
        }
        printBoard();
    }
}

int main() {
    initializeBoard();
    printBoard();

    while (1) {
        readInput();
        printBoard();
        if (checkWin(PLAYER)) {
            printf("You win!\n");
            break;
        }
        computerMove();
        printBoard();
        if (checkWin(COMPUTER)) {
            printf("Computer wins!\n");
            break;
        }
        if (isBoardFull()) {
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}
