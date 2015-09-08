#include <iostream>
//#include <list>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000002
using namespace std;

/* Type def of Nodes */
typedef struct Node {
    int data;
    struct Node *next;
} node;

/**
  Class of Self-designed Stack
**/
class Stack {
public:
	Stack();
	bool empty();
	void push(int);
	int pop();
	int top();
private:
	int size;
  node* tops;
};

Stack::Stack() {
	tops = NULL;
	size = 0;
}

bool Stack::empty() {
	return tops==NULL;
}

void Stack::push(int value) {
	node *elem = new node;
	elem->data = value;
	elem->next = tops;
	tops = elem;
	size++;
}

int Stack::pop() {
	int value;
	node* tmp = tops;
	value = tmp->data;
	tops = tmp->next;
	delete tmp;
	size--;
	return value;
}

int Stack::top() {
	return tops->data;
}

int paths; // the path tmp counter
int maxPaths = 0; // the answer

/**
  Class of Self-designed Graph
**/
class AdjListNode {
    int v;
public:
    AdjListNode(int _v)  { v = _v;}
    int getV()       {  return v;  }
};

typedef struct listnode{
    node* adjl;
    int v;
    int size;
} lists;

class Graph {
    int V;
    lists *adjlist;
    void topologicalSortUtil(int v, bool visited[], Stack *tpsortStack);
public:
    Graph(int V);
    void addEdge(int u, int v);
    void longestPath();
};
 
Graph::Graph(int V) {
    this->V = V;
    adjlist = (lists*)malloc(V*sizeof(lists));
    //cout << "Villages: " << V << endl;
    for (int i=0; i<V; i++) {
      adjlist[i].v = i;
      adjlist[i].size = 0;
      adjlist[i].adjl = new node;
      adjlist[i].adjl->data = i;
    }
}
 
void Graph::addEdge(int u, int v) {
    AdjListNode nodes(v);
    int s = adjlist[u].size;
    node* tmp1 = new node;  
    s++; 
    adjlist[u].size = s;
    node* tmp = adjlist[u].adjl;
    while(tmp->next){
      tmp = tmp->next;
    }
    tmp->next = tmp1;
    tmp->next->data = v;
}

void Graph::topologicalSortUtil(int v, bool visited[], Stack *tpsortStack) {
    visited[v] = true;
    int s = adjlist[v].size;
    int n, next;
    node* tmp = adjlist[v].adjl;
    //cout << v << " size = " << s << endl;
    tmp = tmp->next;
    for (int i=0; i<s; i++) {        
        n = tmp->data;
        //cout << v << n << endl;
        if (!visited[n]){
            topologicalSortUtil(n, visited, tpsortStack);
        }
        tmp = tmp->next;
    }    
    tpsortStack->push(v);
}

void Graph::longestPath() {
    Stack *tpsortStack = new Stack();
    int dist[V];
 
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    int s;
    for (int i = 0; i < V; i++){
        if (visited[i] == false){
            topologicalSortUtil(i, visited, tpsortStack);
        }
    }
    
    bool *visited2 = new bool[V];
    for (int i = 1; i < V; i++)
        visited2[i] = false;
    visited2[0] = true;
    
    /** DFS **/
    while (tpsortStack->empty() == false) {
        int u = tpsortStack->top();
        paths = 0;
        tpsortStack->pop();        
        if (visited2[u] == false){
          Stack *dfsStack = new Stack();
          dfsStack->push(u);
          visited2[u] = true;
          while(dfsStack->empty()==false){
    	      int x = dfsStack->top();
    	      dfsStack->pop();
    	      paths++;
            int s = adjlist[x].size;
            int next, n;
            node* tmp = adjlist[x].adjl;
            for (int i=0; i<s; i++) {
              n = tmp->next->data;
              if (!visited2[n]){
                dfsStack->push(n);
                visited2[n] = true;
                tmp = tmp->next;
              }              
            }
          }
        }
        if (paths >= maxPaths) {
          maxPaths = paths;
        }
    }
}
 
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Graph g(n+1);
    int x, y;    
    for (int i=0; i<m; i++){
      scanf("%d %d", &x, &y);    
      g.addEdge(x, y);    
    }
    g.longestPath(); 
    cout << maxPaths << endl;
    return 0;
}