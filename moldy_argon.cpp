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
  int num_atoms = 10;

  float box_length = 10.0;

  float vel_width = 1.0;
  float vel_max = 10 * vel_width; // if this is too high, lots of rejections

  float t_step = 0.1;
  int num_t_steps = 100;

  char* bc_type_ptr;
  char bc_type = 't'; // Toroidal Boundary Conditions
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
  cout << "Filename: " << filename << endl;

  Sim sim(box_length, num_dims, num_atoms);   

  // Set the positions of the atoms to be a uniform random distribution within
  // the box length.
  srand(time(NULL));
  sim.set_atoms_pos_random_in_box();
  sim.set_atoms_vel_mb(vel_width, vel_max);

  sim.run(num_t_steps, t_step, bc_type, filename);

  return 0;

}