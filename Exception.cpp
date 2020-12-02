#include "./Exception.h"

using namespace DS;
using namespace std;

Exception::Exception(std::string desc, StatusType type) : desc(desc)
{
    type = type;
}
std::string Exception::what()
{
    return desc;
}

StatusType Exception::type()
{
    return type;
}