#include <iostream>

#include "atoms.h"

// Constructors & Destructors -------------------------------------------------

Atoms::Atoms(RowVectorXf &mass_i, ArrayXXf &pos_i, ArrayXXf &vel_i) {

    init(mass_i, pos_i, vel_i);

}

// Inits

int Atoms::init(RowVectorXf &mass_i, ArrayXXf &pos_i, ArrayXXf &vel_i) { 

    set_mass(mass_i); 
    set_pos(pos_i);
    set_vel(vel_i);

    return 0; 

}

// Sets

int Atoms::set_mass(RowVectorXf &mass_i) { mass = mass_i; return 0; }

int Atoms::set_mass(float mass_i, int idx_i) { 

    mass[idx_i] = mass_i; return 0; 

}

int Atoms::set_pos(ArrayXXf &pos_i) { pos = pos_i; return 0; }

int Atoms::set_pos(VectorXf &pos_i, int idx_i) { 

    pos.col(idx_i) = pos_i; return 0;

}

int Atoms::set_pos_random(int num_dims_i, int num_atoms_i, float cell_length_i) {

    ArrayXXf rand_pos(num_dims_i, num_atoms_i);
    rand_pos.setRandom(); rand_pos = rand_pos*cell_length_i/2.0;    

    set_pos(rand_pos);

    return 0;

}

int Atoms::set_vel(ArrayXXf &vel_i) { vel = vel_i; return 0; }

int Atoms::set_vel(VectorXf &vel_i, int idx_i) { 

    vel.col(idx_i) = vel_i; return 0;

}

// Gets

RowVectorXf Atoms::get_mass() const { return mass; }

float Atoms::get_mass(int idx_i) const { return mass[idx_i]; }

ArrayXXf Atoms::get_pos() const { return pos; }

VectorXf Atoms::get_pos(int idx_i) const { return pos.col(idx_i); }

ArrayXXf Atoms::get_vel() const { return vel; }

VectorXf Atoms::get_vel(int idx_i) const { return vel.col(idx_i); }
