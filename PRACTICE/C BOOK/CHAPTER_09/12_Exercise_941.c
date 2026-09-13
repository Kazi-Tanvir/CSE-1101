#include <stdio.h>
#include <string.h>
int total = 0;
void input(char *list[2][30]);
void findNum(void);
void save(void);
void load(void);

int main()
{
    int choice = -1;
    char list[100][2][30];
    printf("1. Enter the names and numbers\n2. Find numbers\n3. Save directory to disk\n4. Load directory from disk\n5. Quit");
    printf("Enter your choice : ");
    scanf(" %d", &choice);

    switch (choice)
    {
    case 1:
        input(list);
        break;
    case 2:
        findNum();
        break;
    case 3:
        save();
        break;
    case 4:
        load();
        break;
    default:
        break;
    }
}

void input(char *list[2][30])
{
    char name[30], num[30];
    
    printf("Enter the name : ");
    scanf(" %29s", name);
    printf("Enter your number : ");
    scanf(" %29s", num);

    strcpy(list[total][0], name);
    strcpy(list[total][1], num);
    total++;
}