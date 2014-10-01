// Hello World

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

#include "atoms.h"

int main() {

    // const int num_dims = 3;

    int num_atoms = 4;

    RowVectorXf mass_1(num_atoms); mass_1 << 1.0, 2.0, 1.0, 2.0;

    // Test init, get_mass

    Atoms atoms_1(mass_1);

    cout << atoms_1.get_mass() << endl;    

    // Test set_mass

    RowVectorXf mass_2(num_atoms); mass_2 << 2.0, 4.0, 2.0, 4.0;

    cout << atoms_1.get_mass() << endl;    

    // Test set_mass, get_mass individual

    atoms_1.set_mass(5.0, 2);    

    cout << atoms_1.get_mass(2) << endl;

    cout << atoms_1.get_mass() << endl;

    return 0;

}