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

int Atoms::set_pos_random(float box_length_i) {
  ArrayXXf rand_pos(get_num_dims(), get_num_atoms());
  rand_pos.setRandom(); rand_pos = rand_pos*box_length_i/2.0;    
  set_pos(rand_pos);
  return 0;
}

int Atoms::move(ArrayXXf &move_i) { pos_ += move_i; return 0; }

int Atoms::move(VectorXf &move_i, int idx_i) {
  VectorXf pos = pos_.col(idx_i);
  pos_.col(idx_i) = pos + move_i; 
  return 0;
}

int Atoms::set_vel(ArrayXXf &vel_i) { vel_ = vel_i; return 0; }

int Atoms::set_vel(VectorXf &vel_i, int idx_i) { 
  vel_.col(idx_i) = vel_i; return 0;
}

int Atoms::accl(ArrayXXf &accl_i) { vel_ += accl_i; return 0; }

int Atoms::accl(VectorXf &accl_i, int idx_i) {
  VectorXf vel = vel_.col(idx_i);
  vel_.col(idx_i) = vel + accl_i;
  return 0;
}

int Atoms::step_with_vel_verlet(float t_step_i) {

  // Calculate Force Before, No force for now
  // ArrayXXf force_before = ArrayXXf::Zero(num_dims_, num_atoms_);

  // Update Positions
  ArrayXXf step_move(num_dims_, num_atoms_);
  step_move = vel_*t_step_i; //+ force_before*t_step_i*t_step_i/2;
  move(step_move);

  // Calculate Force After, No force for now
  // ArrayXXf force_after = ArrayXXf::Zero(num_dims_, num_atoms_);

  // Update Velocities
  // ArrayXXf accl(num_dims_, num_atoms_);
  // step_accl = force_before + force_after*t_step_i/2;
  // accl(step_accl);

  return 0;
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

string Atoms::get_json_mass() const {

  stringstream mass_ss;
  mass_ss.precision(4);

  mass_ss << "\"mass\": " << "[";

  for (int n = 0; n < get_num_atoms()-1; n++) {
    mass_ss << get_mass(n) << ", ";
  }
  // Last atom
  mass_ss << get_mass(get_num_atoms()-1);

  mass_ss << "]";

  return mass_ss.str();

}

string Atoms::get_json_pos() const {

  stringstream pos_ss;
  pos_ss.precision(4);

  pos_ss << "\"pos\": " << "[" << endl;

  for (int n = 0; n < get_num_atoms()-1; n++) {
    pos_ss << "[";
    for (int i = 0; i < get_num_dims()-1; i++) {

      pos_ss << get_pos(n)[i] << ", ";

    } 
    pos_ss << get_pos(n).tail(1) << "]," << endl;
  }
  // Last atom
  pos_ss << "[";
  for (int i = 0; i < get_num_dims()-1; i++) {
    pos_ss << get_pos(get_num_atoms()-1)[i] << ", ";
  } 
  pos_ss << get_pos(get_num_atoms()-1).tail(1) << "]";

  pos_ss << "]";

  return pos_ss.str();

}

string Atoms::get_json_vel() const {

  stringstream vel_ss;
  vel_ss.precision(4);

  vel_ss << "\"vel\": " << "[" << endl;

  for (int n = 0; n < get_num_atoms()-1; n++) {
    vel_ss << "[";
    for (int i = 0; i < get_num_dims()-1; i++) {

      vel_ss << get_vel(n)[i] << ", ";

    } 
    vel_ss << get_vel(n).tail(1) << "]," << endl;
  }
  // Last atom
  vel_ss << "[";
  for (int i = 0; i < get_num_dims()-1; i++) {
    vel_ss << get_vel(get_num_atoms()-1)[i] << ", ";
  } 
  vel_ss << get_vel(get_num_atoms()-1).tail(1) << "]";

  vel_ss << "]";

  return vel_ss.str();

}

string Atoms::get_json() const {

  stringstream json_ss;
  json_ss.precision(4);

  json_ss << "{" << endl;

  json_ss << get_json_mass();

  json_ss << "," << endl;

  json_ss << get_json_pos();

  json_ss << "," << endl;

  json_ss << get_json_vel();

  json_ss << endl << "}";

  return json_ss.str();

}

int Atoms::write_json_file(ofstream & json_o_file_i) {

  if (json_o_file_i.is_open()) {
      json_o_file_i << get_json();
      return 0;
  }

  else {
    cout << "Filestream closed. Unable to write file." << endl; 
    return 1;
  }

}

int Atoms::write_json_file(string & json_filename_i) {

    ofstream json_o_file;
    json_o_file.open(json_filename_i.c_str());
   
    write_json_file(json_o_file);

    json_o_file.close();

    return 0;

}

