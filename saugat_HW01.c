# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

struct database{
    char* column;
    char* values[1024];
};



void get_unique_degrees(char* values[], int rows){
    int i, j, counter = 0;
    char* unique_degrees[50];

    for (i=0; i<rows; i++){
        int unique = 1;
        for (j=0; j<counter; j++){
            if (!strcmp(values[i], unique_degrees[j])){
                unique = 0;
                break;
            }
        }
        if (unique == 1){
            unique_degrees[counter] = (char *) malloc(25);
            strcpy(unique_degrees[counter], values[i]);
            counter++;
        }
    }
    
    printf("Total number of Unique Degrees: ");
    printf("%d\n", counter);
    printf("Unique Degrees:\n");
    for (j=0; j<counter; j++){
        printf("%s\n", unique_degrees[j]);
    }
}

void get_top3_gpa(char* gpa[], char* first_name[], char* last_name[], int rows){
    float top1, top2, top3 = -1;
    int top1_idx, top2_idx, top3_idx = 0;
    int curr;

    for (curr=0; curr<rows; curr++){
        if (atof(gpa[curr]) > top1){
            // get the values
            top3 = top2;
            top2 = top1;
            top1 = atof(gpa[curr]);

            // get the index
            top3_idx = top2_idx;
            top2_idx = top1_idx;
            top1_idx = curr;
        }
        else if (atof(gpa[curr]) > top2 && atof(gpa[curr]) != top1){
            // get the value
            top3 = top2;
            top2 = atof(gpa[curr]);

            // get the index
            top3_idx = top2_idx;
            top2_idx = curr;
        }
        else if(atof(gpa[curr]) > top3 && atof(gpa[curr]) != top2){
            // get the value
            top3 = atof(gpa[curr]);

            // get the index
            top3_idx = curr;
        }
    }

    printf("\nFull Name of Students with top 3 Highest GPA:\n");
    printf("%s %s\n", first_name[top1_idx], last_name[top1_idx]);
    printf("%s %s\n", first_name[top2_idx], last_name[top2_idx]);
    printf("%s %s\n", first_name[top3_idx], last_name[top3_idx]);

}

void get_avg_credit_hrs(char* credit_hrs[], int rows){
    int i;
    double total_credit_hrs;
    for (i=0; i<rows; i++){
        total_credit_hrs += atoi(credit_hrs[i]);
    }

    printf("\nAverage Credit Hours: %.2f\n", total_credit_hrs/rows);
}

void get_cs_avg_gpa(char* major[], char* gpa[], int rows){
    int i;
    double total_cs_gpa;
    int counter = 0;
    for (i=0; i<rows; i++){
        if (!strcmp(major[i], "Computer Science")){
            total_cs_gpa += atof(gpa[i]);
            counter++;
        }
    }

    if (counter > 0){
        printf("\nCS average GPA: %.2f\n", total_cs_gpa/counter);
    }
    else{
        printf("\nNo Students from CS department!");
    }
    
}

void get_advisor_count(char* advisor[], char* major[], int rows){

    int i, j, counter = 0;
    char* unique_dept[50];

    // first get unique department
    for (i=0; i<rows; i++){
        int unique = 1;
        for (j=0; j<counter; j++){
            if (!strcmp(major[i], unique_dept[j])){
                unique = 0;
                break;
            }
        }
        if (unique == 1){
            unique_dept[counter] = (char *) malloc(25);
            strcpy(unique_dept[counter], major[i]);
            counter++;
        }
    }

    printf("\nUnique Advisors per department: \n");
    
    for (j=0; j<counter; j++){
        // if (strcmp(unique_dept[j], major[j])){
        //     continue;
        // }
        char* unique_advisor[50];
        // printf("%s: %d\n", unique_dept[j], counter);

        int advisor_counter = 0;
        for (i=0; i<rows; i++){
            if (strcmp(unique_dept[j], major[i])){
                continue;
            }

            int unique = 1;
            int k;
            for (k=0; k<advisor_counter; k++){
                if (!strcmp(advisor[i], unique_advisor[k])){
                    unique = 0;
                    break;
                }
            }
            if (unique == 1){
                unique_advisor[advisor_counter] = (char *) malloc(25);
                strcpy(unique_advisor[advisor_counter], advisor[i]);
                advisor_counter++;
            }
            
        }
        printf("%s: %d\n", unique_dept[j], advisor_counter);

    }


}

int main(int argc, char** argv){
    const char* filename = "students_dataset.csv";
    FILE* fstream = fopen(filename, "r");

    char line[1024];

    int r = 0; // rows
    int c; // columns

    char* columnNames[1024] = {};

    struct database db[9];

    while (fgets(line, 1024, fstream)){
        char* tokens = strtok(line, ",");
        if (r == 0){
            c = 0;
            while (tokens){
                db[c].column = (char *) malloc(25);
                strcpy(db[c].column, tokens);
                tokens = strtok(NULL, ",");
                c++;
            }

        }
        // printf("%s\n", db[0].column);
        else{
            c = 0;
            while(tokens){
                db[c].values[r-1] = (char *) malloc(25);
                strcpy(db[c].values[r-1], tokens);
                tokens = strtok(NULL, ",");
                c++;
            }
        }

        r++;
    }

    get_unique_degrees(db[3].values, r-1);
    get_top3_gpa(db[4].values, db[0].values, db[1].values, r-1);
    get_avg_credit_hrs(db[5].values, r-1);
    get_cs_avg_gpa(db[2].values, db[4].values, r-1);
    get_advisor_count(db[7].values, db[2].values, r-1);

    return 0;
}
