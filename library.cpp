#include "./library.h"
#include "./Boom.h"

using namespace DS;

void *Init()
{
    return ((void *)new Boom());
}

StatusType AddCourse(void *DS, int courseID, int numOfClasses)
{
    Boom boom = *static_cast<Boom *>(DS);
    return boom.AddCourse(courseID, numOfClasses);
}

StatusType RemoveCourse(void *DS, int courseID)
{
    Boom boom = *static_cast<Boom *>(DS);
    return boom.RemoveCourse(courseID);
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    Boom boom = *static_cast<Boom *>(DS);
    return boom.WatchClass(courseID, classID, time);
}
StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    Boom boom = *static_cast<Boom *>(DS);
    return boom.TimeViewed(courseID, classID, timeViewed);
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    Boom boom = *static_cast<Boom *>(DS);
    return boom.GetMostViewedClasses(numOfClasses, courses, classes);
}

void Quit(void *DS)
{
    Boom boom = static_cast<Boom *>(DS);
    delete boom;
}
