
PROJECT(need4speed)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

#list all source files here
ADD_EXECUTABLE(need4speed main.cpp)

#need to link to some other libraries ? just add them here
#TARGET_LINK_LIBRARIES(need4speed png jpeg)
 
