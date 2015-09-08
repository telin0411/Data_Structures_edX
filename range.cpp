#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define N 500005

using namespace std;

int a[N];

int compare(const void *a, const void *b){
    int *aa = (int*)a;
    int *bb = (int*)b;
    return (*aa) - (*bb);
}

int BinSearch(int l, int r, int num){
    int mid, start=l, end=r;
    while(start <= end){
        mid = start + ((end - start) >> 1);
        if (a[mid] >= num)
            end = mid - 1;
        else
            start = mid + 1;
    }
    return start;
}

int main(){
    
    int n, m, l, r, i, retl, retr, out;
    scanf("%d %d\n", &n, &m);
    for (i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    // http://www.cnblogs.com/CCBB/archive/2010/01/15/1648827.html
	// std::qsort with self-defined function
    qsort(a, n, sizeof(int), compare);
    for(i = 0; i < m; i++){
        scanf("%d %d", &l, &r);
        retl = BinSearch(0, n-1, l);
        retr = BinSearch(0, n-1, r);
        out  = retr - retl;
        if(a[retr] == r)
            out++;
        if (out < 0)
            out = 0;
        printf("%d\n", out);
    }
}