#include <stdio.h>
#include <stdlib.h> 

#define L 500005 

int a[L]; 

int compare(const void *a, const void *b)
{
    int *pa = (int*)a;
    int *pb = (int*)b;
    return (*pa) - (*pb);
} 

void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
} 

int find(int begin, int end, int ac)
{
    int mid, left = begin, right = end;
    while (left <= right)
    {
        mid = left + ((right - left) >> 1);
        if (a[mid] >= ac) right = mid - 1;
        else left = mid + 1;
    }
    return left;
} 

int main()
{
    int n, m, i;
    scanf("%d %d\n", &n, &m); 

    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }  

    qsort(a, n, sizeof(int), compare); 

    for (i = 0; i < m; i++)
    {
        int l, r, ans, lf, rt;
        scanf("%d %d", &l, &r); 

        //make sure l <= r
        if (l > r)
        {
            swap(l, r);
        } 

        rt = find(0, n - 1, r);
        lf = find(0, n - 1, l);
        ans = rt - lf;
        if (a[rt] == r) ans++;
        if (ans < 0) ans = 0; 

        printf("%d\n", ans);
    }
}