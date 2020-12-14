#ifndef VECTOR_H
#define VECTOR_H

#include "./Exception.h"

namespace DS
{
    class Vector
    {
    public:
        int size;
        int *data;
        Vector(int size);
        ~Vector();
        Vector (const Vector &origin);
        Vector& operator=(const Vector &origin);
        void insert(int i, int val);
        int &operator[](int);
    };

    
} // namespace DS

#endif
