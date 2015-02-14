// moldy_argon.cpp: Tommy Ogden <t@ogden.eu>
// Description: 

#include <iostream>
#include <Eigen/Core>

#include <cmath>

using namespace std;
using namespace Eigen;

#include "sim.h"

int main(int argc, char* argv[]) {

  // Default values

  int num_dims = 2;
  int num_atoms = 16;

  float box_length = 4.0;

  float vel_width = 0.1;
  float vel_max = 10 * vel_width; // if this is too high, lots of rejections

  float t_step = 0.004;
  int num_t_steps = 1000;

  char* bc_type_ptr;
  char bc_type = 't'; // Toroidal Boundary Conditions

  char* force_type_ptr;
  char force_type = 'l'; // Lennard-Jones

  float cutoff = 0.0;

  string filename = "moldy_argon.json";

  // Iterate over argv[] to get the parameters stored inside.
  for (int i = 1; i < argc; i++) { 
    // Check that we haven't finished parsing already
    if (i + 1 != argc) {
      if (string(argv[i]) == "--num-dims")
        num_dims = atoi(argv[i+1]);
      else if (string(argv[i]) == "--num-atoms")
        num_atoms = atoi(argv[i+1]);
      else if (string(argv[i]) == "--box-length")
        box_length = atof(argv[i+1]); 
      else if (string(argv[i]) == "--vel-width")
        vel_width = atof(argv[i+1]); 
      else if (string(argv[i]) == "--t-step") // Time step
        t_step = atof(argv[i+1]);
      else if (string(argv[i]) == "--num-t-steps") // Number of time steps
        num_t_steps = atoi(argv[i+1]);
      else if (string(argv[i]) == "--bc-type") {// Boundary condition type
        bc_type_ptr = argv[i+1]; 
        bc_type = *bc_type_ptr; 
      }
      else if (string(argv[i]) == "--force-type") { // Force type
        force_type_ptr = argv[i+1]; 
        force_type = *force_type_ptr; 
      }
      else if (string(argv[i]) == "--cutoff")
        cutoff = atof(argv[i+1]); 
      else if (string(argv[i]) == "--filename")
        filename = argv[i+1];
    }
  }

  cout << "Num dims: " << num_dims << endl;
  cout << "Num atoms: " << num_atoms << endl;
  cout << "Box length: " << box_length << endl;
  cout << "Vel width:" << vel_width << endl;
  cout << "Time step: " << t_step << endl;
  cout << "Num time steps: " << num_t_steps << endl;
  cout << "BC Type: " << bc_type << endl;
  cout << "Force Type: " << force_type << endl;
  cout << "Cutoff: " << cutoff << endl;
  cout << "Filename: " << filename << endl;

  Sim sim(box_length, num_dims, num_atoms);   

  // Seed random number generator for MB dist
  srand(time(NULL));

  // Assign positions
  // sim.set_atoms_pos_random_in_box();
  // sim.get_atoms()->set_pos_random_min(box_length, 1.25);
  sim.get_atoms()->set_pos_lattice(box_length);

  // Assign velocities, Maxwell-Boltzmann distribution
  sim.set_atoms_vel_mb(vel_width, vel_max);

  sim.run(num_t_steps, t_step, bc_type, force_type, cutoff, filename);

  return 0;

}