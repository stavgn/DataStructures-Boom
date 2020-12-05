#ifndef ClassData_H
#define ClassData_H

#include "./Vector.h"

namespace DS
{
    class ClassData : public Vector
    {
    private:
        /* data */
    public:
        ClassData(int course = 0, int classNum = 0, int watchTime = 0);
        ~ClassData() = default;
        bool operator<(const ClassData &dv);
        bool operator<=(const ClassData &dv);
        bool operator>(const ClassData &dv);
        bool operator>=(const ClassData &dv);
        bool operator==(const ClassData &dv);
        bool operator!=(const ClassData &dv);
        int course();
        int classNum();
        int time();
    };

} // namespace DS

#endif