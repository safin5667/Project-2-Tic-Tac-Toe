#include <stdio.h>

#define SIZE 3

char board[SIZE][SIZE]; 

void initializeBoard()
{
    int num = 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = num + '0';
            num++;
        }
    }
}

void displayBoard()
{
    putchar('\n');
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1)
                printf("|");
        }
        putchar('\n');
        if (i < SIZE - 1)
            printf("---|---|---\n");
    }
    putchar('\n');
}

int checkWin()
{
    // Check rows and columns
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;
}

int isDraw()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
        }
    }
    return 1;
}

void playGame()
{
    int player = 1, choice, row, col;
    char mark;

    initializeBoard();

    while (1)
    {
        displayBoard();
        mark = (player == 1) ? 'X' : 'O';
        printf("Player %d, enter your move (1-9): ", player);
        scanf("%d", &choice);

        if (choice < 1 || choice > 9)
        {
            printf("Invalid input, try again.\n");
            continue;
        }

        row = (choice - 1) / SIZE;
        col = (choice - 1) % SIZE;

        if (board[row][col] == 'X' || board[row][col] == 'O')
        {
            printf("Cell already taken, try again.\n");
            continue;
        }

        board[row][col] = mark;

        if (checkWin())
        {
            displayBoard();
            printf("Player %d wins! 🎉\n", player);
            break;
        }

        if (isDraw())
        {
            displayBoard();
            printf("It's a draw! 🤝\n");
            break;
        }

        player = (player == 1) ? 2 : 1;
    }
}

int main()
{
    printf("🎮 Welcome to Tic Tac Toe! 🎮\n");
    playGame();
    return 0;
}
