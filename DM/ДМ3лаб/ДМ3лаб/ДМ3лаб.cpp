
// 
//флоид
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int thereAreReplaces(int N);

int main(){
    int N;
    FILE* inputFile = fopen("input.txt", "r");
    fscanf(inputFile, "%d", &N);
    fclose(inputFile);
    int k = 1;
    int i = 1;
    while (k <= N){
        if (!thereAreReplaces(i)){
            k += 1;
        }
        i += 1;
    }
    FILE* outputFile = fopen("output.txt", "w");
    fprintf(outputFile, "%d", i - 1);
    fclose(outputFile);
    return 0;
}

int thereAreReplaces(int N){
    int size = 0;
    char* str = (char*)calloc(size, sizeof(char));
    do{
        size += 1;
        str = (char*)realloc(str, size * sizeof(char));
        str[size - 1] = 48 + N % 10;
    } while ((N /= 10) > 0);
    char* reverseStr = (char*)calloc(size, sizeof(char));
    for (int i = 0; i < size; i += 1){
        reverseStr[i] = str[size - i - 1];
    }
    free(str);
    int index = 0;
    int* arr = (int*)calloc(10, sizeof(int));
    for (int i = 0; i < size; i += 1){
        index = (int)reverseStr[i] - 48;
        arr[index] += 1;
    }
    free(reverseStr);
    for (int i = 0; i < 10; i += 1){
        if (arr[i] > 1){
            free(arr);
            return 1;
        }
    }
    free(arr);
    return 0;
}

