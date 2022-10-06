#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "parsedata.h"
#include "challenge.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Please provide argument to select assignment.\n");
        return -1;
    }
    char selectedAssignment = atoi(argv[1]);

    int N = 0;
    GetSize(&N);
    int arr[N];
    GetArray(arr, N);
    int K = 0;
    GetK(&K);


    if (selectedAssignment == 1)
    {
        int smallestNumber = 0;
        FindSmallestNumberThatIsRepeatedKTimes(arr, N, K, &smallestNumber);

        printf("%d\n", smallestNumber);
    }
    else if (selectedAssignment == 2)
    {
        int difference = 0;
        ComputeDifferenceBetweenMaxAndMinSumOfKElements_0(arr, N, K, &difference);  

        printf("%d\n", difference);
    }
    else if (selectedAssignment == 31)
    {
        int difference = 0;
        ComputeDifferenceBetweenMaxAndMinSumOfKElements_1(arr, N, K, &difference);
        printf("%d\n", difference);
    }
    else if (selectedAssignment == 32)
    {
        int difference = 0;
        //ComputeDifferenceBetweenMaxAndMinSumOfKElements_2( /* TODO: fill in parameters */ );
        printf("%d\n", difference);
    }
    else if (selectedAssignment == 33)
    {
        int difference = 0;
        //ComputeDifferenceBetweenMaxAndMinSumOfKElements_3( /* TODO: fill in parameters */ );
        printf("%d\n", difference);
    }
    else
    {
        printf("Error: Unknown assignment: %d\n", selectedAssignment);
    }

    return 0;
}
