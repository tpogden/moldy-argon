// atoms_test_a01.cpp: Tommy Ogden <t@ogden.eu> 
// Description: Initialise a set of atoms with default mass, pos and vel. Print 
//              info.

#include <iostream>
using namespace std;

#include "atoms.h"

int main() {
  // We'll use a 3D model.
  const int kNumDims = 3;
  // Initialise a set of atoms.
  int num_atoms = 6;
  Atoms atoms_1(kNumDims, num_atoms);
  // Print masses, positions and velocities.
  cout << atoms_1.get_info() << endl;
  // Set the positions of the atoms with a uniform random distribution within
  // a box with limits [-5.0, 5.0] in 3D.
  float box_length = 10.0;
  atoms_1.set_pos_random(box_length);
  // Print the atom masses, positions and velocities.
  cout << atoms_1.get_info() << endl;
  return 0;
}