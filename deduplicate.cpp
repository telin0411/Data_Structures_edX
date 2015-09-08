#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define TABLE_SIZE 10000000

using namespace std;

unsigned long DJB2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class HashEntry {
private:
  unsigned long key;
  int value;
public:
  HashEntry(unsigned long key, int value) {
    this->key = key;
    this->value = value;
  } 
  unsigned long getKey() {return key;} 
  int getValue() {return value;}
};

class HashMap {
private:
  HashEntry **table;
public:
  HashMap() {
    table = new HashEntry*[TABLE_SIZE];
    for (int i=0; i<TABLE_SIZE; i++)
      table[i] = NULL;
  }
  int get(unsigned long key){
    int Hash = (key % TABLE_SIZE);
    while (table[Hash] != NULL && table[Hash]->getKey() != key)
      Hash = (Hash + 1) % TABLE_SIZE;
    if (table[Hash] == NULL)
      return -1;
    else
      return table[Hash]->getValue();
  }
  void put(unsigned long key, int value) {
    int Hash = (key % TABLE_SIZE);
    while (table[Hash] != NULL && table[Hash]->getKey() != key)
      Hash = (Hash + 1) % TABLE_SIZE;
    if (table[Hash] != NULL)
      delete table[Hash];
    table[Hash] = new HashEntry(key, value);
  }
  ~HashMap() {
    for (int i=0; i<TABLE_SIZE; i++)
      if (table[i] != NULL)
        delete table[i];
    delete[] table;
  }  
};

int main() {
  int n;
  int val;
  HashMap *map = new HashMap();
  scanf("%d", &n);
  unsigned char **arr = (unsigned char**)calloc(n,sizeof(unsigned char*));
  
  for (int i=0; i <n; i++ ) {
    arr[i] = (unsigned char*)calloc(50, sizeof(unsigned char));
    scanf("%s", arr[i]);
    //cout << map->get(DJB2(arr[i])) << endl;
    if ( map->get(DJB2(arr[i])) == -1 ){
      map->put(DJB2(arr[i]), 1);
    }
    else{
      val = map->get(DJB2(arr[i]));
      val++;
      map->put(DJB2(arr[i]), val);
    }
    //cout << map->get(DJB2(arr[i])) << endl;
    if ( map->get(DJB2(arr[i])) == 2 )
      printf("%s\n", arr[i]);
  }
  for (int i=0; i<n; i++) {
    free(arr[i]);
  }
  free(arr);
  return 0;
}