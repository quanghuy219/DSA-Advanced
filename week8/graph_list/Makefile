# Declaration of variables
CC = gcc
CC_FLAGS = -g -Wall
 
# File names
EXEC = main
ALL_SOURCES = $(wildcard *.c)
SOURCES = $(filter-out btfile.c, $(ALL_SOURCES))
OBJECTS = $(ALL_SOURCES:.c=.o)
LIBS = libfdr/libfdr.a

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(CC_FLAGS) -o $(EXEC) $(OBJECTS) $(LIBS)
 
# To obtain object files
%.o: %.c
	$(CC) $(CC_FLAGS) -I/libfdr/include -c $< 

# To remove generated files
clean:
	rm -f $(EXEC) *.o
