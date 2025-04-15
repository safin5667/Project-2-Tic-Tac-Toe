#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 3

char board[SIZE][SIZE];

void clearScreen()
{
    system("clear"); // use "cls" for Windows
}

void printColor(const char *text, const char *colorCode)
{
    printf("%s%s\033[0m", colorCode, text);
}

void initializeBoard()
{
    int num = 1;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = num++ + '0';
}

void displayBoard()
{
    printf("\n   \033[1;37m    Tic Tac Toe Arena 🎮\033[0m\n\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("     ");
        for (int j = 0; j < SIZE; j++)
        {
            char mark = board[i][j];
            if (mark == 'X')
                printColor(" X ", "\033[1;31m");
            else if (mark == 'O')
                printColor(" O ", "\033[1;34m");
            else
            {
                char buf[4] = {' ', mark, ' ', '\0'};
                printColor(buf, "\033[1;33m");
            }

            if (j < SIZE - 1)
                printf("\033[1;37m│");
        }
        printf("\n");
        if (i < SIZE - 1)
            printf("     ───┼───┼───\n");
    }
    printf("\n");
}

int checkWin()
{
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;
    return 0;
}

int isDraw()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return 1;
}

void intro()
{
    clearScreen();
    srand(time(0));
    printf("\033[1;35m");
    printf("████████╗██╗ ██████╗      ████████╗ █████╗  ██████╗     ████████╗ ██████╗ ███████╗\n");
    printf("╚══██╔══╝██║██╔════╝      ╚══██╔══╝██╔══██╗██╔════╝     ╚══██╔══╝██╔═══██╗██╔════╝\n");
    printf("   ██║   ██║██║  ███╗        ██║   ███████║██║  ███╗       ██║   ██║   ██║█████╗  \n");
    printf("   ██║   ██║██║   ██║        ██║   ██╔══██║██║   ██║       ██║   ██║   ██║██╔══╝  \n");
    printf("   ██║   ██║╚██████╔╝        ██║   ██║  ██║╚██████╔╝       ██║   ╚██████╔╝███████╗\n");
    printf("   ╚═╝   ╚═╝ ╚═════╝         ╚═╝   ╚═╝  ╚═╝ ╚═════╝        ╚═╝    ╚═════╝ ╚══════╝\n");
    printf("\033[0m\n");

    const char *quotes[] = {
        "Think fast 🧠",
        "No mercy today 🔥",
        "Can you outsmart your rival? 👀",
        "Let’s play a classic... with style 😎",
        "This is not just a game. It’s WAR. ⚔️"};
    int q = rand() % 5;
    printf("💬 %s\n", quotes[q]);

    printf("⏳ Loading");
    for (int i = 0; i < 3; i++)
    {
        fflush(stdout);
        sleep(1);
        printf(".");
    }
    printf("\n\n");
}

void dropAnimation(int row, int col, char mark)
{
    char temp;
    for (int r = 0; r <= row; r++)
    {
        temp = board[r][col];
        board[r][col] = mark;
        clearScreen();
        printf("🎯 Dropping your move...\n");
        displayBoard();
        usleep(150000);
        board[r][col] = temp;
    }
    board[row][col] = mark;
}

void fireworkFrame(const char *frame[], int lines)
{
    for (int i = 0; i < lines; i++)
    {
        printf("\033[1;36m%s\033[0m\n", frame[i]);
    }
}

void victoryFireworks()
{
    const char *frames[4][7] = {
        {"     *     ",
         "    ***    ",
         "   *****   ",
         "  *******  ",
         "   *****   ",
         "    ***    ",
         "     *     "},
        {"    \\|/    ",
         "  -- * --  ",
         "    /|\\    ",
         "     |     ",
         "   * | *   ",
         "    / \\    ",
         " 🎇 WOW!   "},
        {" \\   |   / ",
         "   \\ | /   ",
         "---  *  ---",
         "   / | \\   ",
         " /   |   \\ ",
         "           ",
         " 🎆 BOOM!  "},
        {"   *   *   ",
         "  * * * *  ",
         " *   *   * ",
         "*    *    *",
         " *   *   * ",
         "  *     *  ",
         "✨ KABOOM! "}};

    for (int i = 0; i < 8; i++)
    {
        clearScreen();
        fireworkFrame(frames[i % 4], 7);
        usleep(300000);
    }

    printf("\n");
}

void playGame()
{
    int player = 1, choice, row, col;
    char mark;

    initializeBoard();

    while (1)
    {
        clearScreen();
        printf("🎯 Current Board:\n");
        displayBoard();

        mark = (player == 1) ? 'X' : 'O';
        printf("👤 \033[1;36mPlayer %d\033[0m (%c), enter a number (1-9): ", player, mark);
        scanf("%d", &choice);

        if (choice < 1 || choice > 9)
        {
            printColor("❌ Invalid move! Try again...\n", "\033[1;31m");
            sleep(1);
            continue;
        }

        row = (choice - 1) / SIZE;
        col = (choice - 1) % SIZE;

        if (board[row][col] == 'X' || board[row][col] == 'O')
        {
            printColor("⚠️ Spot taken! Try again.\n", "\033[1;33m");
            sleep(1);
            continue;
        }

        dropAnimation(row, col, mark);

        if (checkWin())
        {
            clearScreen();
            displayBoard();
            printf("🏆 \033[1;32mPlayer %d WINS!\033[0m 🎉🎉🎉\n", player);
            victoryFireworks();
            printf("🏆 \033[1;32mPlayer %d WINS! GG!\033[0m 🎉🎉🎉\n", player);
            printf("🔥 \033[1;33mLegend status unlocked.\033[0m\n");
            break;
        }

        if (isDraw())
        {
            clearScreen();
            displayBoard();
            printColor("🤝 It's a tie! Respect. 🤜🤛\n", "\033[1;35m");
            break;
        }

        player = (player == 1) ? 2 : 1;
    }
}

int main()
{
    intro();
    playGame();
    return 0;
}
