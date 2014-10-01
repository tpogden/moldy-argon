// Hello World

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

#include "atoms.h"

int main() {

    const int num_dims = 3;

    int num_atoms = 4;

    float cell_length = 5.0;

    RowVectorXf mass_1(num_atoms); mass_1 << 1.0, 2.0, 1.0, 2.0;

    ArrayXXf pos_1 = ArrayXXf::Zero(num_dims, num_atoms);

    ArrayXXf vel_1 = ArrayXXf::Zero(num_dims, num_atoms);

    Atoms atoms_1(mass_1, pos_1, vel_1);

    cout << "Mass:" << endl;

    cout << atoms_1.get_mass() << endl;

    cout << "Pos:" << endl;

    cout << atoms_1.get_pos() << endl;

    cout << "Vel:" << endl;

    cout << atoms_1.get_vel() << endl;

    atoms_1.set_pos_random(num_dims, num_atoms, cell_length);

    cout << "Pos:" << endl;

    cout << atoms_1.get_pos() << endl;

    return 0;

}