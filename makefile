# Variables ___________________________________________________________________

CFLAGS=-c
IFLAGS=-I eigen

# All _________________________________________________________________________

all: moldy_argon

# Binaries ____________________________________________________________________

moldy_argon: moldy_argon.o sim.o atoms.o
	g++ $(IFLAGS) moldy_argon.o sim.o atoms.o -o moldy_argon

moldy_argon.o:
	g++ $(CFLAGS) $(IFLAGS) moldy_argon.cpp	

sim.o: sim.cpp
	g++ $(CFLAGS) $(IFLAGS) sim.cpp

atoms.o: atoms.cpp
	g++ $(CFLAGS) $(IFLAGS) atoms.cpp

# Clean _______________________________________________________________________
	
clean:
	rm -rf *.o