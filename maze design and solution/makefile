# makefile
# Boilerplate makefile for Assignment 2
# Feel free to edit or use your own versions if desired.

# Replace 'header1.h', 'header2.h', 'object1.o', 'object2.o', and 'executable'
# with your filenames. It's fine if you only have one header, just delete
# 'header2.h' in that case.


# What compiler do you use? Default is gcc.
CC=gcc

# Your headers go here. It's fine to only have one.
# DEPS = solve.h

# List of the object files that will be built. Replace the dummy-files with
# names corresponding to your source files. I.E. if you have source_1.c and
# source_2.c, these would be source_1.o and source_2.o
OBJ = solve.o main_solve.o 

# This is your actual executable to build. In general, just name this the same
# as whichever .c file has the main() function, with no suffix.
EXE = main_solve

################################################################################
## You should not need to change anything below this divider
################################################################################


# Default (first in the file) target. Will build your executable from your
# object files.
$(EXE): $(OBJ)
	$(CC) -o $@ $^ -lm


# This just makes sure your prerequisites exist before trying to build your
# object files.
$(OBJ): $(DEPS)


# Pattern rule that will build the listed object files from corresponding C
# files, and has your dependency list as a prerequisite
%.o: %.c
	$(CC) -c -o $@ $<


# .PHONY tells the makefile that the "clean" target isn't a file.
.PHONY: clean

# remove object files and executable created by make
clean:
	rm $(OBJ) $(EXE)
