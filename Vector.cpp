#include "Vector.h"
#include "Exception.h"

using namespace DS;

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
        throw Exception("i is greater then the size of the vector", FAILURE);
    }
    return data[i];
}

Vector::~Vector()
{
    delete[] data;
}
