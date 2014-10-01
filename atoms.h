#ifndef ATOMS_H
#define ATOMS_H

#include <Eigen/Core>

using namespace std;
using namespace Eigen;

// Class: Atoms _______________________________________________________________

class Atoms {

  private:

    RowVectorXf mass;
    ArrayXXf pos;
    ArrayXXf vel;

  public:

    // Constructors & Destructors _____________________________________________

    Atoms(RowVectorXf &mass_i);

    // Inits

    int init(RowVectorXf &mass_i);

    // Sets

    int set_mass(RowVectorXf &mass_i);
    int set_mass(float mass_i, int idx_i);

    int set_pos(ArrayXXf &pos_i);
    int set_pos(VectorXf &pos_i, int idx_i);

    int set_vel(ArrayXXf &vel_i);
    int set_vel(VectorXf &vel_i, int idx_i);

    // Gets

    RowVectorXf get_mass() const;
    float get_mass(int idx_i) const;

    ArrayXXf get_pos() const;
    VectorXf get_pos(int idx_i) const;

    ArrayXXf get_vel() const;
    VectorXf get_vel(int idx_i) const;

};

#endif