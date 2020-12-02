#ifndef ClassData_H
#define ClassData_H

#include "./Vector.h";

namespace DS
{
    class ClassData : public Vector
    {
    private:
        /* data */
    public:
        ClassData(int course, int classNum, int watchTime);
        ~ClassData() = default;
        bool operator<(const ClassData &dv);
    };

} // namespace DS

#endif