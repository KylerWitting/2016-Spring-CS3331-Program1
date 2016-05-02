CC       = gcc

OBJ_FILE  = prog1.o
EXE_FILE  = prog1
PROG 	  = prog1.c
TAGS      = -lm -o


${EXE_FILE}: ${PROG}
	${CC} ${PROG} ${TAGS} ${EXE_FILE}

all : ${EXE_FILE}

clean:
	rm -f ${OBJ_FILE} ${EXE_FILE}
