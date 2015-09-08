#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define N 1000010
#define Dim 2

using namespace std;
long int out = 0; // final answer
int y[N]; // y-axis

// compare function
static int compare(const void* p1, const void* p2) {
  int* arr1 = (int*)p1;
  int* arr2 = (int*)p2;
  int diff1 = arr1[0] - arr2[0];
  if (diff1) return diff1;
  return arr1[1] - arr2[1];
}

void merge(int y[], int tmp[], int l, int mid, int r){
    int i=l, j=mid, k=l;
    while ((i <= mid - 1) && (j <= r)){
        if (y[i] <= y[j]){
            tmp[k++] = y[i++];
            out += (r-j+1);     
        }
        else{
            tmp[k++] = y[j++];                    
        }
    }
    while (i <= mid - 1)
        tmp[k++] = y[i++];
    while (j <= r)
        tmp[k++] = y[j++];
    for (i = l; i <= r; i++)
        y[i] = tmp[i];
}

void mergeAndCnt(int y[], int tmp[], int l, int r){
    int mid;
    if (r > l){
        mid = (l+r)/2;
        mergeAndCnt(y, tmp, l, mid);
        mergeAndCnt(y, tmp, mid+1, r);
        merge(y, tmp, l, mid+1, r);
    }
}

void inversion_count(int y[], int n){
    int *tmp = new int [n];
    mergeAndCnt(y, tmp, 0, n-1);
}

int main(int argc, char *argv[]){
  int a[N][Dim] = {0}, n;
  scanf("%d", &n);
  for (int i=0; i<n; i++){
    scanf("%d %d\n", &a[i][0], &a[i][1]);
  }
  // using std::qsort with self-designed comparing function 
  // to sort 2d array with respect to the first column
  qsort(a, n, 2*sizeof(int), compare);
  for (int i=0; i<n; i++){
    y[i] = a[i][1];
  }
  inversion_count(y, n);
  printf("%ld\n", out);
  return 0;
}