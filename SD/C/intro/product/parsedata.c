#include "parsedata.h"
#include <stdio.h>

int ParseData(char inputname[], int* N, int arr[], int* K)
{
    //read file file
    FILE *file = fopen(inputname, "r");
    if(file == NULL){
        return -1;
    }
    if(fscanf(file, "%i", N) != 1){
        fclose(file);
        return -1;
    }
    for(int i = 0; i < *N; i++){
        if(fscanf(file, "%i", &arr[i]) != 1){
            fclose(file);
            return -1;
        }
    }
    if(fscanf(file, "%i", K) != 1){
        fclose(file);
        return -1;
    }
    fclose(file);
    return 1;
    
}
