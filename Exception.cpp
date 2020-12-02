#include "./Exception.h"

using namespace DS;
using namespace std;

Exception::Exception(std::string desc, StatusType type) : desc(desc)
{
    type_data = type;
}
std::string Exception::what()
{
    return desc;
}

StatusType Exception::type()
{
    return type_data;
}