#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits>
using namespace std;

#define MAX 1000010

typedef struct Node {
    int data;
    int counter;
    struct Node *next;
} node;

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

class Queap {
public:
	Queap();
	void enqueap(int);
	int dequeap();
	int min();
private:
    Stack *in;
    Stack *out;
    Stack *Pin;
    Stack *Pout;
    Stack *cntin;
    Stack *cntout;
};

Queap::Queap() {
	in = new Stack();
	out = new Stack();
	Pin = new Stack();
	Pout = new Stack();
	cntin = new Stack();
	cntout = new Stack();
}

void Queap::enqueap(int value) {
	in->push(value);
	if (Pin->empty()){
		Pin->push(value);
		cntin->push(1);
	}
	else{
		if (Pin->top() >= value){
			Pin->push(value);
			cntin->push(1);
		}
		else{
			int tmp = cntin->pop();
			tmp++;
			cntin->push(tmp);
		}
	}
}

int Queap::dequeap() {
	int p;
	int ret;
	int counter;
	if(out->empty() && in->empty()){
		return 0;
	}
	if(out->empty()){
		while(!in->empty()){
			p = in->pop();
			counter = cntin->pop();
			if(!(--counter)){
				Pin->pop();
			}
			else{
				cntin->push(counter);
			}
			out->push(p);
			if (Pout->empty()){
				Pout->push(p);
				cntout->push(1);
			}
			else{
				if (Pout->top() >= p){
					Pout->push(p);
					cntout->push(1);
				}
				else{
					int tmp = cntout->pop();
					tmp++;
					cntout->push(tmp);
				}
			}			
		}
	}
	ret = out->pop();
	counter = cntout->pop();
	if(!(--counter)){
		Pout->pop();
	}
	else{
		cntout->push(counter);
	}	
	return ret;
}

int Queap::min() {
	if (Pin->empty() && !Pout->empty()){
		return Pout->top();
	}
	else if (!Pin->empty() && Pout->empty()){
		return Pin->top();
	}
	else if (Pin->empty() && Pout->empty()){
		return 0;
	}
	else{
		if (Pin->top() < Pout->top())
			return Pin->top();
		else
			return Pout->top();
	}
}

int main() {
	Queap *queap = new Queap();
	int n;
	int x;
	int ret;
	char input;
	scanf("%d\n", &n);
	for (int i=0; i<n; i++){
        scanf("%c", &input);
        while (input != 'E' && input != 'D' && input != 'M'){
        	scanf("%c", &input);
        }
        switch(input){
        	case 'E':
        		scanf("%d\n", &x);
        		queap->enqueap(x);
        		break;
        		
        	case 'D':
        		ret = queap->dequeap();
        		printf("%d\n", ret);
        		break;
        	
        	case 'M':
        		ret = queap->min();
        		printf("%d\n", ret);
        		break;
        }
	}
	return 0;
}