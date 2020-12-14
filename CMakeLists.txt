

# The following is required by CMake
# Set hw0 as the project name, C as the target language
# A project can contain multiple build products
project(wet_1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/bin/g++ CACHE PATH "" FORCE)
# # (Optionally uncomment): see more output from cmake during build,
# # including specific gcc command(s).
# set(CMAKE_VERBOSE_MAKEFILE ON)
# Set variables holding flags for gcc
set(MTM_FLAGS_DEBUG "-std=c++11 -Wall -Werror -pedantic-errors")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDBUG")
# Set the flags for gcc (can also be done using target_compile_options and a couple of other
#ways)
set(CMAKE_CPP_FLAGS ${MTM_FLAGS_DEBUG})
# Tell CMake to build an executable named mtm_tot, specifying the comprising file(s)

# add_executable(wet_1 main_for_testing.cpp Boom.cpp ClassDataVector.cpp Exception.cpp library.cpp Vector.cpp)
add_executable(wet_1 main1.cpp Boom.cpp ClassDataVector.cpp Exception.cpp library.cpp Vector.cpp)
#  add_executable(wet_1 main.cpp)
