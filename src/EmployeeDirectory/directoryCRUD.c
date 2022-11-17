#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getCharInput(char* message) {
  char* userInput = malloc(sizeof(char)*100);
  printf(message);
  scanf("%s", userInput);
  return userInput;
}

int getIntInput(char* message) {
  int userInput = -1;
  printf(message);
  scanf("%d", &userInput);
  return userInput;
}

void displayEmployees(){
  FILE* fp = fopen("directory.txt", "r");

  if(fp == NULL)
  {
    printf("Cannot open file\n");
    return;
  }

  char* line[500];
  int lineNumber = 1;

  printf("\nLast Name, First Name, Position, Employee ID,Telephone\n");
  while (fgets(line, sizeof(line), fp)) {
    printf("%d: %s", lineNumber, line);
    lineNumber++;
  }
}

void addEmployee() {

  FILE* fp = fopen("directory.txt", "a");

  if (fp == NULL)
  {
    printf("Cannot open file\n");
    return;
  }

  char* last = getCharInput("Please enter last name: ");
  char* first = getCharInput("Please enter first name: ");
  char* position = getCharInput("Please enter position: ");
  char* id = getCharInput("Please enter id: ");
  char* phone = getCharInput("Please enter telephone number: ");

  fprintf(fp, "%s,%s,%s,%s,%s\n", last, first, position, id, phone);

  fclose(fp);
  chmod("directory.txt", strtol("644", 0, 8));
  chown("directory.txt", 0, 0);
}

void deleteEmployee() {
  FILE* fp = fopen("directory.txt", "r");
  FILE* fpTemp = fopen("temp.txt", "w");

  if (fp == NULL) {
    printf("No entries to delete\n");
    return;
  }

  int deleteNumber = getIntInput("Please enter record number to delete: ");

  char line[500];
  int lineNumber = 1;

  while((fgets(line, sizeof(line), fp)) != NULL){
    if (lineNumber != deleteNumber){
      fputs(line, fpTemp);
    }
    lineNumber++;
  }

  fclose(fp);
  fclose(fpTemp);
  remove("directory.txt");
  rename("temp.txt", "directory.txt");
  chmod("directory.txt", strtol("644", 0, 8));
  chown("directory.txt", 0, 0);
}

void editEmployee() {
  FILE* fp = fopen("directory.txt", "r");
  FILE* fpTemp = fopen("temp.txt", "w");

  if (fp == NULL) {
    printf("No entries to delete\n");
    return;
  }

  int editNumber = getIntInput("Please enter record number to edit: ");
  char* last = getCharInput("Please enter last name: ");
  char* first = getCharInput("Please enter first name: ");
  char* position = getCharInput("Please enter position: ");
  char* id = getCharInput("Please enter id: ");
  char* phone = getCharInput("Please enter telephone number: ");

  char line[500];
  int lineNumber = 1;

  while((fgets(line, sizeof(line), fp)) != NULL){
    if (lineNumber == editNumber){
      fprintf(fpTemp, "%s,%s,%s,%s,%s\n", last, first, position, id, phone);
    }
    else {
      fputs(line, fpTemp);
    }

    lineNumber++;
  }

  fclose(fp);
  fclose(fpTemp);
  remove("directory.txt");
  rename("temp.txt", "directory.txt");
  chmod("directory.txt", strtol("644", 0, 8));
  chown("directory.txt", 0, 0);
}

void changePassword() {

  FILE* fp = fopen("password.txt", "w");

  if (fp == NULL)
  {
    printf("Cannot open file\n");
    return;
  }

  char* userPassword = getCharInput("Please enter new password: ");
  fputs(userPassword, fp);

  fclose(fp);
  chmod("password.txt", strtol("600", 0, 8));
  chown("password.txt", 0, 0);
  return;
}

int isPasswordValid() {

  FILE* fp = fopen("password.txt", "r");

  if (fp == NULL)
  {
    char* userPassword = getCharInput("No password set. Please enter password: ");

    /* If no password file, then create one and create default password */
    fp = fopen("password.txt", "w");
    fputs(userPassword, fp);
    fclose(fp);
    chmod("password.txt", strtol("600", 0, 8));
    return 1;
  }
  else {

    char* userPassword = getCharInput("Please enter password: ");

    char* filePassword[100];
    fgets(filePassword, sizeof(filePassword), fp);
    fclose(fp);
    chmod("password.txt", strtol("600", 0, 8));
    chown("password.txt", 0, 0);

    if (strcmp(filePassword, userPassword) == 0) {
      return 1;
    }
    else {
      printf ("\nIncorrect password\n");
    }

  }

  return 0;
}