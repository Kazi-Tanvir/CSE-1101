    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>


    #define MAX_ROWS 1000

    int age_group(float age) {
        if (age > 0 && age < 18.0) return 1; 
        else if (age >= 18.0 && age < 40.0) return 2;
        else if (age >= 40.0) return 3;
    }

    int main() {
        FILE *file = fopen("data/titanic.csv", "r");
        FILE *file1 = fopen("data/titanic_1.csv", "w");
        if (!file) {
            printf("Error: Could not open titanic.csv\n");
            return 1;
        }

        char line[1024];
        char original[1024];
        float age[MAX_ROWS];
        int count = 0;

        if(fgets(line,sizeof(line),file)){
            line[strcspn(line,"\r\n")] = '\0';
            fprintf(file1,"%s,Age_Group\n",line);
        }

    

        while (fgets(line, sizeof(line), file) != NULL && count < MAX_ROWS) {
            strcpy(original,line);
            original[strcspn(original,"\r\n")] = '\0';
            char *ptr = line;
            int col = 0;

            while (ptr) {
                char *next = strchr(ptr, ',');
                if (next) {
                    *next = '\0'; 
                }
                if (col == 6) {
                    if (*ptr == '\0' || *ptr == '\r' || *ptr == '\n') age[count] = -1.0;
                    else  age[count] = atof(ptr);
                }
                if (!next) break;
                ptr = next + 1;
                col++;
            }
            if(age[count] != -1.0) {
                fprintf(file1,"%s,%d\n",original,age_group(age[count]));
            }
            count++;
        }
        fclose(file);
        fclose(file1);
        return 0;
    }