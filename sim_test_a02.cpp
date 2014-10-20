// sim_test_a02.cpp: Tommy Ogden <t@ogden.eu>
// Description: 

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

#include "sim.h"

int main() {

  // Initialise simulation
  const int kNumDims = 2;
  float box_length = 10.0; 
  int num_atoms = 50;
  Sim sim(box_length, kNumDims, num_atoms);

  // Set the positions of the atoms to be a uniform random distribution within
  // the box length.
  srand(time(NULL));
  sim.set_atoms_pos_random_in_box();

  // We'll write a Maxwell-Boltzmann velocity dist function later to use.
  float max_speed = 1.0;
  sim.get_atoms()->set_vel_random(max_speed);

  // Run the simulation.
  int num_t_steps = 1000;
  float t_step = 0.1;
  string filename = "sim_test_a02.json";
  sim.run(num_t_steps, t_step, filename);

  return 0;

}