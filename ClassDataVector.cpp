#include "./ClassDataVector.h"

using namespace DS;

ClassData::ClassData(int course, int classNum, int watchTime) : Vector(3)
{
    data[0] = course;
    data[1] = classNum;
    data[2] = watchTime;
}
ClassData& ClassData::operator=(const ClassData& origin)
{
    data[0] = origin.data[0];
    data[1] = origin.data[1];
    data[2] = origin.data[2];
    return *this;
}

int ClassData::course() const
{
    return data[0];
}

int ClassData::classNum() const
{
    return data[1];
}

int ClassData::time() const
{
    return data[2];
}

bool ClassData::operator<(const ClassData &dv) const
{
    if (time() < dv.time())
    {
        return true;
    }
    if (time() == dv.time())
    {
        if (course() > dv.course())
        {
            return true;
        }
        if (course() == dv.course())
            if (classNum() > dv.classNum())
            {
                return true;
            }
    }
    return false;
}

bool ClassData::operator<=(const ClassData &dv) const
{
    return ((*this == dv) || (*this < dv));
}

bool ClassData::operator>(const ClassData &dv) const
{
    return !(*this <= dv);
}
bool ClassData::operator>=(const ClassData &dv) const
{
    return ((*this == dv) || (*this > dv));
}
bool ClassData::operator==(const ClassData &dv) const
{
    return ((time() == dv.time()) && (course() == dv.course()) && (classNum() == dv.classNum()));
}
bool ClassData::operator!=(const ClassData &dv) const
{
    return !(*this == dv);
}
