// atoms.h: Tommy Ogden <t@ogden.eu>
// Definition for Sim (simulation) class.

#ifndef SIM_H
#define SIM_H

#include <Eigen/Core>
#include <fstream>

#include "atoms.h"

using namespace std;
using namespace Eigen;

// Represents a simulation. A simulation's state has a collection of atoms
// (an Atoms object) and a current time (t). Sample usage:
// Sim my_sim(10, 2, 10); // 10 atoms in a 2D box.

class Sim {

 private:

  float t_; // time

  // TODO: Should box length be a member of atoms or sim? If the box length is
  // a member of the Sim class then the set_pos_random method should **also**
  // be in the Sim class.
  float box_length_; 

  Atoms * atoms_;

 public:

  // Constructors & Destructors _______________________________________________

  Sim(float t_i, float box_length_i, int num_dims_i, int num_atoms_i);
  Sim(float box_length_i, int num_dims_i, int num_atoms_i);

  // Inits ____________________________________________________________________

  // Initialises the simulation, putting in a set of Atoms with masses = 1,
  // positions and velocities zero vectors.
  int init(float t_i, float box_length_i, int num_dims_i, int num_atoms_i);

  // Sets _____________________________________________________________________

  // Sets the current time of the simulation.
  int set_t(float t_i);

  // Sets the box length (i.e. [-box_length/2, box_length/2] in each 
  // dimension).
  int set_box_length(float box_length_i);

  // Sets the positions of the atoms to be a uniform random distribution within
  // the box_length.
  int set_atoms_pos_random_in_box();

  // Gets _____________________________________________________________________

  // Returns the current time of the simulation.
  float get_t() const;
  // Returns the box length of the simulation.
  float get_box_length() const;
  // Returns the collection of atoms.
  Atoms * get_atoms() const;
  // Returns the simulation object in json format.
  string get_json() const;

// File Writes ________________________________________________________________

  // Writes the simulation object in json format to a file stream object.
  int write_json_file(ofstream & json_o_file_i);
  // Write the simulation object in jason format to the given filename.  
  int write_json_file(string & json_filename_i);

// Run ________________________________________________________________________

  // Runs the simulation by stepping from t=0.0 and saves the json format
  // object to the given filename at each step.
  int run(int num_t_steps_i, float t_step_i, string & json_filename_i);

};

#endif