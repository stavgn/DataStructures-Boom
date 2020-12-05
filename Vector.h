#ifndef VECTOR_H
#define VECTOR_H

#include "./Exception.h"

namespace DS
{
    class Vector
    {
    public:
        int *data;
        int size;
        Vector(int size);
        ~Vector();
        void insert(int i, int val);
        int &operator[](int);
    };

    
} // namespace DS

#endif
