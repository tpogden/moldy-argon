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

    float max_speed = 1.0;

    int num_atoms = 5;

    Sim sim(box_length, kNumDims, num_atoms);    

    // TODO: Does box_length need to be in sim, or in atoms? Where else will it
    // used? PBCs?

    sim.get_atoms()->set_pos_random(box_length);

    sim.get_atoms()->set_vel_random(max_speed);

    cout << sim.get_box_length() << endl;
    cout << sim.get_atoms()->get_num_atoms() << endl;

    cout << "Start:" << endl;
    cout << sim.get_t() << endl;
    cout << sim.get_atoms()->get_pos() << endl;

    int num_t_steps = 10;
    float t_step = 0.1;

    sim.run(num_t_steps, t_step);

    cout << "End:" << endl;
    cout << sim.get_t() << endl;    
    cout << sim.get_atoms()->get_pos() << endl;

  return 0;

}