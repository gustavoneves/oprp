# GNU Makefile

CC = mpicc
#CCFLAGS = -Wall
CCFLAGS = 
LDFLAGS = 
#LDFLAGS = -llmpe -lmpe 
TARGET = mpi_matrix_mult 

#%.o: %.c
#	$(CC) $(CCFLAGS) -c $<
#
#%: %.o
#	$(CC) $^ -o $@ 

all: $(TARGET)

# Dependencias

mpi_matrix_mult: matrix.c matrix.h mpi_matrix_mult.c
	$(CC) $(CCFLAGS) matrix.c mpi_matrix_mult.c -o $@ $(LDFLAGS) 
clean:
	rm -f *.o *~ $(TARGET)
