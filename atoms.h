#ifndef ATOMS_H
#define ATOMS_H

#include <Eigen/Core>

using namespace std;
using namespace Eigen;

// Class: Atoms _______________________________________________________________

class Atoms {

  private:

    RowVectorXf mass;

  public:

    // Constructors & Destructors _____________________________________________

    Atoms(RowVectorXf &mass_i);

    // Inits

    int init(RowVectorXf &mass_i);

    // Sets

    int set_mass(RowVectorXf &mass_i);

    // Gets

    RowVectorXf get_mass() const;

};

#endif