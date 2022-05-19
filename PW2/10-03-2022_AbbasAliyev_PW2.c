#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *array, int n){
    printf("[ ");
    for(int i = 0; i < n; i++)
        printf("%d ", array[i]);
    puts("]");
}

int *merge(int *array1, int *array2, int n, int m){
    //n is size of array1, m is size of array2
    int *res = (int *)calloc(n+m, sizeof (int));

    // i count array1, j counts array2, k counts res
    int i = 0, j = 0, k = 0;

    while (i < n && j < m){
        if(array1[i] <= array2[j])
            res[k++] = array1[i++];
        else
            res[k++] = array2[j++];
    }

    while (i < n)
        res[k++] = array1[i++];
    while (j < m)
        res[k++] = array2[j++];

    return res;
}

void rotateLeftOnce(int *array, int n){
    int temp = array[0];
    for(int i = 0; i < n-1; i++)
        array[i] = array[i+1];
    array[n-1] = temp;
}

void rotateRightOnce(int *array, int n){
    int temp = array[n-1];
    for(int i = n-1; i > 0; i--)
        array[i] = array[i-1];
    array[0] = temp;
}

void rotateLeft(int *array, int n, int shift){
    if(shift < 0){
        for(int i = 0; i < (-shift) % n; i++)
            rotateRightOnce(array, n);
    } else{
        for(int i = 0; i < shift % n; i++)
            rotateLeftOnce(array, n);
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *array, int begin, int end){
    int random = (rand() % (end - begin)) + begin;
    swap(array + random, array + end);
    int pivot = array[end];
    int i = begin - 1;
    for(int j = begin; j <= end - 1; j++){
        if(array[j] < pivot)
            swap(array + ++i, array + j);
    }
    swap(array + i + 1, array + end);
    return i+1;
}

void quickSort(int *array, int begin, int end){
    if(begin < end){
        int pi = partition(array, begin, end);
        quickSort(array, begin, pi - 1);
        quickSort(array, pi + 1, end);
    }
}

void ex1(){
    puts("Exercise 1: Merge function.");
    puts("I did it my own way. It can be done without auxiliary array, but it is my way.");
    int arr1[5] = {2, 5, 7, 8, 12};
    int arr2[7] = {1, 3, 4, 5, 10, 13, 16};
    int n = 5, m = 7;
    int *res = merge(arr1, arr2, n, m);
    printf("[ ");
    for(int i = 0; i < n+m; i++)
        printf("%d ", res[i]);
    puts("]");
    puts("");
}

void ex2(){
    puts("Exercise 2: Array rotation function.");
    puts("I have in mind few ways to optimise it, but it is 11:30PM, so...");
    int arr1[5] = {2, 5, 7, 8, 12};
    int n = 5;
    printArray(arr1, n);
    rotateLeftOnce(arr1, n);
    printArray(arr1, n);
    rotateRightOnce(arr1, n);
    printArray(arr1, n);
    rotateRightOnce(arr1, n);
    printArray(arr1, n);
    puts("");
}

void ex3(){
    puts("Exercise 3: Quick sort");
    puts("Just a quick sort with a random pivot.");
    int arr[8] = {20, 3, 45, 500, 22, 13, 120, 95};
    int n = 8;
    printArray(arr, n);
    quickSort(arr, 0, n-1);
    printArray(arr, n);
    puts("");
}

// The function nicerec produces an exponential number of recursive calls, which can quickly eat up all memory.
// Base case of recursion is 1, if number is 1 or above, it will make 2 recursive calls
// It makes a call to itself at the start of the program, then at the end, in between the calls is displaying function.
// Output of a program reminds me of a binary tree for some reason, it looks like this to me:
//               4
//         _____/ \_____
//        /             \
//       3               3
//     _/ \_           _/ \_
//    /     \         /     \
//   2       2       2       2
//  / \     / \     / \     / \
// 1   1   1   1   1   1   1   1

void nicerec(int n){
    if(n > 0){
        nicerec(n - 1);
        printf("%d ", n);
        nicerec(n - 1);
    }
}

void ex4(){
    puts("Exercise 4: Exponential recursion");
    nicerec(4);
}

int main() {
    ex1();
    ex2();
    ex3();
    ex4();

    return 0;
}
