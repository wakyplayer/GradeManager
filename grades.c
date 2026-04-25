#include "grades.h"

void inputGrades(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Grade %d: ", i + 1);
        scanf("%d", &arr[i]);
        if (arr[i] < 0 || arr[i] > 100)
        {
            printf("Invalid grade: %d\n", arr[i]);
            arr[i] = 0;
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
        return;
    }
    int index;
    printf("Enter grade index to edit \n");
    scanf("%d",&index);
    if (index>=0 && index<size)
    {
        int value;
        printf("Enter new grade \n");
        scanf("%d",&value);
        arr[index] = value;
    }
    
}
void AddGrade(int *arr, int *size){
    int grade;
    printf("add new grade \n");
    scanf("%d",&grade);
    int *temp = realloc(arr, (*size + 1) * sizeof(int));
    if (temp == NULL)
    {
        return;
    }
    else  {
        arr = temp;
        arr[*size] = grade;
        (*size)++;
        printf("Grade succesfully added: %d\n",grade);
    }
    
}
void DeleteGrade(int *arr, int *size) {
    printf("Confirm that you want to delete grade at the end (y/n)\n");
    char choice;
    scanf(" %c",&choice);
    if (choice == 'y')
    {
        (*size)--;
        printf("Grade succesfully deleted\n");

    }
}