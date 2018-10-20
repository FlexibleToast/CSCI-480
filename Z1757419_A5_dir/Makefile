#
# PROGRAM:    Assignment 5
# PROGRAMMER: Joseph McDade
# LOGON ID:   z1757419
# DATE DUE:   10/26/2018
#

# Rule to link object code files to create executable file
Assign5: Assign5.o
	gcc -o Assign5 Assign5.o

# Rules to compile source code files to object code
Assign5.o: Assign5.c
	gcc -c Assign5.c

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o Assign5
