    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_ROWS 1000

    int main() {
        FILE *file = fopen("titanic.csv", "r");
        if (!file) {
            printf("Error: Could not open titanic.csv\n");
            return 1;
        }

        char line[1024];
        char gender[MAX_ROWS][10];
        int status[MAX_ROWS];
        float age[MAX_ROWS];
        int count = 0;

        fgets(line, sizeof(line), file);

        while (fgets(line, sizeof(line), file) != NULL && count < MAX_ROWS) {
            char *ptr = line;
            int col = 0;

            while (ptr) {
                char *next = strchr(ptr, ',');
                if (next) {
                    *next = '\0'; 
                }

                if (col == 1) {
                    status[count] = atoi(ptr);
                }
                else if (col == 5) {
                    strcpy(gender[count], ptr);
                }
                else if (col == 6) {
                    if (*ptr == '\0' || *ptr == '\r' || *ptr == '\n') age[count] = -1.0;
                    
                    else  age[count] = atof(ptr);
                }
                if (!next) break;
                ptr = next + 1;
                col++;
            }
            count++;
        }
        
        fclose(file);
        
        int dead_male = 0;
        int alive_male = 0;

        int dead_female = 0;
        int alive_female = 0;

        for(int i = 0 ; i < count ; i++){
            if(age[i] == -1.0) continue;
            if(!(strcmp(gender[i], "male")) && status[i] == 1) alive_male++;
            if(!(strcmp(gender[i], "male")) && status[i] == 0) dead_male++;
            if(!(strcmp(gender[i], "female")) && status[i] == 1) alive_female++;
            if(!(strcmp(gender[i], "female")) && status[i] == 0) dead_female++;
        }
        
        float female = alive_female + dead_female;
        float male = alive_male + dead_male;
        float per_male = 100*(alive_male/male);
        float per_female = 100*(alive_female/female);

        int alive_child = 0;
        int dead_child = 0;
        int alive_adult = 0;
        int dead_adult = 0;
        int alive_senior = 0;
        int dead_senior = 0; 
        for(int i = 0 ; i < count ; i++){
            if((age[i] > 0.00 && age[i] < 18.00)&& status[i] == 1) alive_child++;
            if((age[i] > 0.00 && age[i] < 18.00)&& status[i] == 0) dead_child++;
            if((age[i] >= 18.00 && age[i] < 40.00)&& status[i] == 1) alive_adult++;
            if((age[i] >= 18.00 && age[i] < 40.00)&& status[i] == 0) dead_adult++;
            if(age[i] >= 40.00 && status[i] == 1) alive_senior++;
            if(age[i] >= 40.00 && status[i] == 0) dead_senior++;
        }

        float child = alive_child + dead_child;
        float adult = alive_adult + dead_adult;
        float senior = alive_senior + dead_senior;

        printf("Total Male: %d\n", (int)male);
        printf("Total Dead Male: %d\n", dead_male);
        printf("Percentage of Dead Male: %.2f%%\n\n", 100.0 * (dead_male / male));

        printf("Total Female: %d\n", (int)female);
        printf("Total Dead Female: %d\n", dead_female);
        printf("Percentage of Dead Female: %.2f%%\n\n", 100.0 * (dead_female / female));

        printf("Percentage of Alive Child: %.2f%%\n", 100.0 * (alive_child / child));
        printf("Percentage of Alive Adult: %.2f%%\n", 100.0 * (alive_adult / adult));
        printf("Percentage of Alive Senior: %.2f%%\n", 100.0 * (alive_senior / senior));

        return 0;
    }