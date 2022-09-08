#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "challenge.h"
#include "parsedata.h"

#define MAX_ARRAY_SIZE 100000

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Please provide argument to select assignment.\n");
        return -1;
    }
    //char selectedAssignment = atoi(argv[1]);

    int N = 0;
    int array[MAX_ARRAY_SIZE];
    int K = 0;
    ParseData(argv[1], &N, array, &K);
    //print N, array and K
    printf("N: %i\n", N);
    for(int i = 0; i < N; i++){
        printf("array[%i]: %i\n", i, array[i]);
    }
    printf("K: %i\n", K);


    // if (selectedAssignment == 1)
    // {
    //     int smallestNumber = 0;
    //     FindSmallestNumberThatIsRepeatedKTimes( /* TODO: fill in parameters */ );

    //     printf("%d\n", smallestNumber);
    // }
    // else if (selectedAssignment == 2)
    // {
    //     int difference = 0;
    //     ComputeDifferenceBetweenMaxAndMinSumOfKElements_0( /* TODO: fill in parameters */ );

    //     printf("%d\n", difference);
    // }
    // else if (selectedAssignment == 31)
    // {
    //     int difference = 0;
    //     ComputeDifferenceBetweenMaxAndMinSumOfKElements_1( /* TODO: fill in parameters */ );
    //     printf("%d\n", difference);
    // }
    // else if (selectedAssignment == 32)
    // {
    //     int difference = 0;
    //     ComputeDifferenceBetweenMaxAndMinSumOfKElements_2( /* TODO: fill in parameters */ );
    //     printf("%d\n", difference);
    // }
    // else if (selectedAssignment == 33)
    // {
    //     int difference = 0;
    //     ComputeDifferenceBetweenMaxAndMinSumOfKElements_3( /* TODO: fill in parameters */ );
    //     printf("%d\n", difference);
    // }
    // else
    // {
    //     printf("Error: Unknown assignment: %d\n", selectedAssignment);
    // }

    return 0;
}
