EXEC = myprogram

CC = clang

OPT = -O0
CFLAGS = -std=c99 -g -Wall -MMD ${OPT}

SRC = $(wildcard *.c)

OBJECTS = $(SRC:.c=.o)

DEPENDS = $(OBJECTS:.o=.d)

${EXEC}: ${OBJECTS} 
				${CC} ${CFLAGS} ${OBJECTS} -lm -o ${EXEC}

# copy the generated .d files which provides dependencies for each .c file
-include ${DEPENDS}

.PHONY: clean

clean: 
	rm *.o *.d ${EXEC}
