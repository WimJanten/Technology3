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

void merge(int arr[], int leftStartIndex, int m, int r)
{
    int indexLeft;
    int indexRight;
    int indexMerged;
    int leftSize = m - leftStartIndex + 1;
    int rightSize = r - m;
 
    int L[n1], R[n2];

    for (indexLeft = 0; indexLeft < n1; indexLeft++)
        L[indexLeft] = arr[leftStartIndex + indexLeft];
    for (indexRight = 0; indexRight < n2; indexRight++)
        R[indexRight] = arr[m + 1 + indexRight];
         
    indexLeft = 0;
    indexRight = 0;
    indexMerged = leftStartIndex;
    while (indexLeft < n1 && indexRight < n2) {
        if (L[indexLeft] <= R[indexRight]) {
            arr[indexMerged] = L[indexLeft];
            indexLeft++;
        }
        else {
            arr[indexMerged] = R[indexRight];
            indexRight++;
        }
        indexMerged++;
    }

    while (indexLeft < n1) {
        arr[indexMerged] = L[indexLeft];
        indexLeft++;
        indexMerged++;
    }

    while (indexRight < n2) {
        arr[indexMerged] = R[indexRight];
        indexRight++;
        indexMerged++;
    }
}
 

int MergeSortArray(int arr[], int leftStartIndex, int rightStartIndex)
{
    if(arr == NULL){
        return -1;
    }
    if (leftStartIndex < rightStartIndex) {

        int currentMiddle = leftStartIndex + (rightStartIndex - leftStartIndex) / 2;

        MergeSortArray(arr, leftStartIndex, currentMiddle);
        MergeSortArray(arr, currentMiddle + 1, rightStartIndex);

        merge(arr, leftStartIndex, currentMiddle, rightStartIndex);
    }
    return 0;
}

int ComputeDifferenceBetweenMaxAndMinSumOfKElements_1(
    int *array, int size, int k, int *difference)
{
    if (array == NULL || size < 0 || k < 0 || difference == NULL)
    {
        return -1;
    }

    MergeSortArray(array, 0, size - 1);

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
