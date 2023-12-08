#ifndef UF_H
#define UF_H

#include "head.h"

class UF{
private:
    int *fa, n;

public:

    UF(int);

    ~UF();

    int find(int);

    bool same(int, int);

    void merge(int, int);
};

#endif