""" ===================================================================================================================

Written by Yaniv Wolf.
Last updated 08/12/2020.

Stress Test generator for DS1 Wet1.

Generates an in and out test file in the following format:
- Init
- All AddCourse commands in random order/sorted (can be set using SHUFFLE_INTERNAL_COMMAND_ORDER)
- All WatchClass commands of non-zero classes in random order/sorted (can be set using SHUFFLE_INTERNAL_COMMAND_ORDER)
- All TimeViewed commands in random order/sorted (can be set using SHUFFLE_INTERNAL_COMMAND_ORDER)
- GetMostViewedClasses with the parameter of all classes
- All RemoveCourse commands in random order/sorted (can be set using SHUFFLE_INTERNAL_COMMAND_ORDER)
- Quit

All generated input is legal, meaning all functions return SUCCESS and perform the required action.

=================================================================================================================== """

""" ========================================================
Import (DO NOT EDIT):
======================================================== """

import os
import sys
import math
import random

""" ========================================================
Set parameters (EDIT HERE):
======================================================== """

# Set 1 to shuffle internal order of each command, or 0 not to shuffle.
SHUFFLE_INTERNAL_COMMAND_ORDER = 1

# Set max parameters for random.
MAX_COURSE_ID = 10000 
MAX_CLASSES_IN_COURSE = 50 #Keep it low, or bad things will happen!!
MAX_TIME_VIEWED = 5000

# Set parameters for size of test.
NUMBER_OF_COURSES = 500 #Don't go too wild, espcially if you're testing on the csl3 server.

# Set the directory to which you want to save the test files. 
# If you want to use the current directory, leave a blank string ("").
# Example for Windows directory: "C:\\Users\\USERNAME\\Technion\\Courses\\234218_Data_Structures_1\\HW\\Wet_1\\tests"
# Example for Linux directory: "/home/USERNAME/ds1/wet1/tests"
DIRECTORY = "/home/dor-hay.sha/data_structure/wet_1/tests"

# Set names of test in and out files. Recommended format: "test.in" and "test.out"
TEST_IN_NAME = "test.in"
TEST_OUT_NAME = "test.out"

""" ========================================================
Code (DO NOT EDIT FROM HERE):
======================================================== """

# ==================================
# Generate random data for testing:
# ==================================
def generateData():
    # Generate unique course IDs.
    courseIDs = random.sample(range(1,MAX_COURSE_ID), NUMBER_OF_COURSES)
    # Generate the number of classe for each course.
    courses = {courseIDs[i] : random.randint(1,MAX_CLASSES_IN_COURSE) for i in range(NUMBER_OF_COURSES)}
    # Create a list of tuples (CourseID,ClassID,time_viewed).
    classes = []
    for courseID, num_classes in courses.items():
        for i in range(num_classes):
            specific_class = (courseID, i, random.randint(0,MAX_TIME_VIEWED))
            classes.append(specific_class)
    # Sort the list based on the parameters of the assignment.
    classes = sorted(classes, key = lambda x: (x[0],x[1]))
    classes = sorted(classes, key = lambda x: (x[2]), reverse=True)
    return courses, classes

# =========================
# Write to the test files:
# =========================
def writeTestFiles(courses, classes):

    with open (TEST_IN_NAME, "w") as test_in:
        with open (TEST_OUT_NAME, "w") as test_out:

            # =====
            # Init
            # =====
            test_in.write("Init\n")
            test_out.write("init done.\n")

            # ==========
            # AddCourse
            # ==========
            # Add all of the AddCourse commands and outputs for all courses to buffers.
            buffer_in=[]
            buffer_out=[]
            for courseID,num_classes in courses.items():
                buffer_in.append("AddCourse " + str(courseID) + " " + str(num_classes) + "\n")
                buffer_out.append(("AddCourse: SUCCESS\n"))
            # Shuffle if needed and write to the test files.
            writeToTests(buffer_in, test_in, buffer_out, test_out)

            # ===========
            # WatchClass
            # ===========
            # Add all of the WatchClass commands and outputs for all classes to buffers.
            buffer_in=[]
            buffer_out=[]
            for courseID,classID,time_viewed in classes:
                if time_viewed > 0:
                    buffer_in.append("WatchClass " + str(courseID) + " " + str(classID) + " " + str(time_viewed) + "\n")
                    buffer_out.append("WatchClass: SUCCESS\n") 
            # Shuffle if needed and write to the test files.
            writeToTests(buffer_in, test_in, buffer_out, test_out)

            # ===========
            # TimeViewed
            # ===========
            # Add all of the TimeViewed commands and outputs for all classes to buffers.
            buffer_in=[] 
            buffer_out=[]
            for courseID,classID,time_viewed in classes:
                buffer_in.append("TimeViewed " + str(courseID) + " " + str(classID) + "\n")
                buffer_out.append("TimeViewed: " + str(time_viewed) + "\n")
            # Shuffle if needed and write to the test files.
            writeToTests(buffer_in, test_in, buffer_out, test_out)

            # =====================
            # GetMostViewedClasses
            # =====================
            #Set the size of GetMostViewedClasses to the number of classes in the system.
            get_most_viewed_size = len(classes)
            # Write the command in the input test.
            test_in.write("GetMostViewedClasses " + str(get_most_viewed_size) + "\n")
            # Write the output in the output test.
            test_out.write("GetMostViewedClasses: SUCCESS\n")
            test_out.write("Course\t|\tClass\n")
            count = 0
            for courseID,classID,time_viewed in classes:
                test_out.write(str(courseID) + "\t|\t" + str(classID) + "\n")
                count += 1
                if count == get_most_viewed_size:
                    break
            test_out.write("--End of most viewed classes--\n")

            # =============
            # RemoveCourse
            # =============
            # Add all of the RemoveCourse commands and outputs for all courses to buffers.
            buffer_in=[]
            buffer_out=[]
            for courseID in courses:
                buffer_in.append("RemoveCourse " + str(courseID) + "\n")
                buffer_out.append("RemoveCourse: SUCCESS\n")
            # Shuffle if needed and write to the test files.
            writeToTests(buffer_in, test_in, buffer_out, test_out)

            # =====
            # Quit
            # =====
            test_in.write("Quit\n")
            test_out.write("quit done.\n")

# ==============================================================
# Helper function to write to test files and shuffle if needed:
# ==============================================================
def writeToTests(buffer_in, test_in, buffer_out, test_out):
    if SHUFFLE_INTERNAL_COMMAND_ORDER == 1:
        buffer_combined = list(zip(buffer_in,buffer_out))
        random.shuffle(buffer_combined)
        buffer_in, buffer_out = zip(*buffer_combined)        
    for command in buffer_in:
        test_in.write(command)
    for command in buffer_out:
        test_out.write(command)

# ===============
# Main function:
# ===============
def main():
    if DIRECTORY != "":
        print("Changing directory to " + DIRECTORY + "\n")
        os.chdir(DIRECTORY)
        print("Changed directory.\n")
    else:
        print("Using current directory: " + os.getcwd() + "\n")
    print("Generating Data...\n")
    courses, classes = generateData()
    print("Done generating Data.\n")
    print("Generating Test Files...\n")
    writeTestFiles(courses,classes)
    print("Done generating Test Files.\n")

    os.system("/home/dor-hay.sha/data_structure/wet_1/build/wet_1 < /home/dor-hay.sha/data_structure/wet_1/tests/test.in > /home/dor-hay.sha/data_structure/wet_1/out.txt")
    os.system("diff /home/dor-hay.sha/data_structure/wet_1/out.txt /home/dor-hay.sha/data_structure/wet_1/tests/test.out")

# =================
# Run the program:
# =================
if __name__ == "__main__":
    main()