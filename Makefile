
# source files in this project (for beautification)
PROJECT_NAME=assg05
assg_src = SchedulingSystem.cpp \
	   SchedulingPolicy.cpp \
	   FCFSSchedulingPolicy.cpp \
	   SPNSchedulingPolicy.cpp

test_src = ${PROJECT_NAME}-tests.cpp \
	   ${assg_src}

sim_src  = ${PROJECT_NAME}-sim.cpp \
	   ${assg_src}

# template files, list all files that define template classes
# or functions and should not be compiled separately (template
# is included where used)
template-files =

# assignment description documentation
assg_doc = ${PROJECT_NAME}.pdf

# common targets and variables used for all assignments/projects
include include/Makefile.inc

# assignment header file specific dependencies
${OBJ_DIR}/${PROJECT_NAME}-tests.o: ${INC_DIR}/SchedulingSystem.hpp ${SRC_DIR}/${PROJECT_NAME}-tests.cpp
${OBJ_DIR}/${PROJECT_NAME}-sim.o: ${INC_DIR}/SchedulingSystem.hpp ${INC_DIR}/SchedulingPolicy.hpp ${INC_DIR}/FCFSSchedulingPolicy.hpp ${INC_DIR}/SPNSchedulingPolicy.hpp ${SRC_DIR}/${PROJECT_NAME}-sim.cpp
${OBJ_DIR}/SchedulingSystem.o: ${INC_DIR}/SchedulingSystem.hpp ${INC_DIR}/SchedulingPolicy.hpp ${INC_DIR}/FCFSSchedulingPolicy.hpp ${SRC_DIR}/SchedulingSystem.cpp
${OBJ_DIR}/SchedulingPolicy.o: ${INC_DIR}/SchedulingPolicy.hpp ${INC_DIR}/SchedulingSystem.hpp ${SRC_DIR}/SchedulingPolicy.cpp
${OBJ_DIR}/FCFSSchedulingPolicy.o: ${INC_DIR}/FCFSSchedulingPolicy.hpp ${INC_DIR}/SchedulingPolicy.hpp ${SRC_DIR}/FCFSSchedulingPolicy.cpp
${OBJ_DIR}/SPNSchedulingPolicy.o: ${INC_DIR}/SPNSchedulingPolicy.hpp ${INC_DIR}/SchedulingPolicy.hpp ${SRC_DIR}/SPNSchedulingPolicy.cpp

