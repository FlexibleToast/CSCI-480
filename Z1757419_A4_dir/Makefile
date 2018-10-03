#
# PROGRAM:    Assignment 4
# PROGRAMMER: Joseph McDade
# LOGON ID:   z1757419
# DATE DUE:   10/12/2018
#

# Compiler variables
CCFLAGS = -ansi -Wall -std=c++11

# Rule to link object code files to create executable file
Assign4: Assign4.o Process.o
	g++ $(CCFLAGS) -o Assign4 Assign4.o Process.o

# Rules to compile source code files to object code
Assign4.o: Assign4.cpp Process.h
	g++ $(CCFLAGS) -c Assign4.cpp

Process.o: Process.cpp Process.h
	g++ $(CCFLAGS) -c Process.cpp


# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign4
