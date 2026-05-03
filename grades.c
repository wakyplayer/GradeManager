#include "grades.h"

int ReadIntInRange(const char* prompt, int min, int max){
    char Line[100];
    char extra;
    int value;
    while(1) {
        printf("%s",prompt);
        if (fgets(Line, sizeof(Line), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }
        if (sscanf(Line, " %d %c", &value, &extra) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        if (value < min || value > max)
        {
            printf("Invalid input. Enter a number from %d to %d.\n", min, max);
            continue;
            
        }
        
        return value;
    }
}
char ReadYesNo(const char* prompt){
    char Line[100];
    while(1) {
        
        printf("%s",prompt);
        if (fgets(Line, sizeof(Line), stdin) == NULL) {
            clearerr(stdin);
            continue;
        }
        if (Line[0] == 'y' || Line[0] == 'Y') {
            return 'y';
        }
        if (Line[0] == 'n' || Line[0] == 'N') {
            return 'n';
        }
        printf("invalid input please enter y or n\n");
    }
}


void inputGrades(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Grade %d: ", i + 1);
        scanf("%d", &arr[i]);
        if (arr[i] < 0 || arr[i] > 100)
        {
            printf("Invalid grade: %d\n", arr[i]);
            arr[i] = ReadIntInRange("Enter a grade(0-100) ", 0, 100);
        }
    }
}
void printGrades(int *arr, int size)
{

    printf("Student grades are: \n");
    for (int i = 0; i < size; i++)
    {
        printf("%d \n", arr[i]);
    }
}
int findMax(int *arr, int size)
{
    if (size == 0) {
        return 0;
    }
    int Max = arr[0];
    for (int i = 0; i < size; i++)
    {

        if (arr[i] > Max)
        {
            Max = arr[i];
        }
    }
    return Max;
}
int countPassed(int *arr, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] >= 60)
        {
            count++;
        }
    }
    return count;
}
int countFailed(int *arr, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < 60)
        {
            count++;
        }
    }
    return count;
}

double findAverage(int *arr, int size)
{
    if (size == 0) {
        return 0;
    }
    
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    sum /= size;
    return sum;
}
void EditGrade(int *arr, int size) {
    
    if (size == 0)
    {
        printf("no grades available to edit\n");
        return;
    }
    int index = ReadIntInRange("Enter grade index to edit (0-based)\n", 0, size -1);
    int value = ReadIntInRange("Enter a grade(0-100) ", 0, 100);
    arr[index] = value;
    
}
void AddGrade(int **arr, int *size){
    int grade = ReadIntInRange("Enter a grade(0-100) ", 0, 100);
    /* Use a temporary pointer so we do not lose the old memory if realloc fails. */
    int *temp = realloc(*arr, (*size + 1) * sizeof(int));
    if (temp == NULL)
    {
        return;
    }
    else  {
        /* Write the new pointer back to main through the double pointer. */
        *arr = temp;
        (*arr)[*size] = grade;
        (*size)++;
        printf("Grade succesfully added: %d\n",grade);
    }
    
}
void DeleteGrade(int *arr, int *size) {
    if (*size == 0) {
        printf("no grades available to delete\n");
        return;
    }
    char choice = ReadYesNo("Confirm that you want to delete grade at the end (y/n)\n");
    if (choice == 'y')
    {
        (*size)--;
        printf("Grade succesfully deleted\n");

    }
}
