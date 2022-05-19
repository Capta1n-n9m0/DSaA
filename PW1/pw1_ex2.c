#include <stdio.h>
int main(){
    int i,j=0,k=0,n;
    printf("\n\n Separate odd and even integers in array:\n");
    printf("------------------------------------------------------\n");
    printf("Input the number of elements to be stored in the array :");
    scanf("%d%*c",&n);
    int arr1[n], arr2[n], arr3[n];
    printf("Input %d elements in the array :\n",n);
    for(i=0;i<n;i++){
        printf("element - %d : ", i);
        scanf("%d%*c", &arr1[i]);
    }
/* Loop to test if an element is odd or even.*/
    for(i = 0; i < n; i++){
/* Range them into the two arrays: arr2 and arr3 */
        // arr2 - odds
        // arr3 - evens
        if(arr1[i]%2) arr2[j++] = arr1[i];
        else arr3[k++] = arr1[i];
    }
/* Print both arrays*/
    printf("\nOdds: ");
    for(i = 0; i < j; i++){
        printf("%d ", arr2[i]);
    }
    printf("\nEvens: ");
    for(i = 0; i < k; i++){
        printf("%d ", arr3[i]);
    }
    puts("");
    return 0;
}