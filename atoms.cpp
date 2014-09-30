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

// Gets

RowVectorXf Atoms::get_mass() const { return mass; }