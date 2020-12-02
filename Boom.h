#ifndef BOOM_H
#define BOOM_H

#include "./Tree.h"
#include "./Vector.h"
#include "./ClassDataVector.h"
#include "./Exception.h"
 
namespace DS
{
    class Boom
    {
        Tree<int, Vector> courses;
        Tree<ClassData, ClassData> classes;

    private:
        /* data */
    public:
        Boom();
        ~Boom() = default;
        StatusType AddCourse(int courseID, int numOfClasses);
        StatusType RemoveCourse(int courseID);
        StatusType WatchClass(int courseID, int classID, int time);
        StatusType TimeViewed(int courseID, int classID, int *timeViewed);
        StatusType GetMostViewedClasses(int numOfClasses, int *courses, int *classes);
    };

} // namespace DS

#endif