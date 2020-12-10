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
        throw Exception("i is greater then the size of the vector", INVALID_INPUT);
    }
    return data[i];
}
Vector::Vector(const Vector &origin)
{
    size = origin.size;
    data = new int[size];
     for (int i = 0; i < size; i++)
    {
        data[i] = origin.data[i];
    }
}
Vector& Vector::operator=(const Vector &origin)
{
    delete[] data;
    size = origin.size;
    data = new int[size];
     for (int i = 0; i < size; i++)
    {
        data[i] = origin.data[i];
    }
    return *this;
}


Vector::~Vector()
{
    delete[] data;
}
