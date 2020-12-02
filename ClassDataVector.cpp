#include "./ClassDataVector.h";

using namespace DS;

ClassData::ClassData(int course, int classNum, int watchTime) : Vector(3)
{
    data[0] = course;
    data[1] = classNum;
    data[2] = watchTime;
}

bool ClassData::operator<(const ClassData &dv)
{
    return true;
}