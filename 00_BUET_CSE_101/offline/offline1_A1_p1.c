#include<stdio.h>

int main(){
    int amount = -1;
    int notes[] = {200 ,100, 50, 20, 10};
    int wanted[5]={0};
    scanf("%d", &amount);
    if(amount%500 != 0) {
        printf("Invalid Input");
        return 0;
    }
    for(int i = 0; i < 3; i++) {
        scanf(" %d", &wanted[i]);
        if(wanted <= 0){
            printf("Invalid Input");
            return 0;
        }
        if(notes[i]*wanted[i] > amount){
            printf("Exchange Not Possible!");
            return 0;
        }
    }
    for(int i = 0; i < 5; i++){
        if(i > 2)  wanted[i] = amount/(notes[i]);
        amount -= notes[i]*wanted[i];
        printf("Tk %d notes: %d\n",notes[i],wanted[i]);
    }
    return 0;
}


// left amount = amount - notes[i]*wanted[i];
// if notes*wanted greater than amount then amount calculated amount/notes i = available *