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
        throw Exception("invalid courseId", FAILURE);
    }

    return SUCCESS;
}

StatusType Boom::RemoveCourse(int courseID)
{
    if (courses.find(courseID) == nullptr)
    {
        throw Exception("Course was not found", FAILURE);
    }
    Vector &v = *courses.find(courseID);
    for (int i = 0; i < v.size; i++) {
         if (v[i] != 0) {
            ClassData key = ClassData(courseID, i, v[i]);
            classes.remove(key);
         }
    }
    courses.remove(courseID);
    return SUCCESS;
}

StatusType Boom::WatchClass(int courseID, int classID, int time)
{
    if (courses.find(courseID) != nullptr)
    {
        Vector &v = *courses.find(courseID);
        ClassData prev_record = ClassData(courseID, classID, v[classID]);
        ClassData *next_record_key = new ClassData(courseID, classID, v[classID] + time);
        v[classID] += time;
        classes.remove(prev_record);
        classes.insert(*next_record_key, next_record_key);
    }
    else
    {
        throw Exception("course wasn't found", FAILURE);
    }

    return SUCCESS;
}

StatusType Boom::TimeViewed(int courseID, int classID, int *timeViewed)
{
    if(courses.find(courseID) == nullptr)
    {
        throw Exception("course was'nt found", FAILURE);
    }
    Vector &v = *courses.find(courseID);
    *timeViewed = v[classID];
    return SUCCESS;
}

StatusType Boom::GetMostViewedClasses(int numOfClasses, int *courses_array, int *classes_array)
{
    int counter = numOfClasses;
    if (classes.get_max_leaf() != nullptr)
    {
        tree_node<ClassData, ClassData> *node = classes.get_max_leaf();
        while ((counter > 0) && (node != nullptr))
        {
            ClassData &data = *(node->data_ptr);
            courses_array[numOfClasses - counter] = data[0];
            classes_array[numOfClasses - counter] = data[1];
            counter--;
            node = node->left_ptr;
        }
    }

    tree_node<int, Vector> *courses_node = courses.get_min_leaf();
    while ((counter > 0) && (courses_node != nullptr))
    {
        Vector &data = *(courses_node->data_ptr);
        int courseId = courses_node->key;
        for (int i = 0; ((i < data.size) && (counter > 0)); i++)
        {
            if (data[i] == 0)
            {
                courses_array[numOfClasses - counter] = courseId;
                classes_array[numOfClasses - counter] = i;
                counter--;
            }
        }
        courses_node = courses_node->right_ptr;
    }
    if (counter != 0)
    {
        throw Exception(("numOfClasses is too big"), FAILURE);
    }
    return SUCCESS;
}