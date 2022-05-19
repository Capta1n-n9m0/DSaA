#include <stdio.h>

int main() {
    int i, n, sum = 0;
    printf("\n\n Find the sum of all elements of array:\n");
    printf("--------------------------------------\n");
    printf("Input the number of elements to be stored in the array :");
    scanf("%d%*c", &n);
    printf("Input %d elements in the array :\n", n);
/* Input the elements of the array*/
    int a[n];
    for(i = 0; i < n; i++)
        scanf("%d%*c", &a[i]);
/* Find the sum of all array’s elements*/
    for(i = 0; i < n; i++)
        sum += a[i];
    printf("Sum of all elements stored in the array is : %d\n\n", sum);
    return 0;
}