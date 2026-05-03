#include "grades.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#define FILE_NAME "grades.txt"


void PrintMenu(void)
{
    printf("\nMenu\n"
           "1 - Print grades\n"
           "2 - Show max\n"
           "3 - Show average\n"
           "4 - Show passed students\n"
           "5 - Show failed students\n"
           "6 - Save students to file\n"
           "7 - Read students from file\n"
           "8 - Read students from keyboard\n"
           "9 - Edit grade\n"
           "10 - Add grade\n"
           "11 - Delete grade\n"
           "12 - Toggle auto save\n"
           "0 - Exit\n");
}
void Savetofile(int *arr, int size) {
     FILE* fptr = fopen(FILE_NAME, "w");
    if (fptr == NULL)
    {
        printf("couldn't open file to save ");
        return;
    }

    fprintf(fptr,"%d\n",size);
    for (int i = 0; i < size; i++)
    {
       fprintf(fptr,"%d\n",arr[i]);
    }
    fclose(fptr);
}

bool Load_grades_from_file(int *arr, int size) {
    FILE* fptr = fopen(FILE_NAME, "r");
    if (fptr == NULL)
    {
        return false;
    }
    int arraysize;

    fscanf(fptr,"%d",&arraysize);
    if (arraysize != size)
    {
        fclose(fptr);
        printf("file exist but student count doesn't match \n");
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        if (fscanf(fptr,"%d",&arr[i])!=1)
        {
            fclose(fptr);
            printf("Error while reading file");
            return false;
        }  
    }

    fclose(fptr);
    return true;
}



int main(void)
{
    bool HasGradesData = false;
    bool Autosave = false;
    int n = ReadIntInRange("how many students\n", 0, 100);
    if (n < 0)
    {
        printf("Invalid size: %d\n", n);
        return 1;
    }
    int *grades = (int *)malloc(n * sizeof(int));
    // Load_grades_from_file(grades,n);
    int choice = 0;
    bool exit = false;
    while (true)
    {
        PrintMenu();
        choice = ReadIntInRange("your choice\n", 0, 12);
        switch (choice)
        {
        case 0:
            exit = true;
            break;
        case 1:
                if (HasGradesData == true) {
                    printGrades(grades, n);
                    printf("\n");
                }
                
            break;
        case 2:
        printf("\n");
                if (n == 0) {
                    printf("No grades available\n");
                }
                else {
                    if (HasGradesData == true) {
                        int Max = findMax(grades, n);
                        printf("Max elements is: %d\n", Max);
                    }
                    
                }
            break;
        case 3:
                if (HasGradesData == true) {
                    printf("\n");
                    double group = findAverage(grades, n);
                    
                    if (group >= 75)
                    {
                        printf("Good group result %f\n", group);
                    }
                    else
                    {
                        printf("Group result is not very strong %f\n", group);
                    }
                    
                    
                }
            break;

        case 4:
                if (HasGradesData == true) {
                    printf("\n");
                    int count = countPassed(grades, n);
                    printf("Students passed %d\n", count);
                }
                
            break;

        case 5:
                if (HasGradesData == true) {
                    printf("\n");
                    int cfailed = countFailed(grades, n);
                    printf("Students not passed %d\n", cfailed);
                    
                }
                
            break;

            case 6:
            printf("Succesfully saved to file \n");
            Savetofile(grades,n);
            break;

            case 7:
                if (Load_grades_from_file(grades,n)) {
                    printf("Succesfully load from file \n");
                    HasGradesData = true;
                }
                else {
                    printf("Failed to load from file \n");
                }
            
            break;

            case 8:
            inputGrades(grades,n);
                HasGradesData = true;
                    
            break;
            case 9:
                if (HasGradesData == true) {
                    EditGrade(grades,n);
                }
            if (Autosave == true)
            {
                Savetofile(grades,n);
            }
            break;
            case 10:
            AddGrade(&grades,&n);
                HasGradesData = true;
            if (Autosave == true)
            {
                Savetofile(grades,n);
            }
            break;
            case 11:
                if (HasGradesData == true) {
                    DeleteGrade(grades,&n);
                }
            if (Autosave == true)
            {
                Savetofile(grades,n);
            }
                if (n == 0) {
                    HasGradesData = false;
                }
            
            break;
            case 12:
            Autosave = !Autosave;
            if (Autosave == true)
            {
                printf("Autosave is now activated\n");
                Savetofile(grades,n);
            }
            else {
                printf("Autosave is now disabled");
            }
            break;
        default:
            printf("Wrong choice the range should be from 1 to 5 \n");

            break;
        }
        if (exit == true)
        {
            break;
        }
    }
    free(grades);
    return 0;
}
