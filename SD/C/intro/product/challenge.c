#include "challenge.h"
#include <stdio.h>

int FindSmallestNumberThatIsRepeatedKTimes(
            int* array, int size, int k, int* smallestNumber)
{
    
    if (array == NULL || size < 0 || k < 0 || smallestNumber == NULL)
    {
        return -1;
    }
    int count = 0;
    int smallest = array[0];
    
    for (int i = 0; i < size; i++)
    {
        count = 0;
        for (int j = 0; j < size; j++)
        {
            if (array[i] == array[j])
            {
                count++;
            }
        }
        if (count == k && array[i] < smallest)
        {
            smallest = array[i];
        }
    }
    if(smallest == -1)
    {
        return -1;
    }
    *smallestNumber = smallest;
    return 0;
}

int ComputeDifferenceBetweenMaxAndMinSumOfKElements_0(
            int* array, int size, int k, int* difference)
{
    if (array == NULL || size < 0 || k < 0 || difference == NULL)
    {
        return -1;
    }
    
    return -1;
}

int ComputeDifferenceBetweenMaxAndMinSumOfKElements_1(
            int* array, int size, int k, int* difference)
{
    return -1;
}

int ComputeDifferenceBetweenMaxAndMinSumOfKElements_2(
            int* array, int size, int k, int* difference)
{
    return -1;
}

int ComputeDifferenceBetweenMaxAndMinSumOfKElements_3(
            int* array, int size, int k, int* difference)
{
    return -1;
}
