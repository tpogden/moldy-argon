// atoms_test_a02.cpp: Tommy Ogden <t@ogden.eu> 
// Description: Testing move and accl functions

#include <iostream>
using namespace std;

#include "atoms.h"

int main() {
  // We'll use a 3D model.
  const int kNumDims = 2;
  // Initialise a set of atoms.
  int num_atoms = 2;
  Atoms atoms(kNumDims, num_atoms);
  // Set the positions of the atoms with a uniform random distribution within
  // a box with limits [-5.0, 5.0] in 3D.
  srand(time(NULL));
  float box_length = 10.0;
  atoms.set_pos_random(box_length);

  ArrayXXf vel_0 = ArrayXXf::Ones(kNumDims, num_atoms)*0.5;
  atoms.set_vel(vel_0);

  cout << atoms.get_info() << endl;

  float t_step = 0.1;

  atoms.step_with_vel_verlet(t_step);
  cout << atoms.get_info() << endl;

  atoms.step_with_vel_verlet(t_step);
  cout << atoms.get_info() << endl;

  atoms.step_with_vel_verlet(t_step);
  cout << atoms.get_info() << endl;

  atoms.step_with_vel_verlet(t_step);
  cout << atoms.get_info() << endl;

  atoms.step_with_vel_verlet(t_step);
  cout << atoms.get_info() << endl;

  return 0;
}