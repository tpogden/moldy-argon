// sim_test_a00.cpp: Tommy Ogden <t@ogden.eu>
// Description: 

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

#include "sim.h"

int main() {

    const int kNumDims = 2;

    float t = 0.0;
    float box_length = 10.0; 

    int num_atoms = 5;

    Sim sim(t, box_length, kNumDims, num_atoms);

    cout << sim.get_t() << endl;

    cout << sim.get_box_length() << endl;

    cout << sim.get_atoms()->get_num_atoms() << endl;

  // cout << "Hello" << endl;

  return 0;

}