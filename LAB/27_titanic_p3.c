    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_ROWS 1000

    int main() {
        FILE *file = fopen("data/titanic_1.csv", "r");
        if (!file) {
            printf("Error: Could not open titanic_1.csv\n");
            return 1;
        }

        char line[1024];
        char gender[MAX_ROWS][10];
        int status[MAX_ROWS];
        int passengerClass[MAX_ROWS];
        int ageClass[MAX_ROWS];
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

                if (col == 1) status[count] = atoi(ptr);
                if (col == 2) passengerClass[count] = atoi(ptr);
                if (col == 5) strcpy(gender[count], ptr);
                if (col == 13) ageClass[count] = atoi(ptr);

                if (!next) break;
                ptr = next + 1;
                col++;
            }
            count++;
        }
        
        fclose(file);
        
        int dead_male = 0, alive_male = 0;
        int dead_female = 0, alive_female = 0;

        int dead_pclass1 = 0, alive_pclass1 = 0;
        int dead_pclass2 = 0, alive_pclass2 = 0;
        int dead_pclass3 = 0, alive_pclass3 = 0;

        int dead_age1 = 0, alive_age1 = 0;
        int dead_age2 = 0, alive_age2 = 0;
        int dead_age3 = 0, alive_age3 = 0;

        for (int i = 0; i < count; i++) {
            if (strcmp(gender[i], "male") == 0) {
                if (status[i] == 1) alive_male++;
                else if (status[i] == 0) dead_male++;
            } else if (strcmp(gender[i], "female") == 0) {
                if (status[i] == 1) alive_female++;
                else if (status[i] == 0) dead_female++;
            }

            if (passengerClass[i] == 1) {
                if (status[i] == 1) alive_pclass1++;
                else if (status[i] == 0) dead_pclass1++;
            } else if (passengerClass[i] == 2) {
                if (status[i] == 1) alive_pclass2++;
                else if (status[i] == 0) dead_pclass2++;
            } else if (passengerClass[i] == 3) {
                if (status[i] == 1) alive_pclass3++;
                else if (status[i] == 0) dead_pclass3++;
            }

            if (ageClass[i] == 1) {
                if (status[i] == 1) alive_age1++;
                else if (status[i] == 0) dead_age1++;
            } else if (ageClass[i] == 2) {
                if (status[i] == 1) alive_age2++;
                else if (status[i] == 0) dead_age2++;
            } else if (ageClass[i] == 3) {
                if (status[i] == 1) alive_age3++;
                else if (status[i] == 0) dead_age3++;
            }
        }

        int total_male = alive_male + dead_male;
        int total_female = alive_female + dead_female;

        int total_pclass1 = alive_pclass1 + dead_pclass1;
        int total_pclass2 = alive_pclass2 + dead_pclass2;
        int total_pclass3 = alive_pclass3 + dead_pclass3;

        int total_age1 = alive_age1 + dead_age1;
        int total_age2 = alive_age2 + dead_age2;
        int total_age3 = alive_age3 + dead_age3;

        printf("=== GENDER CATEGORY ===\n");
        printf("Total Male: %d\n", total_male);
        printf("Alive Male: %d\n", alive_male);
        printf("Dead Male: %d\n", dead_male);
        printf("Percentage of Dead Male: %.2f%%\n\n", 100.0 * dead_male / total_male);

        printf("Total Female: %d\n", total_female);
        printf("Alive Female: %d\n", alive_female);
        printf("Dead Female: %d\n", dead_female);
        printf("Percentage of Dead Female: %.2f%%\n\n", 100.0 * dead_female / total_female);

        printf("=== PASSENGER CLASS CATEGORY ===\n");
        printf("Total Class 1: %d\n", total_pclass1);
        printf("Alive Class 1: %d\n", alive_pclass1);
        printf("Dead Class 1: %d\n", dead_pclass1);
        printf("Percentage of Dead Class 1: %.2f%%\n\n", 100.0 * dead_pclass1 / total_pclass1);

        printf("Total Class 2: %d\n", total_pclass2);
        printf("Alive Class 2: %d\n", alive_pclass2);
        printf("Dead Class 2: %d\n", dead_pclass2);
        printf("Percentage of Dead Class 2: %.2f%%\n\n", 100.0 * dead_pclass2 / total_pclass2);

        printf("Total Class 3: %d\n", total_pclass3);
        printf("Alive Class 3: %d\n", alive_pclass3);
        printf("Dead Class 3: %d\n", dead_pclass3);
        printf("Percentage of Dead Class 3: %.2f%%\n\n", 100.0 * dead_pclass3 / total_pclass3);

        printf("=== AGE CLASS CATEGORY ===\n");
        printf("Total Child (Class 1): %d\n", total_age1);
        printf("Alive Child (Class 1): %d\n", alive_age1);
        printf("Dead Child (Class 1): %d\n", dead_age1);
        printf("Percentage of Dead Child (Class 1): %.2f%%\n\n", 100.0 * dead_age1 / total_age1);

        printf("Total Adult (Class 2): %d\n", total_age2);
        printf("Alive Adult (Class 2): %d\n", alive_age2);
        printf("Dead Adult (Class 2): %d\n", dead_age2);
        printf("Percentage of Dead Adult (Class 2): %.2f%%\n\n", 100.0 * dead_age2 / total_age2);

        printf("Total Senior (Class 3): %d\n", total_age3);
        printf("Alive Senior (Class 3): %d\n", alive_age3);
        printf("Dead Senior (Class 3): %d\n", dead_age3);
        printf("Percentage of Dead Senior (Class 3): %.2f%%\n", 100.0 * dead_age3 / total_age3);

        return 0;
    }