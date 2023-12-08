#include "head.h"
#include "UF.h"

UF:: UF(int sz){
    fa = new int [n = sz];
    memset(fa, 0, sizeof(fa));
    for(int i = 1; i < sz; i ++) fa[i] = i;
}

UF:: ~UF(){
    delete fa;   
}

int UF:: find(int x){
    if(fa[x] == x) return x;
    else return fa[x] = find(fa[x]);
}

bool UF:: same(int x, int y){
    return find(x) == find(y);
}

void UF:: merge(int x, int y){
    fa[find(x)] = find(y);
}