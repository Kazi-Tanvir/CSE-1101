#include <stdio.h>
#include <stdlib.h>

int winCondition(char board[9]) {
    if (board[0] == board[1] && board[1] == board[2]) return 1;
    if (board[3] == board[4] && board[4] == board[5]) return 1;
    if (board[6] == board[7] && board[7] == board[8]) return 1;
    if (board[0] == board[3] && board[3] == board[6]) return 1;
    if (board[1] == board[4] && board[4] == board[7]) return 1;
    if (board[2] == board[5] && board[5] == board[8]) return 1;
    if (board[0] == board[4] && board[4] == board[8]) return 1;
    if (board[2] == board[4] && board[4] == board[6]) return 1;
    return 0;
}

void printBoard(int n, int i, char board[9], char p1, char p2) {
    for (int j = 1; j < 10; j++) {
        if (j == n) {
            board[j - 1] = (i % 2 == 0) ? p1 : p2;
        }
        printf("%c", board[j - 1]);
        if (j % 3 == 0) {
            printf("\n----------\n");
        }
        if (j % 3 != 0) {
            printf(" | ");
        }
    }
}

int validMove(int n, int done[9]) {
    if (n > 9 || n < 1) return 0;
    for (int i = 0; i < 9; i++) {
        if (done[i] == n) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n, p;
    char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int done[9] = {0};
    char p1, p2;

    printf("Choose your Character [1 for X and 2 for O] : ");
    scanf("%d", &p);
    if (p == 1) {
        p1 = 'X';
        p2 = 'O';
    } else {
        p1 = 'O';
        p2 = 'X';
    }

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            printf("Your Turn\n");
            printf("Enter Your Position (1-9) : ");
            scanf("%d", &n);
        } else {
            printf("Computers Turn\n");
            n = rand() % 9 + 1;
            printf("Computer Position : %d\n", n);
        }

        if (!validMove(n, done)) {
            printf("Invalid move\n");
            i--;
            continue;
        }

        done[i] = n;
        printBoard(n, i, board, p1, p2);

        if (winCondition(board)) {
            if (i % 2 == 0) {
                printf("You win\n");
            } else {
                printf("Computer wins\n");
            }
            break;
        }
        if (i == 8 && !winCondition(board)) {
            printf("Draw\n");
        }
    }

    return 0;
}