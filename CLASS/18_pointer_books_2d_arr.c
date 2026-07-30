void book(){
    char *book[20];
    for(int i = 0; i < 20 ;i++){
        scanf(" %[\n]",book[i]);
    }
    for(int i = 0; i < 20 ;i++){
        printf("%s\n",book[i]);
    }
}

int main(){
    book();
    return 0;
}
