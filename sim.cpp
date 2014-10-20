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

  Sim::Sim(float box_length_i, int num_dims_i, int num_atoms_i) {
    init(0.0, box_length_i, num_dims_i, num_atoms_i);
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

int Sim::set_atoms_pos_random_in_box() { 
  atoms_->set_pos_random(box_length_);
  return 0;
}

// Gets _______________________________________________________________________

float Sim::get_t() const { return t_; }

float Sim::get_box_length() const { return box_length_; }

Atoms * Sim::get_atoms() const { return atoms_; }

string Sim::get_json() const {
  stringstream json_ss;
  json_ss << "{" << endl;
  json_ss << "\"t\": " << t_ << "," << endl;
  json_ss << "\"atoms\": " << endl; 
  json_ss << atoms_->get_json() << endl;
  json_ss << "}";
  return json_ss.str();
}

// File Writes ________________________________________________________________

int Sim::write_json_file(ofstream & json_o_file_i) {
    if (json_o_file_i.is_open()) {
        json_o_file_i << get_json(); return 0;
    }
    else {
        cout << "Filestream closed. Unable to write file." << endl; return 1;
    }    
}

int Sim::write_json_file(string & json_filename_i) {
    ofstream json_o_file;
    json_o_file.open(json_filename_i.c_str());
    write_json_file(json_o_file);
    json_o_file.close();
    return 0;
}

// Run ________________________________________________________________________

int Sim::run(int num_t_steps_i, float t_step_i, char bc_type_i,
  string & json_filename_i) {

  // cout.precision(3);

  t_ = 0.0;

  ofstream json_file;
  json_file.open(json_filename_i.c_str());

  json_file << "[" << endl;

  for (int i = 0; i < num_t_steps_i; i++) {

    write_json_file(json_file);
    json_file << "," << endl;
    
    atoms_->step_with_vel_verlet(t_step_i, box_length_, bc_type_i);
    t_ += t_step_i;

    // Show progress
    cout << "  "<< (int)100.0*i/num_t_steps_i << "%\r";
    cout.flush();

  }

  write_json_file(json_file);

  json_file << endl << "]" << endl;

  json_file.close();

  cout << "  100%\r";
  cout << endl << "Done. Written to " << json_filename_i << "." << endl;

  return 0;

}
