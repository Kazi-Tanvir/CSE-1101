#include<stdio.h>


int main(){  
    double d[10] = {
        10.23, 19.87, 1002.23, 12.9, 0.897,
        11.45, 75.34, 0.0, 1.01, 875.875
    };

    FILE *file = fopen("data/myfile","wb");
    if(!file) return 1;
    
    if(fwrite(d,sizeof(d),1,file) != 1){
        printf("Cannot Write\n");
        return 1;
    }
    fclose(file);   
    for(int i = 0 ; i < 10 ; i ++) d[i] = -1.0;
    
    file = fopen("data/myfile","rb");
        if(!fread(d,sizeof(d),1,file)){
            printf("Read Error\n");
            return 1;
    }
    fclose(file);
    for(int i = 0 ; i < 10 ; i ++) printf("%.3f ",d[i]);
}