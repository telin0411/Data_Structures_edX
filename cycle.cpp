#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 997
#define R 26
#define MMAX 100005
#define DIGIT(S, i) ((S)[i] - 'A')

typedef long long HashCode;

bool check1by1(char* P, char* T, size_t i) {
    for (size_t m = strlen(P), j = 0; j < m; j++, i++) {
        if (P[j] != T[i]) return false;
    }
    return true;
}

HashCode prepareDm(size_t m) {
    HashCode Dm = 1;
    for (size_t i = 1; i < m; i++) 
        Dm = (Dm*R) % M;
    return Dm;
}

void updateHash(HashCode& hashT, char* T, size_t m, size_t k, HashCode Dm) {
    hashT = (hashT - DIGIT(T, k - 1)*Dm) % M;
    hashT = (hashT*R + DIGIT(T, k + m - 1)) % M;
    if (hashT < 0) hashT += M;
}

bool match(char* P, char* T) {
    size_t m = strlen(P), n = strlen(T);
    HashCode Dm, hashP = 0, hashT = 0;
    Dm = prepareDm(m);
    for (size_t i = 0; i < m; i++) {
        hashP = (hashP*R + DIGIT(P, i)) % M;
        hashT = (hashT*R + DIGIT(T, i)) % M;
    }
    for (size_t k = 0;;) {
        if (hashT == hashP && check1by1(P, T, k)) return true;
        if (++k>n - m) return false;
        else updateHash(hashT, T, m, k, Dm);
    }
}

int main() {
    char* s1 = (char*)malloc(sizeof(char)*(MMAX));
    char* s2 = (char*)malloc(sizeof(char)*(MMAX * 2));

    do {
        if (scanf("%s %s", s1, s2) == EOF) break;
        int n1, n2;
        n1 = strlen(s1); n2 = strlen(s2);
        if (n1 != n2) printf("NO\n");
        else {
            int i;
            for (i = n2; i < n2 * 2 - 1; i++) s2[i] = s2[i - n2];
            s2[i] = '\0';
            if (match(s1, s2)) printf("YES\n");
            else printf("NO\n");
        }
    } while (true);
    return 0;
}