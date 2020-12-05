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
        throw Exception("Course was not found",FAILURE); 
    }
    courses.remove(courseID);
    return SUCCESS;
}

StatusType Boom::WatchClass(int courseID, int classID, int time)
{
    if (courses.find(courseID) != nullptr)
    {
        Vector &v = *courses.find(courseID);
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
    Vector& v = *courses.find(courseID);
    *timeViewed = v[classID - 1];
    return SUCCESS;
}

StatusType Boom::GetMostViewedClasses(int numOfClasses, int *courses_array, int *classes_array)
{
    int counter = numOfClasses;
    tree_node<ClassData, ClassData> *node = classes.get_max_leaf();
    while ((counter > 0) && (node != nullptr))
    {
        ClassData& data = *(node->data_ptr);
        courses_array[counter - 1] = data[0];
        classes_array[counter - 1] = data[1];
        counter--;
        node = node->left_ptr;
       
    }

    tree_node<int, Vector> *courses_node = courses.get_min_leaf();
    while( (counter > 0) && (courses_node != nullptr))
    {
        Vector& data = *(courses_node->data_ptr);
        int courseId = courses_node->key;
        for (int i = 0;(( i < data.size) &&(counter != 0)) ; i++)
        {
            if (data[i] == 0)
            {
                courses_array[counter - 1] = courseId;
                classes_array[counter - 1] = i;
                counter--;
               
            }
        }
        courses_node = courses_node->right_ptr;
        
    }

    if (counter != 0)
    {
        throw Exception(("numOfClasses is too big"), FAILURE);
    }
}