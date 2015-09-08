#include <iostream>
#include <cstdio>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
using namespace std;

const long long int MAX=4294967296;

typedef struct Task{
	long long int priority;
	char name[9];
} task;

class PriorityQueue{
private:
	int size;
	task keys[4000005];
	void percdown(int lo, int hi);
	void percup(int lo, int hi);
	void Heapify();
public:
	PriorityQueue(){size=0;}
	/*PriorityQueue(task* items, int n){
		keys = new task[n];
		for (int i=0; i<n; i++){
			keys[i] = items[i];
		}		
		size = n;
		Heapify();
	}*/
	void insert(task item);
	task delMin();
	int getsize(){return size;}
};

void PriorityQueue::percdown(int lo, int hi){
	int child = hi;
	while (child > lo){
		int parent = (child-1)/2;
		if (keys[child].priority < keys[parent].priority){
			task tmp = keys[child];
			keys[child] = keys[parent];
			keys[parent] = tmp;
			child = parent;
		}
		else if (keys[child].priority == keys[parent].priority && strcmp(keys[child].name, keys[parent].name) < 0){
			task tmp = keys[child];
			keys[child] = keys[parent];
			keys[parent] = tmp;
			child = parent;			
		}
		else{
			break;
		}
	}
	return;
}

void PriorityQueue::percup(int lo, int hi){
	int root = lo;
	while ((root*2)+1 <= hi){
		int lc = (root * 2) + 1;
		int rc = lc + 1;
		int swapidx = root;
		if (keys[swapidx].priority > keys[lc].priority){
			swapidx = lc;
		}
		else if ((keys[swapidx].priority == keys[lc].priority) && (strcmp(keys[swapidx].name, keys[lc].name)>0)){
			swapidx = lc;
		}
		if ((rc <= hi) && (keys[swapidx].priority > keys[rc].priority)){
			swapidx = rc;		
		}
		else if ((rc <= hi) && (keys[swapidx].priority == keys[rc].priority) && (strcmp(keys[swapidx].name, keys[rc].name)>0)){
			swapidx = rc;
		}
		if (swapidx != root){
			task tmp = keys[root];
			keys[root] = keys[swapidx];
			keys[swapidx] = tmp;
			root = swapidx;
		}
		else{
			break;
		}
	}
	return;
}

void PriorityQueue::insert(task item){
	keys[size++] = item;
	percdown(0, size-1);
	return;
}

task PriorityQueue::delMin(){
	if (size==0){
		task tmp;
		tmp.priority = MAX;
		return tmp;
	}
	int last = size-1;
	task tmp = keys[0];
	keys[0] = keys[last];
	keys[last] = tmp;
	percup(0, last-1);
	size--;
	return tmp;
}

void PriorityQueue::Heapify(){
	int mid = (size-2)/2;
	while (mid >= 0){
		percup(mid, size-1);
		--mid;
	}
	return;
}

int main() {
	// your code goes here
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	task in;
	task out;
	cin >> n;
	cin >> m;
	PriorityQueue* PQ = new PriorityQueue();
	task* inits;
	inits = new task[n];
	for(int i=0; i<n; i++){
		//scanf("%lld", &in.priority);
		cin >> in.priority;
		//scanf("%s", &in.name);
		cin >> in.name;
		PQ->insert(in);
		//inits[i] = in;
	}
	//PriorityQueue* PQ = new PriorityQueue(inits, n);	
	while (m--){
		if (PQ->getsize() > 0){
			out = PQ->delMin();
			//printf("%s\n", out.name);
			cout << out.name << endl;
			if (out.priority*2 < MAX){
				out.priority *= 2;
				PQ->insert(out);	
			}
		}
	}
	return 0;
}