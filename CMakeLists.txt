cmake_minimum_required (VERSION 2.6)
PROJECT(student_score)
ADD_DEFINITIONS("-Wall -Wextra -ansi -pedantic -std=c99 -g")
add_executable (studentscore main.c list.c listsort.c)

