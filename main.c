#include <stdio.h>

#define SIZE 3

char board        ;

void initializeBoard() {
    int num = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board    = num + '0';
            num++;
        }
    }
}
void displayBoard() {
    putchar('\n');
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            putchar(' ');
            putchar();
            putchar(' ');
            if (j < SIZE - 1) putchar('|');
        }
        putchar('\n');
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    putchar('\n');
}

int checkWin() {
    for (int i = 0; i < SIZE; i++) {
        if ( ) return 1;
        if ( ) return 1;
    }
    if (  ) 1;
    if (  ) return 1;
    return 0;
}

int isDraw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (   ) return 0;
        }
    }
    return 1;
}

void playGame() {
    int player = 1, choice, row, col;
    char mark;

    initializeBoard();

    while (1) {
        displayBoard();
        mark = (player == 1) ? 'X' : 'O';
        printf("Player %d, enter your move (1-9): ", player);
        scanf("%d", &choice);

        row = (choice - 1) / SIZE;
        col = (choice - 1) % SIZE;

        if () {
            printf("Invalid move, try again.\n");
            continue;
        }
        
        board = mark;

        if (checkWin()) {
            displayBoard();
            printf("Player %d wins!\n", player);
            break;
        }
        
        if (isDraw()) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }
        
        player = (player == 1) ? 2 : 1;
    }
}

int main() {
    printf("Welcome to Tic Tac Toe!\n");
    playGame();
    return 0;
}
