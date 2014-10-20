// atoms_test_a02.cpp: Tommy Ogden <t@ogden.eu> 
// Description: 

#include <iostream>
using namespace std;

#include "atoms.h"

int main() {
  // We'll use a 3D model.
  const int kNumDims = 2;
  // Initialise a set of atoms.
  int num_atoms = 10;
  Atoms atoms_1(kNumDims, num_atoms);
  // Set the positions of the atoms with a uniform random distribution within
  // a box with limits [-5.0, 5.0] in 3D.
  srand(time(NULL));
  float box_length = 10.0;
  atoms_1.set_pos_random(box_length);
  // Print the atom masses, positions and velocities.
  cout << atoms_1.get_json() << endl;

  string json_fname = "atoms_test_a02.json";
    
  atoms_1.write_json_file(json_fname);

  return 0;
}