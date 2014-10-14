// atoms_test_a01.cpp: Tommy Ogden <t@ogden.eu> 
// Description: Initialise a set of atoms with default mass, pos and vel. Print 
//              info.

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

#include "atoms.h"

int main() {

  const int kNumDims = 3;

  int num_atoms = 6;

  Atoms atoms_1(kNumDims, num_atoms);

  cout << atoms_1.get_info() << endl;

  float cell_length = 5.0;

  atoms_1.set_pos_random(cell_length);

  cout << atoms_1.get_info() << endl;

  return 0;

}