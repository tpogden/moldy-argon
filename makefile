# Variables ___________________________________________________________________

CFLAGS=-c
IFLAGS=-I eigen

# All _________________________________________________________________________

# all: clean
# all: sim_test_a00
all: sim_test_a01

# Sim _________________________________________________________________________

# Binaries

sim_test_a01: sim_test_a01.o sim.o atoms.o
	g++ $(IFLAGS) sim_test_a01.o sim.o atoms.o -o sim_test_a01

sim_test_a00: sim_test_a00.o sim.o atoms.o
	g++ $(IFLAGS) sim_test_a00.o sim.o atoms.o -o sim_test_a00

# Outputs

sim_test_a01.o:
	g++ $(CFLAGS) $(IFLAGS) sim_test_a01.cpp

sim_test_a00.o:
	g++ $(CFLAGS) $(IFLAGS) sim_test_a00.cpp

sim.o: sim.cpp
	g++ $(CFLAGS) $(IFLAGS) sim.cpp

# Atoms _______________________________________________________________________

# Binaries

atoms_test_a04: atoms_test_a04.o atoms.o
	g++ $(IFLAGS) atoms_test_a04.o atoms.o -o atoms_test_a04

atoms_test_a03: atoms_test_a03.o atoms.o
	g++ $(IFLAGS) atoms_test_a03.o atoms.o -o atoms_test_a03	

atoms_test_a02: atoms_test_a02.o atoms.o
	g++ $(IFLAGS) atoms_test_a02.o atoms.o -o atoms_test_a02	

atoms_test_a01: atoms_test_a01.o atoms.o
	g++ $(IFLAGS) atoms_test_a01.o atoms.o -o atoms_test_a01	

atoms_test_a00: atoms_test_a00.o atoms.o
	g++ $(IFLAGS) atoms_test_a00.o atoms.o -o atoms_test_a00	

# Outputs

atoms_test_a04.o: atoms_test_a04.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms_test_a04.cpp

atoms_test_a03.o: atoms_test_a03.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms_test_a03.cpp

atoms_test_a02.o: atoms_test_a02.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms_test_a02.cpp

atoms_test_a01.o: atoms_test_a01.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms_test_a01.cpp

atoms_test_a00.o: atoms_test_a00.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms_test_a00.cpp

atoms.o: atoms.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms.cpp

# Clean -----------------------------------------------------------------------
	
clean:
	rm -rf *.o