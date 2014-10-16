//
//
//
//

#ifndef SIM_H
#define SIM_H

#include <Eigen/Core>
#include <fstream>

#include "atoms.h"

using namespace std;
using namespace Eigen;

// Class: Sim _________________________________________________________________

class Sim {

 private:

  float t_; // time
  float box_length_;

  Atoms * atoms_;

 public:

  // Constructors & Destructors _______________________________________________

  Sim(float t_i, float box_length_i, int num_dims_i, int num_atoms_i);

  // Inits ____________________________________________________________________

  int init(float t_i, float box_length_i, int num_dims_i, int num_atoms_i);

  // Sets _____________________________________________________________________

  int set_t(float t_i);
  int set_box_length(float box_length_i);

  // Gets _____________________________________________________________________

  float get_t() const;
  float get_box_length() const;

  Atoms * get_atoms() const;

};

#endif