#ifndef GRADES
#define GRADES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ReadIntInRange(const char* prompt, int min, int max);
char ReadYesNo(const char* prompt);
void InputGrades(int *arr, int size);
void PrintGrades(int *arr, int size);
int findMax(int *arr, int size);
int CountPassed(int *arr, int size);
int CountFailed(int *arr, int size);
double FindAverage(int *arr, int size);
void EditGrade(int *arr, int size);
void AddGrade(int **arr, int *size);
void DeleteGrade(int **arr, int *size);

#endif
