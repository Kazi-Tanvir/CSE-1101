#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char words[20][20] = {
    "programming", "computer", "algorithm", "variable", "function",
    "keyboard", "monitor", "compiler", "language", "software",
    "hardware", "internet", "database", "network", "pointer",
    "terminal", "boolean", "integer", "library", "hangman"
};

char selectedWord[20];
char guessedWord[20];
char guessedLetters[26];
int guessCount = 0;
int attempts = 0;

void drawHangman(int wrong){
    printf("\n  Attempts Left: %d\n", 6 - wrong);
    printf("  +---+\n");
    printf("  |   |\n");

    if(wrong >= 1) printf("  o   |\n");
    else printf("      |\n");

    if(wrong == 2) printf("  |   |\n");
    else if(wrong == 3) printf(" /|   |\n");
    else if(wrong >= 4) printf(" /|\\  |\n");
    else printf("      |\n");

    if(wrong == 5) printf(" /    |\n");
    else if(wrong >= 6) printf(" / \\  |\n");
    else printf("      |\n");

    printf("=========\n\n");
}

void displayWord(){
    printf("  Word: ");
    for(int i = 0; i < strlen(selectedWord); i++){
        printf("%c ", guessedWord[i]);
    }
    printf("\n");
}

void displayGuessedLetters(){
    printf("  Guessed Letters: ");
    for(int i = 0; i < guessCount; i++){
        printf("%c ", guessedLetters[i]);
    }
    printf("\n");
}

int isAlreadyGuessed(char c){
    for(int i = 0; i < guessCount; i++){
        if(guessedLetters[i] == c) return 1;
    }
    return 0;
}

int isWordComplete(){
    for(int i = 0; i < strlen(selectedWord); i++){
        if(guessedWord[i] == '_') return 0;
    }
    return 1;
}

void processGuess(char c){
    guessedLetters[guessCount] = c;
    guessCount++;

    int found = 0;
    for(int i = 0; i < strlen(selectedWord); i++){
        if(selectedWord[i] == c){
            guessedWord[i] = c;
            found = 1;
        }
    }

    if(!found){
        attempts++;
        printf("  Wrong guess!\n");
    }
    else{
        printf("  Correct!\n");
    }
}

void selectWord(){
    int index = rand() % 20;
    strcpy(selectedWord, words[index]);
    int len = strlen(selectedWord);
    for(int i = 0; i < len; i++){
        guessedWord[i] = '_';
    }
    guessedWord[len] = '\0';
}

void resetGame(){
    guessCount = 0;
    attempts = 0;
    memset(guessedLetters, 0, 26);
    memset(guessedWord, 0, 20);
    selectWord();
}

void playGame(){
    resetGame();
    printf("\n===== HANGMAN GAME =====\n");
    printf("  Guess the word! You have 6 attempts.\n");

    while(attempts < 6 && !isWordComplete()){
        drawHangman(attempts);
        displayWord();
        displayGuessedLetters();

        char input;
        printf("\n  Enter a letter: ");
        scanf(" %c", &input);
        if(input >= 'A' && input <= 'Z') input = input + 32;

        if(!(input >= 'a' && input <= 'z')){
            printf("  Invalid input! Enter a letter (a-z).\n");
            continue;
        }

        if(isAlreadyGuessed(input)){
            printf("  You already guessed '%c'. Try another.\n", input);
            continue;
        }

        processGuess(input);
    }

    drawHangman(attempts);
    displayWord();

    if(isWordComplete()){
        printf("  You WIN! The word was: %s\n\n", selectedWord);
    }
    else{
        printf("  You LOST! The word was: %s\n\n", selectedWord);
    }
}

int main(){
    int seed;
    printf("Enter any number to start: ");
    scanf("%d", &seed);
    srand(seed);
    int choice;

    do{
        printf("=============================\n");
        printf("    HANGMAN - Main Menu\n");
        printf("=============================\n");
        printf("1. Play Game\n");
        printf("2. Exit\n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        if(choice == 1) playGame();
        else if(choice != 2) printf("Invalid choice!\n");
        printf("\n");
    } while(choice != 2);

    printf("Thanks for playing!\n");
    return 0;
}
