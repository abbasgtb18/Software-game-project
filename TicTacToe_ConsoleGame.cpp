#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3

char board[SIZE][SIZE];

// Initialize the game board
void initBoard() {
    char num = '1';
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = num++;
}

// Display the current board state
void printBoard() {
    system("cls");  // use "clear" for Linux/Mac
    printf("\n  TIC TAC TOE\n  Player 1 (X)  -  Player 2 (O)\n\n");
    for (int i = 0; i < SIZE; ++i) {
        printf("     ");
        for (int j = 0; j < SIZE; ++j) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        if (i < SIZE - 1)
            printf("\n    ---|---|---\n");
    }
    printf("\n\n");
}

// Place the player's mark if valid
bool placeMark(int choice, char mark) {
    if (choice < 1 || choice > 9)
        return false;

    int row = (choice - 1) / SIZE;
    int col = (choice - 1) % SIZE;

    if (board[row][col] == 'X' || board[row][col] == 'O')
        return false;

    board[row][col] = mark;
    return true;
}

// Check for a win
bool checkWin(char mark) {
    for (int i = 0; i < SIZE; ++i)
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark))
            return true;

    return (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark);
}

// Check for a draw
bool checkDraw() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

// Main game logic
void playGame() {
    int currentPlayer = 1;
    char mark;
    int choice;
    bool validMove;

    initBoard();

    while (1) {
        printBoard();
        mark = (currentPlayer == 1) ? 'X' : 'O';

        printf("Player %d [%c], enter your move (1-9): ", currentPlayer, mark);
        if (scanf_s("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear invalid input
            printf("Invalid input. Try again.\n");
            continue;
        }

        validMove = placeMark(choice, mark);

        if (!validMove) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        if (checkWin(mark)) {
            printBoard();
            printf("Player %d [%c] wins the game!\n", currentPlayer, mark);
            break;
        }

        if (checkDraw()) {
            printBoard();
            printf("The game is a draw.\n");
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

// Ask user to play again
bool askReplay() {
    char choice;
    printf("Do you want to play again? (Y/N): ");
    scanf_s(" %c", &choice, 1);
    return (choice == 'Y' || choice == 'y');
}

int main() {
    do {
        playGame();
    } while (askReplay());

    printf("Thanks for playing!\n");
    return 0;
}
