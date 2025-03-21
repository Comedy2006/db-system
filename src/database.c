// UI will be added later (experimental)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COL 3
#define MAX_LEN 100 //Entries should only be 100 chars long, will be changes later

char*** db = NULL;
int rows = 0;

void db_load(); //load entries from file
void db_save(); //save entries to file
void db_del(); //delete entry from file
void db_add(); //add entry from file
void db_list(); //list entries
void db_enc(); //encrypt the database (will be added in the future)
void db_exit();

int main(int argc, char** argv){
    int choice;
    db_load();
    while(1){
        printf("\n1. Add Record\n2. Delete Record\n3. View Records\n4. Exit\nChoice: ");
        if(scanf("%d", &choice) != 1){
            printf("Invalid Input, please enter an Integer value!\n");
            while (getchar() != '\n');
            continue;
        }
        switch(choice){
            case 1: db_add(); break;
            case 2: db_del(); break;
            case 3: db_list(); break;
            case 4: db_exit(); return 0;
            default: printf("Invalid input!\n");
        }
    }
    return 0;
}

void db_load(){
    FILE* f = fopen("db.txt", "r");
    if (!f) return;

    char tem[MAX_LEN * MAX_COL];
    while (fgets(tem, sizeof(tem), f)){
        db = realloc(db, (rows+1)*sizeof(char**));
        db[rows] = malloc(MAX_COL * sizeof(char*));
        for(int i = 0; i < MAX_COL; i++) {
            db[rows][i] = malloc(MAX_LEN);
        }
        sscanf(tem, "%99[^,],%99[^,],%99[^\n]", db[rows][0], db[rows][1], db[rows][2]);
        rows++;
    }
    fclose(f);
    
    return;
}

void db_save(){
    FILE* f = fopen("db.txt", "w");
    if (!f) return;

    for(int i = 0; i < rows; i++){
        fprintf(f, "%s,%s,%s\n", db[i][0], db[i][1], db[i][2]);
    }

    fclose(f);
}

void db_del(){
    int ind; //index

    printf("Enter the desired index you want to delete:\n");
    if(scanf("%d", &ind) != 1){
        printf("Invalid Input, please enter an Integer value!\n");
        while (getchar() != '\n');
        db_del();
    }

    if (ind < 1 || ind > rows){
        printf("Invalid Index\n");
        return;
    }

    ind--;
    free(db[ind][0]);
    free(db[ind][1]);
    free(db[ind][2]);
    free(db[ind]);

    for(int i = ind; i < rows-1; i++){
        db[i] = db[i+1];
    }

    db[rows-1] = NULL;
    rows--;

    db = realloc(db, rows*sizeof(char**));
    db_save();
}

void db_add(){
    db = realloc(db, (rows+1)*sizeof(char**));
    db[rows] = malloc(MAX_COL*sizeof(char*));

    for(int i = 0; i < MAX_COL; i++){
        db[rows][i]=malloc(MAX_LEN);
    }
    printf("Enter Website:\n");
    scanf("%99s", db[rows][0]);
    printf("Enter Username:\n");
    scanf("%99s", db[rows][1]);
    printf("Enter Password:\n");
    scanf("%99s", db[rows][2]);
    rows++;

    db_save();
}

void db_list(){
    printf("\nStored Records\n");
    for(int i = 0; i < rows; i++){
        printf("%d: %s | %s | %s\n", i+1, db[i][0], db[i][1], db[i][2]);
    }
}

void db_exit(){
    for (int i = 0; i < rows; i++) {
        free(db[i][0]);
        free(db[i][1]);
        free(db[i][2]);
        free(db[i]);
    }
    free(db);
}