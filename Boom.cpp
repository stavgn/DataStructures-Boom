#include "./Boom.h"
#include "./Vector.h"
#include "./ClassDataVector.h"
#include "./tree_node.h"
#include "./Exception.h"

using namespace DS;

Boom::Boom() : classes(Tree<ClassData, ClassData>()), courses(Tree<int, Vector>())
{
}

StatusType Boom::AddCourse(int courseID, int numOfClasses)
{
    if (courses.find(courseID) == nullptr)
    {
        courses.insert(courseID, new Vector(numOfClasses));
    }
    else
    {
        throw Exception("invalid courseId", INVALID_INPUT);
    }

    return SUCCESS;
}

StatusType Boom::RemoveCourse(int courseID)
{
    courses.remove(courseID);
    return SUCCESS;
}

StatusType Boom::WatchClass(int courseID, int classID, int time)
{
    if (courses.find(courseID) != nullptr)
    {
        Vector v = *courses.find(courseID);
        ClassData prev_record = ClassData(courseID, classID, v[classID - 1]);
        ClassData *next_record = new ClassData(courseID, classID, v[classID - 1] + time);
        v[classID - 1] += time;
        classes.remove(prev_record);
        classes.insert(*next_record, next_record);
    }
    else
    {
        throw Exception("invalid courseId", INVALID_INPUT);
    }

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
    int counter = numOfClasses;
    tree_node node = classes.get_anchor();
    while (counter > 0)
    {
        ClassData data = *node.data_ptr;
        courses[counter - 1] = data[0];
        courses[counter - 1] = data[1];
        counter--;
        node = *node.left_ptr;
        if (*node == nullptr)
        {
            break;
        }
    }

    tree_node courses_node = courses.get_anchor();
    while (counter > 0)
    {
        ClassData data = *courses_node.data_ptr;
        courses[counter - 1] = data[0];
        courses[counter - 1] = data[1];
        courses_node = *node.left_ptr;
        counter--;
        if (*node == nullptr)
        {
            break;
        }
    }

    if (counter != 0)
    {
        throw Exception("numOfClasses is too big, INVALID_INPUT);
    }
}