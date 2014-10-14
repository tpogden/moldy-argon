//
//
//
//

#include <iostream>

#include "atoms.h"

// Constructors & Destructors _________________________________________________


Atoms::Atoms(int num_dims_i, int num_atoms_i, RowVectorXf &mass_i, 
             ArrayXXf &pos_i, ArrayXXf &vel_i) {
  init(num_dims_i, num_atoms_i, mass_i, pos_i, vel_i);
}

Atoms::Atoms(int num_dims_i, int num_atoms_i) {
  init(num_dims_i, num_atoms_i);
}

// Inits ______________________________________________________________________

int Atoms::init(int num_dims_i, int num_atoms_i, RowVectorXf &mass_i, 
                ArrayXXf &pos_i, ArrayXXf &vel_i) { 
  set_num_dims(num_dims_i);
  set_num_atoms(num_atoms_i);

  set_mass(mass_i); 
  set_pos(pos_i);
  
  set_vel(vel_i);
  return 0; 
}

int Atoms::init(int num_dims_i, int num_atoms_i) {
  set_num_dims(num_dims_i);
  set_num_atoms(num_atoms_i);

  RowVectorXf mass_ones = RowVectorXf::Ones(get_num_atoms());
  set_mass(mass_ones);

  ArrayXXf pos_zero = ArrayXXf::Zero(get_num_dims(), get_num_atoms());
  set_pos(pos_zero);

  ArrayXXf vel_zero = ArrayXXf::Zero(get_num_dims(), get_num_atoms());
  set_vel(vel_zero);

  return 0;
}

// Sets _______________________________________________________________________

int Atoms::set_num_dims(int num_dims_i) { num_dims_ = num_dims_i; return 0; }

int Atoms::set_num_atoms(int num_atoms_i) { 
  num_atoms_ = num_atoms_i; return 0; 
} 

int Atoms::set_mass(RowVectorXf &mass_i) { mass_ = mass_i; return 0; }

int Atoms::set_mass(float mass_i, 
                    int idx_i) { mass_[idx_i] = mass_i; return 0; }

int Atoms::set_pos(ArrayXXf &pos_i) { pos_ = pos_i; return 0; }

int Atoms::set_pos(VectorXf &pos_i, int idx_i) { 
  pos_.col(idx_i) = pos_i; return 0;
}

int Atoms::set_pos_random(float cell_length_i) {
  ArrayXXf rand_pos(get_num_dims(), get_num_atoms());
  rand_pos.setRandom(); rand_pos = rand_pos*cell_length_i/2.0;    
  set_pos(rand_pos);
  return 0;
}

int Atoms::set_vel(ArrayXXf &vel_i) { vel_ = vel_i; return 0; }

int Atoms::set_vel(VectorXf &vel_i, int idx_i) { 
  vel_.col(idx_i) = vel_i; return 0;
}

// Gets _______________________________________________________________________

int Atoms::get_num_dims() const { return num_dims_; }

int Atoms::get_num_atoms() const { return num_atoms_; }

RowVectorXf Atoms::get_mass() const { return mass_; }

float Atoms::get_mass(int idx_i) const { return mass_[idx_i]; }

ArrayXXf Atoms::get_pos() const { return pos_; }

VectorXf Atoms::get_pos(int idx_i) const { return pos_.col(idx_i); }

ArrayXXf Atoms::get_vel() const { return vel_; }

VectorXf Atoms::get_vel(int idx_i) const { return vel_.col(idx_i); }

string Atoms::get_info() const {

  stringstream info_ss;
  info_ss.precision(4);
  info_ss << "Mass:" << endl << get_mass() << endl;
  info_ss << "Pos:" << endl << get_pos() << endl; 
  info_ss << "Vel:" << endl << get_vel(); 
  return info_ss.str();

}
