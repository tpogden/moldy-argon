// Hello World

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

#include "atoms.h"

int main() {

    const int num_dims = 3;

    int num_atoms = 4;

    RowVectorXf mass_1(num_atoms); mass_1 << 1.0, 2.0, 1.0, 2.0;

    // Test init, get_mass

    Atoms atoms_1(mass_1);

    cout << atoms_1.get_mass() << endl;

    // set pos

    ArrayXXf pos_1 = ArrayXXf::Zero(num_dims, num_atoms);

    atoms_1.set_pos(pos_1);

    VectorXf pos_atom_2(num_dims); pos_atom_2 << 2.0, 4.0, 6.0;

    atoms_1.set_pos(pos_atom_2, 2);

    cout << atoms_1.get_pos() << endl;

    cout << atoms_1.get_pos(2) << endl;

    return 0;

}