#include "./library.h"
#include "./Boom.h"

using namespace DS;

void *Init()
{
    return ((void *)new Boom());
}

StatusType AddCourse(void *DS, int courseID, int numOfClasses)
{
    try
    {
        Boom boom = *static_cast<Boom *>(DS);
        return boom.AddCourse(courseID, numOfClasses);
    }
    catch (Exception &e)
    {
        return e.type();
    }
    catch (std::bad_alloc &ba)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveCourse(void *DS, int courseID)
{
    try
    {
        Boom boom = *static_cast<Boom *>(DS);
        return boom.RemoveCourse(courseID);
    }
    catch (Exception &e)
    {
        return e.type();
    }
    catch (std::bad_alloc &ba)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    try
    {
        Boom boom = *static_cast<Boom *>(DS);
        return boom.WatchClass(courseID, classID, time);
    }
    catch (Exception &e)
    {
        return e.type();
    }
    catch (std::bad_alloc &ba)
    {
        return ALLOCATION_ERROR;
    }
}
StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    try
    {
        Boom boom = *static_cast<Boom *>(DS);
        return boom.TimeViewed(courseID, classID, timeViewed);
    }
    catch (Exception &e)
    {
        return e.type();
    }
    catch (std::bad_alloc &ba)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    try
    {
        Boom boom = *static_cast<Boom *>(DS);
        return boom.GetMostViewedClasses(numOfClasses, courses, classes);
    }
    catch (Exception &e)
    {
        return e.type();
    }
    catch (std::bad_alloc &ba)
    {
        return ALLOCATION_ERROR;
    }
}

void Quit(void **DS)
{
    Boom *boom = static_cast<Boom *>(*DS);
    delete boom;
}
