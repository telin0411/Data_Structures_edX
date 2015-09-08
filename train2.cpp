#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include "assert.h"

#define MAX 1600005

using namespace std;

int ans[MAX];
int cnt = 0;

template <class T>
class stack {
    T* data_;
    int capacity_;
    int size_;

public:

    stack(int default_size = 4) {
        data_ = new T[default_size];
        capacity_ = default_size;
        size_  = 0;
    }
    
    int size() {
        return size_;
    }

    void push(const T &d) {
        ensureSize();

        data_[size_] = d;
        size_++;
    }

    T pop() {
        assert(size_ > 0);
        size_ --;
        return data_[size_];
    }

    T top() {
        assert(size_ > 0);
        return data_[size_-1];
    }

private:
    void ensureSize() {
        if(capacity_ == size_) {
            capacity_ *= 2;
            T* newdata = new T[capacity_];
            for (int i = 0 ; i < size_; i++) {
                newdata[i] = data_[i];
            }

            delete[] data_;
            data_ = newdata;
        }
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int* data = new int[n]; 
    for(int i = 0; i < n; i++) {
        scanf("%d", &data[i]);
    }
    stack<int> outstack(n);
    bool result = true;
    int pushmax = 0;
    for(int i = 0; i < n && result; i++) {
        int cur = data[i];
        while(outstack.size() == 0 || pushmax < cur) {
            pushmax++;
            outstack.push(pushmax);
            ans[cnt++] = 1;
            if(outstack.size() > m) {
                result = false;
                break;
            }
        }
        if(outstack.top() == cur){
            outstack.pop();
            ans[cnt++] = 0;
        }
    }
    if(result && outstack.size() == 0){
        //printf("Yes");
        for (int x=0; x<cnt; x++){
        	if (ans[x] == 1)
        		printf("push\n");
        	else
        		printf("pop\n");
        }
    }
    else
        printf("No");

    delete[] data;
    return 0;
}