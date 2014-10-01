#include <iostream>

#include "atoms.h"

// Constructors & Destructors -------------------------------------------------

Atoms::Atoms(RowVectorXf &mass_i) {

    init(mass_i);

}

// Inits

int Atoms::init(RowVectorXf &mass_i) { set_mass(mass_i); return 0; }

// Sets

int Atoms::set_mass(RowVectorXf &mass_i) { mass = mass_i; return 0; }

int Atoms::set_mass(float mass_i, int idx_i) { 

    mass[idx_i] = mass_i; return 0; 

}

int Atoms::set_pos(ArrayXXf &pos_i) { pos = pos_i; return 0; }

int Atoms::set_pos(VectorXf &pos_i, int idx_i) { 

    pos.col(idx_i) = pos_i; return 0;

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
