//
//
//
//

#ifndef ATOMS_H
#define ATOMS_H

#include <Eigen/Core>

using namespace std;
using namespace Eigen;

// Class: Atoms _______________________________________________________________

class Atoms {

 private:

  int num_dims_;
  int num_atoms_;

  RowVectorXf mass_;
  ArrayXXf pos_;
  ArrayXXf vel_;

 public:

  // Constructors & Destructors _______________________________________________

  Atoms(int num_dims_i, int num_atoms_i, RowVectorXf &mass_i, ArrayXXf &pos_i, 
        ArrayXXf &vel_i);

  Atoms(int num_dims_i, int num_atoms_i);

  // Inits ____________________________________________________________________

  int init(int num_dims_i, int num_atoms_i, RowVectorXf &mass_i, 
           ArrayXXf &pos_i, ArrayXXf &vel_i);

  int init(int num_dims_i, int num_atoms_i);

  // Sets _____________________________________________________________________

  int set_num_dims(int num_dims_i);
  int set_num_atoms(int num_atoms_i);  

  int set_mass(RowVectorXf &mass_i);
  int set_mass(float mass_i, int idx_i);

  int set_pos(ArrayXXf &pos_i);
  int set_pos(VectorXf &pos_i, int idx_i);
  int set_pos_random(float cell_length_i);

  int set_vel(ArrayXXf &vel_i);
  int set_vel(VectorXf &vel_i, int idx_i);

  // Gets _____________________________________________________________________

  int get_num_dims() const;
  int get_num_atoms() const;

  RowVectorXf get_mass() const;
  float get_mass(int idx_i) const;

  ArrayXXf get_pos() const;
  VectorXf get_pos(int idx_i) const;

  ArrayXXf get_vel() const;
  VectorXf get_vel(int idx_i) const;

  string get_info() const;

};

#endif