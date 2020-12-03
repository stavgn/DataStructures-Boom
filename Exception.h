
#ifndef EXECPTION_H
#define EXECPTION_H

#include <set>
#include <memory>
#include <string>
#include "library.h"





namespace DS
{

//     typedef enum
// {
//     SUCCESS = 0,
//     FAILURE = -1,
//     ALLOCATION_ERROR = -2,
//     INVALID_INPUT = -3
// } StatusType;


    class Exception : public std::exception
    {

    public:
        std::string desc;
        StatusType type_data;
        Exception(std::string desc, StatusType type);
        ~Exception() = default;
        std::string what();
        StatusType type();
    };

} // namespace DS

#endif