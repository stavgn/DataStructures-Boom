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

    Vector::Vector(int size) : size(size), data(new int[size])
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = 0;
        }
    }

    void Vector::insert(int i, int val)
    {
        data[i] = val;
    }

    int &Vector::operator[](int i)
    {
        if (i >= size)
        {
            throw Exception("i is greater then the size of the vector", INVALID_INPUT);
        }
        return data[i];
    }

    Vector::~Vector()
    {
        delete data;
    }

} // namespace DS

#endif
