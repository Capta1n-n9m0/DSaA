#include<stdio.h>
int i,l;
int search(int ,int *,int);
int main(){
    int n,m;
    // Read size of array
    scanf("%d",&n);
    int a[n];
    // Read elements of array
    for(i=0;i<n;i++){scanf("%d",&a[i]);}
    // Read number to look for
    scanf("%d",&m);
    // Call searching function
    search(n,a,m);
    return 0;
}
// n - read size of an array
// a - pointer to start of an array
// m - number to look for
int search(int n,int *a,int m){
    // linear search, works for unsorted array
    for(i=0;i<n;i++){
        if(m==a[i]){
            l=1;
            break;
        }
    }
    // l - finding flag.
    if(l==1){
        printf("%d is present in the array",m);
    }
    else{
        printf("%d is not present in the array",m);
    }
}