#ifndef GRADES
#define GRADES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ReadIntInRange(const char* prompt, int min, int max);
char ReadYesNo(const char* prompt);
void inputGrades(int *arr, int size);
void printGrades(int *arr, int size);
int findMax(int *arr, int size);
int countPassed(int *arr, int size);
int countFailed(int *arr, int size);
double findAverage(int *arr, int size);
void EditGrade(int *arr, int size);
void AddGrade(int **arr, int *size);
void DeleteGrade(int *arr, int *size);

#endif
