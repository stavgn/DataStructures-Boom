#include "./library.h"
#include "./Boom.h"

using namespace DS;

void *Init()
{
    return ((void *)new Boom());
}

StatusType AddCourse(void *DS, int courseID, int numOfClasses)
{

    if (DS == nullptr || numOfClasses <= 0 || courseId <= 0)
    {
        return INVALID_INPUT;
    }
    try
    {
        Boom *boom = static_cast<Boom *>(DS);
        if (boom == NULL)
        {
            return INVALID_INPUT;
        }
        return boom->AddCourse(courseID, numOfClasses);
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
    if (DS == nullptr || courseId <= 0)
    {
        return INVALID_INPUT;
    }
    try
    {
        Boom *boom = static_cast<Boom *>(DS);
        if (boom == NULL)
        {
            return INVALID_INPUT;
        }
        return boom->RemoveCourse(courseID);
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
    if (DS == nullptr || courseId <= 0 || classID < 0)
    {
        return INVALID_INPUT;
    }
    try
    {
        Boom *boom = static_cast<Boom *>(DS);
        if (boom == NULL)
        {
            return INVALID_INPUT;
        }
        return boom->WatchClass(courseID, classID, time);
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
    if (DS == nullptr || courseID <= 0 || classID < 0)
    {
        return INVALID_INPUT;
    }
    try
    {
        Boom *boom = static_cast<Boom *>(DS);
        if (boom == NULL)
        {
            return INVALID_INPUT;
        }
        return boom->TimeViewed(courseID, classID, timeViewed);
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
    if (DS == nullptr || courseID <= 0 || classID < 0)
    {
        return INVALID_INPUT;
    }
    try
    {
        Boom *boom = static_cast<Boom *>(DS);
        if (boom == NULL)
        {
            return INVALID_INPUT;
        }
        return boom->GetMostViewedClasses(numOfClasses, courses, classes);
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
    if (boom == NULL)
    {
        return INVALID_INPUT;
    }
    delete boom;
}
