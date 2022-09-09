#include "parsedata.h"
#include <stdio.h>

int GetSize(int *N)
{
    if (N == NULL)
    {
        return -1;
    }

    if (scanf("%i", N) != 1)
    {
        return -1;
    }
    return 0;
}

int GetArray(int arr[], int size){

    if(arr == NULL || size < 0)
    {
        return -1;
    }
    for(int i = 0; i < size; i++)
    {
        if(scanf("%i", &arr[i]) != 1)
        {
            return -1;
        }
    }
    return 0;
}

int GetK(int *K)
{
    if (K == NULL)
    {
        return -1;
    }

    if (scanf("%i", K) != 1)
    {
        return -1;
    }
    return 0;
}
