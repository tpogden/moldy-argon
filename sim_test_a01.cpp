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

    int num_atoms = 10;

    Sim sim(box_length, kNumDims, num_atoms);    

    sim.get_atoms()->set_pos_random(box_length);
    sim.get_atoms()->set_vel_random(max_speed);

    cout << "Start:" << endl;
    cout << sim.get_t() << endl;
    cout << sim.get_atoms()->get_pos() << endl;

    int num_t_steps = 100;
    float t_step = 0.1;

    string filename = "sim.json";

    sim.run(num_t_steps, t_step, filename);

    cout << "End:" << endl;
    cout << sim.get_t() << endl;    
    cout << sim.get_atoms()->get_pos() << endl;

    cout << sim.get_json() << endl;

  return 0;

}