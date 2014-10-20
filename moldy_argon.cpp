// moldy_argon.cpp: Tommy Ogden <t@ogden.eu>
// Description: 

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

#include "sim.h"

int main(int argc, char* argv[]) {

  int num_dims = 2;
  int num_atoms = 10;

  float box_length = 10.0; 
  float max_speed = 1.0;

  float t_step = 0.1;
  int num_t_steps = 100;

  char bc_type = 't'; // Toroidal Boundary Conditions
  string filename = "moldy_argon.json";

  // Iterate over argv[] to get the parameters stored inside.
  for (int i = 1; i < argc; i++) { 
    // Check that we haven't finished parsing already
    if (i + 1 != argc) {
      if (string(argv[i]) == "--num-dims") // Num dims
        num_dims = atoi(argv[i+1]);
      else if (string(argv[i]) == "--num-atoms") // Num atoms
        num_atoms = atoi(argv[i+1]);
      else if (string(argv[i]) == "--box-length") // Box length
        box_length = atof(argv[i+1]); 
      else if (string(argv[i]) == "--max-speed") // Max speed
        max_speed = atof(argv[i+1]);  
      else if (string(argv[i]) == "--t-step") // Time step
        t_step = atof(argv[i+1]);
      else if (string(argv[i]) == "--num-t-steps") // Number of time steps
        num_t_steps = atoi(argv[i+1]);
      else if (string(argv[i]) == "--bc-type") // Boundary condition type
        num_t_steps = atoi(argv[i+1]);
      else if (string(argv[i]) == "--filename") // Filename
        filename = argv[i+1];
    }
  }

  cout << "Num dims: " << num_dims << endl;
  cout << "Num atoms: " << num_atoms << endl;

  cout << "Box length: " << box_length << endl; 
  cout << "Max speed: " << max_speed << endl;

  cout << "Time step: " << t_step << endl;
  cout << "Num time steps: " << num_t_steps << endl;

  Sim sim(box_length, num_dims, num_atoms);   

  // Set the positions of the atoms to be a uniform random distribution within
  // the box length.
  srand(time(NULL));
  sim.set_atoms_pos_random_in_box();

  // We'll write a Maxwell-Boltzmann velocity dist function later to use.
  sim.get_atoms()->set_vel_random(max_speed);


  sim.run(num_t_steps, t_step, bc_type, filename);

  return 0;

}