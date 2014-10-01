# Variables ___________________________________________________________________

CFLAGS=-c
IFLAGS=-I eigen

# Atoms _______________________________________________________________________

all: atoms_test_a00

# Binaries

atoms_test_a00: atoms_test_a00.o atoms.o
	g++ $(IFLAGS) atoms_test_a00.o atoms.o -o atoms_test_a00	

# Outputs

atoms_test_a01.o: atoms_test_a01.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms_test_a01.cpp

atoms_test_a00.o: atoms_test_a00.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms_test_a00.cpp

atoms.o: atoms.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms.cpp

# Clean -----------------------------------------------------------------------
	
clean:
	rm -rf *.o