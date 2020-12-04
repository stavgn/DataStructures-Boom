#include "./ClassDataVector.h"

using namespace DS;

ClassData::ClassData(int course, int classNum, int watchTime) : Vector(3)
{
    data[0] = course;
    data[1] = classNum;
    data[2] = watchTime;
}

int ClassData::course()
{
    return data[0]
}

int ClassData::classNum()
{
    return data[1]
}

int ClassData::time()
{
    return data[2]
}

bool ClassData::operator<(const ClassData &dv)
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

bool ClassData::operator<=(const ClassData &dv)
{
    return (this == dv) || (this < dv);
}

bool ClassData::operator>(const ClassData &dv)
{
    return !(this < dv);
}
bool ClassData::operator>=(const ClassData &dv)
{
    return (this == dv) || (this > dv);
}
bool ClassData::operator==(const ClassData &dv)
{
    return (time() == dv.time()) && (course() < dv.course()) && (classNum() == dv.classNum())
}
bool ClassData::operator!=(const ClassData &dv)
{
    return !(this == dv);
}
