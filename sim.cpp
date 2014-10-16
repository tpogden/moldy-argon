//
//
//
//

#include <iostream>

#include "sim.h"

// Constructors & Destructors _________________________________________________

  Sim::Sim(float t_i, float box_length_i, int num_dims_i, int num_atoms_i) {
    init(t_i, box_length_i, num_dims_i, num_atoms_i);
  }

// Inits ______________________________________________________________________

int Sim::init(float t_i, float box_length_i, int num_dims_i, int num_atoms_i) { 
  set_t(t_i);
  set_box_length(box_length_i);
  atoms_ = new Atoms(num_dims_i, num_atoms_i);
  return 0;
}

// Sets _______________________________________________________________________

int Sim::set_t(float t_i) { t_ = t_i; return 0; }

int Sim::set_box_length(float box_length_i) { 
  box_length_ = box_length_i; return 0; 
}

// Gets _______________________________________________________________________

float Sim::get_t() const { return t_; }

float Sim::get_box_length() const { return box_length_; }

Atoms * Sim::get_atoms() const { return atoms_; }