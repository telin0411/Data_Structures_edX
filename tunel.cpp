#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct NodeS {
    int data;
    struct NodeS *next;
    struct NodeS *prev;
} nodes;

typedef struct NodeP {
    int data;
    int cnt;
    struct NodeP *next;
    struct NodeP *prev;
} nodep;

int main() {
    nodes *headS = new nodes;
    nodes *tmp1;
    nodes *tailS = new nodes;
    tailS = headS;
    nodep *headP = new nodep;
    nodep *tmp2;
    nodep *tailP = new nodep;
    tailP = headP;
    char input;
    int x, k;

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%c", &input);
        while (!('A'<input && input <'Z')){
        	scanf("%c", &input);
        }
        switch (input) {
            case 'E':
                scanf("%d", &x);
                tmp1 = (nodes*)malloc(sizeof(nodes));
                tmp1->data = x;
                tailS->next = tmp1; 
                tmp1->prev = tailS; 
                tailS = tmp1;

                k = 1;
                tmp2 = (nodep*)malloc(sizeof(nodep));;
                tailP->next = tmp2; 
                tmp2->prev = tailP; 
                tailP = tmp2;
                while ((tailP->prev != headP) && (tailP->prev->data <= x)) {
                    k += tailP->prev->cnt;
                    tmp2 = tailP->prev;
                    tmp2->prev->next = tailP;
                    tailP->prev = tmp2->prev;
                    delete tmp2;
                }
                tailP->cnt = k;
                tailP->data = x;
                break;
            case 'D':
                printf("%d\n", headS->next->data);
                headS = headS->next;
                delete headS->prev;
                if (!(--(headP->next)->cnt)) {
                    headP = headP->next;
                    delete headP->prev;
                }
                break;
            case 'M':
                printf("%d\n", headP->next->data);
                break;
        }
    }
    return 0;
}