#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define L 100000000
#define N 75000000

using namespace std;

char out[L+10];
int printcnt = 0;

typedef struct Node{
  char cval;
  struct Node *next;
  struct Node *prev;
} List;

void construct_board(char *z, int n, List* head, List* tail){
  tail->next = NULL;
  tail->prev = head;
  head->next = tail;
  head->prev = NULL;
  head->cval = '-';
  tail->cval = '-';
  List *last = new List();
  last = head;
  for (int i=0; i<n; i++){
    List *newNode = new List();
    newNode->cval = z[i];
    newNode->next = last->next;
    newNode->prev = last;    
    last->next->prev = newNode;
    last->next = newNode;
    last = newNode;
  }
}

void insert_gem(int pos, char gem, List* head, List* tail){
  List *last = new List();
  List *newNode = new List();
  last = head;
  for(int i=-1; i<pos; i++){
    last = last->next;
  }
  newNode->cval = gem;
  newNode->next = last;
  newNode->prev = last->prev;  
  last->prev->next = newNode;
  last->prev = newNode;
}

void cancel_out(int pos, List* head, List* tail){
  List *gem1 = new List();
  List *gem2 = new List();
  List *gem3 = new List();
  List *gem4 = new List();
  List *last = new List();
  List *start = new List();
  List *end = new List();
  last = head;
  start = head;
  end = tail;
  int cancel = 1;
  int cnt;
  for(int i=-1; i<pos-2; i++){
    last = last->next;
  }
  start = last;
  end = last;  
  for(int i=0; i<4; i++){
    if (end->next != tail)
      end = end->next;
  }
  while (cancel==1 && last != tail){
    cancel = 0;
    cnt = 1;
    while(last != end){
      last = last->next;
      if(last->prev->cval==last->cval)
        cnt++;
      else
        cnt = 1;
      if (cnt == 3){ // Starting to cancel out the zuma gems
        cancel = 1;
        if(last->cval==last->next->cval){
          cnt++;
          last = last->next;
        }
        if (cnt == 3){
          gem3 = last;
          gem2 = gem3->prev;
          gem1 = gem2->prev;
          gem1->prev->next = gem3->next;
          gem3->next->prev = gem1->prev;
          delete gem1;
          delete gem2;
          delete gem3;
          last = last->next;
        }
        else{
          gem4 = last;
          gem3 = gem4->prev;
          gem2 = gem3->prev;
          gem1 = gem2->prev;
          gem1->prev->next = gem4->next;
          gem4->next->prev = gem1->prev;
          delete gem1;
          delete gem2;
          delete gem3;
          delete gem4;                    
          last = last->next;                    
        }
        break;
      }
    }
    if (cancel==1 && last != tail){
      start = last;
      for(int i=0; i<2; i++){
        if (start->prev != head)
          start = start->prev;
      }
      end = last;
      int j = 0;
      if (j++<1 && end->next != tail)
        end = end->next;
      last = start;
    }  
  }
}

void print_board(List* head, List* tail){
  List *last = new List();
  last = head->next;
  if(head->next==tail){
    printf("-\n");
  }
  else{
    while(last->next != NULL){
      printf("%c", last->cval);
      last = last->next;
    }
    printf("\n");
  }
}

void ans(List* head, List* tail){
  List *last = new List();
  last = head->next;
  if(head->next==tail){
    out[printcnt++] = '-';
    out[printcnt++] = '\n';
  }
  else{
    while(last->next != NULL){
      out[printcnt++] = last->cval;
      last = last->next;
    }
    out[printcnt++] = '\n';
  }  
}

int main(int argc, char *argv[]){
  char in[20000];
  int n;
  scanf("%s", in);
  List *head = new List();
  List *tail = new List();
  construct_board(in, strlen(in), head, tail);
  int rnd=0;
  scanf("%d\n", &n);
  for (rnd=0; rnd<n; rnd++){
    int pos;
    char gem;
    scanf("%d %c", &pos, &gem);
    insert_gem(pos, gem, head, tail);
    cancel_out(pos, head, tail);
    //print_board(head, tail);
    ans(head, tail);
  }
  for(int i=0; i<printcnt; i++){
    printf("%c", out[i]);
  }
  return 0;
}