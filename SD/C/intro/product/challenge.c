#include "challenge.h"
#include <stdio.h>
#include <stdint.h>

int FindSmallestNumberThatIsRepeatedKTimes(
    int *array, int size, int k, int *smallestNumber)
{

    if (array == NULL || size < 0 || k < 0 || smallestNumber == NULL)
    {
        return -1;
    }
    int count = 0;
    int smallest = INT32_MAX;

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
    if (smallest == -1)
    {
        return -1;
    }
    *smallestNumber = smallest;
    return 0;
}

int BubbleSortArray(int *array, int size)
{
    if (array == NULL || size < 0)
    {
        return -1;
    }
    int temp = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    return 0;
}

int ComputeDifferenceBetweenMaxAndMinSumOfKElements_0(
    int *array, int size, int k, int *difference)
{
    if (array == NULL || size < 0 || k < 0 || difference == NULL)
    {
        return -1;
    }
    BubbleSortArray(array, size);
    int sum1 = 0;
    for (int i = 0; i < k; i++)
    {
        sum1 += array[i];
    }
    int sum2 = 0;
    for (int i = size - 1; i > size - k - 1; i--)
    {
        sum2 += array[i];
    }
    *difference = sum2 - sum1;

    return 0;
}


int ComputeDifferenceBetweenMaxAndMinSumOfKElements_1(
    int *array, int size, int k, int *difference)
{
    return -1;
}

int ComputeDifferenceBetweenMaxAndMinSumOfKElements_2(
    int *array, int size, int k, int *difference)
{
    return -1;
}

int ComputeDifferenceBetweenMaxAndMinSumOfKElements_3(
    int *array, int size, int k, int *difference)
{
    return -1;
}
