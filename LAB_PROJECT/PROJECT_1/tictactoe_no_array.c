#include <stdio.h>
#include <stdlib.h>


char b1 = '1', b2 = '2', b3 = '3', b4 = '4', b5 = '5', b6 = '6', b7 = '7', b8 = '8', b9 = '9';

int winCondition() {
    if (b1 == b2 && b2 == b3) return 1;
    if (b4 == b5 && b5 == b6) return 1;
    if (b7 == b8 && b8 == b9) return 1;
    if (b1 == b4 && b4 == b7) return 1;
    if (b2 == b5 && b5 == b8) return 1;
    if (b3 == b6 && b6 == b9) return 1;
    if (b1 == b5 && b5 == b9) return 1;
    if (b3 == b5 && b5 == b7) return 1;
    return 0;
}

void printBoard(int n, int i, char p1, char p2) {
    char val = (i % 2 == 0) ? p1 : p2;
    if (n == 1) b1 = val;
    else if (n == 2) b2 = val;
    else if (n == 3) b3 = val;
    else if (n == 4) b4 = val;
    else if (n == 5) b5 = val;
    else if (n == 6) b6 = val;
    else if (n == 7) b7 = val;
    else if (n == 8) b8 = val;
    else if (n == 9) b9 = val;

    printf("%c | %c | %c\n", b1, b2, b3);
    printf("----------\n");
    printf("%c | %c | %c\n", b4, b5, b6);
    printf("----------\n");
    printf("%c | %c | %c\n", b7, b8, b9);
    printf("----------\n");
}

int validMove(int n) {
    if (n > 9 || n < 1) return 0;
    if (n == 1) return b1 == '1';
    if (n == 2) return b2 == '2';
    if (n == 3) return b3 == '3';
    if (n == 4) return b4 == '4';
    if (n == 5) return b5 == '5';
    if (n == 6) return b6 == '6';
    if (n == 7) return b7 == '7';
    if (n == 8) return b8 == '8';
    if (n == 9) return b9 == '9';
    return 0;
}

int main() {
    int n, p;
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

        if (!validMove(n)) {
            printf("Invalid move\n");
            i--;
            continue;
        }

        printBoard(n, i, p1, p2);

        if (winCondition()) {
            if (i % 2 == 0) {
                printf("You win\n");
            } else {
                printf("Computer wins\n");
            }
            break;
        }
        if (i == 8 && !winCondition()) {
            printf("Draw\n");
        }
    }

    return 0;
}