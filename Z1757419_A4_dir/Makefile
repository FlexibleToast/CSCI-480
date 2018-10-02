#
# PROGRAM:    Assignment 4
# PROGRAMMER: Joseph McDade
# LOGON ID:   z1757419
# DATE DUE:   09/29/2018
#

# Rule to link object code files to create executable file
Assign4: Assign4.o #Process.o
	gcc -o Assign4 Assign4.o #Process.o

# Rules to compile source code files to object code
Assign4.o: Assign4.c
	gcc -c Assign4.c

# Process.o: Process.c Process.h
# 	gcc -c Process.c

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign4
