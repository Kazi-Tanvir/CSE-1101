#include<stdio.h>
#include<string.h>
#include<math.h>

#define MAX_BOOKS 20
#define MAX_MEMBERS 50

int totalBooks = 0;
char bookTitle[MAX_BOOKS][100];
int bookID[MAX_BOOKS];
int bookStatus[MAX_BOOKS]; // 1 = available, 0 = unavailable

int memberID[MAX_MEMBERS];
int memberStatus[MAX_MEMBERS]; // 0 = no book borrowed, book ID = borrowed book ID

// a. Function to add a new book and print the list of books
void addBookAndPrint(){
    if(totalBooks >= MAX_BOOKS){
        printf("Cannot add more books! Maximum limit reached.\n\n");
        return;
    }

    int i = totalBooks;
    printf("Enter Book ID: ");
    scanf("%d", &bookID[i]);
    printf("Enter Book Title: ");
    scanf(" %[^\n]", bookTitle[i]);
    bookStatus[i] = 1; // 1 means available to borrow
    totalBooks++;

    printf("\nBook added successfully!\n");
    printf("--- Current Book List ---\n");
    for(int j = 0; j < totalBooks; j++){
        printf("Book ID: %d | Title: %s | Status: %s\n", 
               bookID[j], bookTitle[j], bookStatus[j] == 1 ? "Available (1)" : "Unavailable (0)");
    }
    printf("\n");
}

// b. Function to borrow a book by a member
void borrowBook(){
    int mID, bID;
    printf("Enter Member ID (1 to 50): ");
    scanf("%d", &mID);

    if(mID < 1 || mID > MAX_MEMBERS){
        printf("Invalid Member ID!\n\n");
        return;
    }

    int mIdx = mID - 1; // 0-based array index

    if(memberStatus[mIdx] != 0){
        printf("Member %d has already borrowed Book ID %d! (Limit: 1 book)\n\n", mID, memberStatus[mIdx]);
        return;
    }

    printf("Enter Book ID to borrow: ");
    scanf("%d", &bID);

    int bookIdx = -1;
    for(int i = 0; i < totalBooks; i++){
        if(bookID[i] == bID){
            bookIdx = i;
            break;
        }
    }

    if(bookIdx == -1){
        printf("Book ID not found!\n\n");
        return;
    }

    if(bookStatus[bookIdx] == 0){
        printf("Book is currently unavailable!\n\n");
        return;
    }

    // Process borrowing
    memberStatus[mIdx] = bID;
    bookStatus[bookIdx] = 0; // Set book status to unavailable
    printf("Member %d successfully borrowed '%s'!\n\n", mID, bookTitle[bookIdx]);
}

// c. Function to return a book by a member
void returnBook(){
    int mID;
    printf("Enter Member ID (1 to 50): ");
    scanf("%d", &mID);

    if(mID < 1 || mID > MAX_MEMBERS){
        printf("Invalid Member ID!\n\n");
        return;
    }

    int mIdx = mID - 1;

    if(memberStatus[mIdx] == 0){
        printf("Member %d has not borrowed any book!\n\n", mID);
        return;
    }

    int borrowedBookID = memberStatus[mIdx];

    // Find and update book status back to available
    for(int i = 0; i < totalBooks; i++){
        if(bookID[i] == borrowedBookID){
            bookStatus[i] = 1;
            break;
        }
    }

    // Reset member status
    memberStatus[mIdx] = 0;
    printf("Book returned successfully by Member %d!\n\n", mID);
}

// d. Search function to check if a member borrowed a book and its title
void searchMember(){
    int mID;
    printf("Enter Member ID (1 to 50): ");
    scanf("%d", &mID);

    if(mID < 1 || mID > MAX_MEMBERS){
        printf("Invalid Member ID!\n\n");
        return;
    }

    int mIdx = mID - 1;

    if(memberStatus[mIdx] == 0){
        printf("Member %d has not borrowed any book.\n\n", mID);
    } else {
        int borrowedBookID = memberStatus[mIdx];
        char borrowedTitle[100] = "Unknown Title";

        for(int i = 0; i < totalBooks; i++){
            if(bookID[i] == borrowedBookID){
                strcpy(borrowedTitle, bookTitle[i]);
                break;
            }
        }
        printf("Member %d HAS borrowed a book.\n", mID);
        printf("Book ID: %d\n", borrowedBookID);
        printf("Book Title: %s\n\n", borrowedTitle);
    }
}

int main(){
    // Initialize member list
    for(int i = 0; i < MAX_MEMBERS; i++){
        memberID[i] = i + 1;
        memberStatus[i] = 0; // 0 means no book borrowed
    }

    int choice;
    do {
        printf("1. Add Book & Display List\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. Search Member Status\n");
        printf("5. Exit\n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        if(choice == 1) addBookAndPrint();
        else if(choice == 2) borrowBook();
        else if(choice == 3) returnBook();
        else if(choice == 4) searchMember();
        else if(choice != 5) printf("Invalid choice!\n\n");

    } while(choice != 5);

    return 0;
}