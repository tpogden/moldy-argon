// atoms_test_a02.cpp: Tommy Ogden <t@ogden.eu> 
// Description: Testing move and accl functions

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

  cout << atoms_1.get_info() << endl;

  ArrayXXf move_1 = ArrayXXf::Ones(kNumDims, num_atoms);
  atoms_1.move(move_1);

  cout << atoms_1.get_info() << endl;

  VectorXf move_atom_3(kNumDims); move_atom_3 << 2.0, 2.0;
  atoms_1.move(move_atom_3, 3);

  cout << atoms_1.get_info() << endl;

  atoms_1.accl(move_1);

  cout << atoms_1.get_info() << endl;

  atoms_1.accl(move_atom_3, 3);  

  cout << atoms_1.get_info() << endl;

  return 0;
}