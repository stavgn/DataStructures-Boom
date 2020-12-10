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
        ClassData(const ClassData& origin) : Vector(origin) {}
        ClassData& operator=(const ClassData& origin);
        ~ClassData() = default;
        bool operator<(const ClassData &dv) const;
        bool operator<=(const ClassData &dv) const;
        bool operator>(const ClassData &dv) const;
        bool operator>=(const ClassData &dv) const;
        bool operator==(const ClassData &dv) const;
        bool operator!=(const ClassData &dv)const;
        int course() const;
        int classNum() const;
        int time() const;
    };

} // namespace DS

#endif