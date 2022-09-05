#include <stdio.h>

void printCross(int size)
{
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if(i == j || i + j == size - 1){
                printf("*");
            }else printf(" ");
            
        }
        printf("\n");
    }
    printf("\n");
}

void printPlus(int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(j == (size + 1) / 2 - 1 || i == (size + 1) / 2 - 1){
                printf("*");
            }else printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    printCross(9);
    printPlus(5);
    return 0;
}
 