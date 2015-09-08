#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define N 500005
int out[N];
int cnt = 0;
 
int search(int arr[], int x, int n){
	
    for (int i = 0; i < n; i++)
    	if (arr[i] == x)
        	return i;
	return -1;
}

void printPostOrder(int in[], int pre[], int n) {
   	int root = search(in, pre[0], n);
 
   	if (root != 0 && root != -1)
    	printPostOrder(in, pre+1, root);
 
   	if (root != n-1 && root != -1)
    	printPostOrder(in+root+1, pre+root+1, n-root-1);
   	
   	if (root != -1)
   		out[cnt++] = pre[0];
}

int main(){
	int n;
	int in[N];
	int pre[N];
	scanf("%d\n", &n);
	for(int i=0; i<n; i++){
		scanf("%d", &pre[i]);
	}
	for(int i=0; i<n; i++){
		scanf("%d", &in[i]);
	}
   	printPostOrder(in, pre, n);
   	if (cnt < n){
   		cout << "-1";
   	}
   	else{
   		for (int i=0; i<cnt; i++){
   			cout << out[i] << " ";
   		}
   	}
   	return 0;
}