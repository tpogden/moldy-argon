// atoms.cpp: Tommy Ogden <t@ogden.eu>
// Description: 

#include <iostream>

#include "atoms.h"

const float PI = atan(1)*4;

// Maxwell-Boltzmann PDF for a single dimension
float mb_pdf_1d(float a, float v){
    return 1/sqrt(2.0*PI)/a * exp(-pow(v/a,2)/2.);
}

// Atoms class

Atoms::Atoms(int num_dims_i, int num_atoms_i, RowVectorXf &mass_i, 
             ArrayXXf &pos_i, ArrayXXf &vel_i) {
  init(num_dims_i, num_atoms_i, mass_i, pos_i, vel_i);
}

Atoms::Atoms(int num_dims_i, int num_atoms_i) {
  init(num_dims_i, num_atoms_i);
}

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
  ArrayXXf rand_pos(num_dims_, num_atoms_);
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

// TODO: Doc
int Atoms::apply_toroidal_box_bc(float box_length_i) {
  for (int idx = 0; idx < num_atoms_; idx++) {
    for (int d = 0; d < num_dims_; d++) {    
      if (pos_.col(idx)[d] < -box_length_i/2) // Low boundary in each dim
        pos_.col(idx)[d] = box_length_i/2;
      else if (pos_.col(idx)[d] > box_length_i/2) // High boundary in each dim
        pos_.col(idx)[d] = -box_length_i/2;
    }
  }
  return 0;
}

// TODO: Doc
int Atoms::apply_bounce_box_bc(float box_length_i) {
  for (int idx = 0; idx < num_atoms_; idx++) {
    for (int d = 0; d < num_dims_; d++) {    
      if (pos_.col(idx)[d] <= -box_length_i/2) // Low boundary in each dim
        vel_.col(idx)[d] = -vel_.col(idx)[d];
      else if (pos_.col(idx)[d] >= box_length_i/2) // High boundary in each dim
        vel_.col(idx)[d] = -vel_.col(idx)[d];
    }
  }
  return 0;    
}

int Atoms::apply_box_bc(float box_length_i, char bc_type_i) {

  if (bc_type_i == 't')
    apply_toroidal_box_bc(box_length_i);
  else if (bc_type_i == 'b')
    apply_bounce_box_bc(box_length_i);

  return 0;

}

int Atoms::set_vel(ArrayXXf &vel_i) { vel_ = vel_i; return 0; }

int Atoms::set_vel(VectorXf &vel_i, int idx_i) { 
  vel_.col(idx_i) = vel_i; return 0;
}

int Atoms::set_vel_random(float max_speed_i) {
  ArrayXXf rand_vel(get_num_dims(), get_num_atoms());
  rand_vel.setRandom(); rand_vel = rand_vel*max_speed_i;    
  set_vel(rand_vel);
  return 0;
}

// TODO: Document rejection method
int Atoms::set_vel_mb(float a_i, float vel_max_i) {
  // Max value of the PDF is at 0
  float p_max = mb_pdf_1d(a_i, 0.0);
  bool accept; // TODO: Doc
  float p, v_test; // TODO: doc here

  ArrayXXf vel(get_num_dims(), get_num_atoms());

  for (int idx = 0; idx < num_atoms_; idx++) {
    for (int d = 0; d < num_dims_; d++) { 
      accept = false;
      // TODO: Document this loop
      while (accept == false) {
        // Generate a psuedorandom float between -vel_max_i and vel_max_i
        v_test = (float)rand()/RAND_MAX*vel_max_i*2.0 - vel_max_i;
        // Generate a psuedorandom float between 0 and p_max
        p = (float)rand()/RAND_MAX*p_max;
        if (p <= mb_pdf_1d(a_i, v_test)) {
          vel(d, idx) = v_test;
          accept = true;
        }
      }
    }
  }
  set_vel(vel);
  return 0;
}

int Atoms::accl(ArrayXXf &accl_i) { vel_ += accl_i; return 0; }

int Atoms::accl(VectorXf &accl_i, int idx_i) {
  VectorXf vel = vel_.col(idx_i);
  vel_.col(idx_i) = vel + accl_i;
  return 0;
}

// Same as above but with boundary conditions
int Atoms::step_with_vel_verlet(float t_step_i, float box_length_i, 
  char bc_type_i) {

  // Calculate Force Before, No force for now
  // ArrayXXf force_before = ArrayXXf::Zero(num_dims_, num_atoms_);

  // Update Positions
  ArrayXXf step_move(num_dims_, num_atoms_);
  step_move = vel_*t_step_i; //+ force_before*t_step_i*t_step_i/2;
  move(step_move);

  apply_box_bc(box_length_i, bc_type_i);

  // apply_toroidal_box_bc(box_length_i);

  // Calculate Force After, No force for now
  // ArrayXXf force_after = ArrayXXf::Zero(num_dims_, num_atoms_);

  // Update Velocities
  // ArrayXXf accl(num_dims_, num_atoms_);
  // step_accl = force_before + force_after*t_step_i/2;
  // accl(step_accl);

  return 0;

}

int Atoms::get_num_dims() const { return num_dims_; }

int Atoms::get_num_atoms() const { return num_atoms_; }

RowVectorXf Atoms::get_mass() const { return mass_; }

float Atoms::get_mass(int idx_i) const { return mass_[idx_i]; }

ArrayXXf Atoms::get_pos() const { return pos_; }

VectorXf Atoms::get_pos(int idx_i) const { return pos_.col(idx_i); }

// TODO: Doc. Vector from a to b.
VectorXf Atoms::get_vector(int a_i, int b_i) const { 
  return get_pos(b_i) - get_pos(a_i); 
}

float Atoms::get_distance(int a_i, int b_i) const { 
  return get_vector(a_i, b_i).norm();
}

// VectorXf Atoms::

ArrayXXf Atoms::get_vel() const { return vel_; }

VectorXf Atoms::get_vel(int idx_i) const { return vel_.col(idx_i); }

VectorXf Atoms::get_speed() const {
  VectorXf speed(num_atoms_);
  for (int idx = 0; idx < num_atoms_; idx++)
    speed[idx] = get_speed(idx);
  return speed;
}

float Atoms::get_speed(int idx_i) const { 
  VectorXf vel = vel_.col(idx_i);
  return vel.norm();
}

// TODO: get_ave_speed()

string Atoms::get_info() const {
  stringstream info_ss;
  info_ss.precision(4);
  info_ss << "Mass:" << endl << get_mass() << endl;
  info_ss << "Pos:" << endl << get_pos() << endl; 
  info_ss << "Vel:" << endl << get_vel(); 
  return info_ss.str();
}

string Atoms::get_json_num_atoms() const {
  stringstream num_atoms_ss;
  num_atoms_ss << "\"num_atoms\": ";
  num_atoms_ss << get_num_atoms();
  return num_atoms_ss.str();   
}

string Atoms::get_json_num_dims() const {
  stringstream num_dims_ss;
  num_dims_ss << "\"num_dims\": ";
  num_dims_ss << get_num_dims();
  return num_dims_ss.str();   
}

string Atoms::get_json_mass() const {
  stringstream mass_ss;
  mass_ss.precision(4);
  mass_ss << "\"mass\": " << "[";
  for (int n = 0; n < get_num_atoms()-1; n++)
    mass_ss << get_mass(n) << ", ";
  // Last atom
  mass_ss << get_mass(get_num_atoms()-1) << "]";
  return mass_ss.str();
}

string Atoms::get_json_pos() const {
  stringstream pos_ss;
  pos_ss.precision(4);
  pos_ss << "\"pos\": " << "[" << endl;
  for (int n = 0; n < get_num_atoms()-1; n++) {
    pos_ss << "[";
    for (int i = 0; i < get_num_dims()-1; i++)
      pos_ss << get_pos(n)[i] << ", ";
    pos_ss << get_pos(n).tail(1) << "]," << endl;
  }
  // Last atom
  pos_ss << "[";
  for (int i = 0; i < get_num_dims()-1; i++)
    pos_ss << get_pos(get_num_atoms()-1)[i] << ", ";
  pos_ss << get_pos(get_num_atoms()-1).tail(1) << "]]";
  return pos_ss.str();
}

string Atoms::get_json_vel() const {
  stringstream vel_ss;
  vel_ss.precision(4);
  vel_ss << "\"vel\": " << "[" << endl;
  for (int n = 0; n < get_num_atoms()-1; n++) {
    vel_ss << "[";
    for (int i = 0; i < get_num_dims()-1; i++)
      vel_ss << get_vel(n)[i] << ", ";
    vel_ss << get_vel(n).tail(1) << "]," << endl;
  }
  // Last atom
  vel_ss << "[";
  for (int i = 0; i < get_num_dims()-1; i++) {
    vel_ss << get_vel(get_num_atoms()-1)[i] << ", ";
  } 
  vel_ss << get_vel(get_num_atoms()-1).tail(1) << "]]";
  return vel_ss.str();
}

string Atoms::get_json() const {
  stringstream json_ss;
  json_ss.precision(4);
  json_ss << "{" << endl;
  // Append the num atoms
  json_ss << get_json_num_atoms() << "," << endl;
  // Append the num dimenstions
  json_ss << get_json_num_dims() << "," << endl;
  // Append the masses
  json_ss << get_json_mass() << "," << endl;
  // Append the positions
  json_ss << get_json_pos() << "," << endl;
  // Append the velocities
  json_ss << get_json_vel() << endl << "}";
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
