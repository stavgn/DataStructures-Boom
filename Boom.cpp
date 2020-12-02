#include "./Boom.h"
#include "./Vector.h"
#include "./ClassDataVector.h"

using namespace DS;

Boom::Boom() : classes(Tree<ClassData, ClassData>()), courses(Tree<int, Vector>())
{
}

StatusType Boom::AddCourse(int courseID, int numOfClasses)
{

    courses.insert(courseID, Vector(numOfClasses));
    return SUCCESS;
}

StatusType Boom::RemoveCourse(int courseID)
{
    courses.remove(courseID);
    return SUCCESS;
}

StatusType Boom::WatchClass(int courseID, int classID, int time)
{
    Vector v = *courses.find(courseID);
    ClassData prev_record = ClassData(courseID, classID, v[classID - 1]);
    ClassData next_record = ClassData(courseID, classID, v[classID - 1] + time);
    v[classID - 1] += time;
    classes.remove(prev_record);
    classes.insert(next_record, next_record);

    return SUCCESS;
}

StatusType Boom::TimeViewed(int courseID, int classID, int *timeViewed)
{
    Vector v = *courses.find(courseID);
    *timeViewed = v[classID - 1];
    return SUCCESS;
}

StatusType Boom::GetMostViewedClasses(int numOfClasses, int *courses, int *classes)
{
}