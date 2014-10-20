// atoms.h: Tommy Ogden <t@ogden.eu>
// Definition for Atoms (set of atoms) class.

#ifndef ATOMS_H
#define ATOMS_H

#include <Eigen/Core>
#include <fstream>

using namespace std;
using namespace Eigen;

// Represents a set of atoms. Sample usage:
// Atoms my_atoms(2, 10); // 10 atoms in 2D
// // distribute the atoms in a box [-5.0, 5.0]*[-5.0, 5.0]
// my_atoms.set_pos_random(10.0); // distribute atoms in a box [-5, 5]*[-5, 5]
class Atoms {

 private:

  int num_dims_; // Number of dimensions in the model.
  int num_atoms_; // Number of atoms in the model.

  RowVectorXf mass_; // Row array[num_atoms_] of masses for each atom.
  ArrayXXf pos_; // Array[num_dims_, num_atoms_] of position vectors for atoms. 
  ArrayXXf vel_; // Array[num_dims_, num_atoms_] of velocity vectors for atoms. 

 public:

  // Constructors & Destructors _______________________________________________

  Atoms(int num_dims_i, int num_atoms_i, RowVectorXf &mass_i, ArrayXXf &pos_i, 
        ArrayXXf &vel_i);

  // 
  Atoms(int num_dims_i, int num_atoms_i);

  // TODO Destructors!

  // Inits ____________________________________________________________________

  // Initialise the atoms, setting all values manually.
  int init(int num_dims_i, int num_atoms_i, RowVectorXf &mass_i, 
           ArrayXXf &pos_i, ArrayXXf &vel_i);

  // Initialise with atom masses = 1, positions and velocities zero vectors.
  // Just specify the number of dimensions and the number of atoms.
  int init(int num_dims_i, int num_atoms_i);

  // Sets _____________________________________________________________________

  // Set the number of dimensions in the model.
  int set_num_dims(int num_dims_i); 
  int set_num_atoms(int num_atoms_i); // Set the number of atoms in the model.
  // Set all masses with an array[num_atoms] of floats.

  int set_mass(RowVectorXf &mass_i);
  int set_mass(float mass_i, int idx_i); // Set the mass of the idx'th atom.
  // Set all positions with an array of vectors [num_dims, num_atoms].

  // Set the positions of all atoms with an array of 
  // vectors [num_dims, num_atoms].
  int set_pos(ArrayXXf &pos_i); 
  // Set the positions of the idx'th atom with a vector [num_dims]
  int set_pos(VectorXf &pos_i, int idx_i);
  // Set the positions of all the atoms with a uniform random distribution 
  // in a box [-box_length/2, box_length/2] in each dimension.
  int set_pos_random(float box_length_i);
  // Move all of the atoms with an array of vectors [num_dims, num_atoms].
  int move(ArrayXXf &move_i);
  // Move the idx'th atom with a vector [num_dims]
  int move(VectorXf &move_i, int idx_i);

  // Set the velocities of all atoms with an array of 
  // vectors [num_dims, num_atoms].
  int set_vel(ArrayXXf &vel_i);
  // Set the positions of the idx'th atom with a vector [num_dims]  
  int set_vel(VectorXf &vel_i, int idx_i);
  // Set the velocities of all the atoms with a uniform random distribution 
  // [-max_speed, max_speed] in each dimension.
  int set_vel_random(float max_speed);
  // Accelerate (i.e. increase the velocity of) all of the atoms with an array 
  // of vectors [num_dims, num_atoms]
  int accl(ArrayXXf &accl_i);
  // Accelerate (i.e. increase the velocity of) the idx'th atom with a vector
  // [num_dims].
  int accl(VectorXf &accl_i, int idx_i);

  // Integrate Newton's equations of motion for the atoms using the 'Velocity
  // Verlet' algorithm, given a time step.
  // http://en.wikipedia.org/wiki/Verlet_integration#Velocity_Verlet
  int step_with_vel_verlet(float t_step_i);

  // Gets _____________________________________________________________________


  int get_num_dims() const; // Return the number of dimensions in the model.
  int get_num_atoms() const; // Return the number of atoms in the model.

  // Return a row array [num_atoms] with the mass of each atom.
  RowVectorXf get_mass() const; 
  // Return the mass of the idx'th atom.
  float get_mass(int idx_i) const;

  // Return an array of vectors [num_dims, num_atoms] giving the positions of 
  // each of the atoms.
  ArrayXXf get_pos() const;
  // Return a vector [num_dims] giving the position of the idx'th atom.
  VectorXf get_pos(int idx_i) const;

  // Return an array of vectors [num_dims, num_atoms] giving the velocities of 
  // each of the atoms.
  ArrayXXf get_vel() const;
  // Return a vector [num_dims] giving the velocity of the idx'th atom.  
  VectorXf get_vel(int idx_i) const;

  // Returns the masses, positions and velocities, mostly for cout debugging.
  string get_info() const;

  string get_json_num_atoms() const; // Returns the number of atoms as json.
  string get_json_num_dims() const; // Returns the num of dimenstions as json.
  string get_json_mass() const; // Returns the array of masses as json. 
  string get_json_pos() const; // Returns the array of positions as json.
  string get_json_vel() const; // Returns the array of velocities as json.
  string get_json() const; // Returns the atom object in json format.

  // File Writes ______________________________________________________________

  // Write the atom in json format to a file stream object.
  int write_json_file(ofstream & json_o_file_i);
  // Write the atom in jason format to the given filename.
  int write_json_file(string & json_filename_i);

};

#endif