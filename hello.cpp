// Hello World

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

int main() {

    const int num_dims = 3;

    int num_atoms = 10;

    cout << "Hello World." << endl;

    ArrayXXf pos = ArrayXXf::Zero(num_dims, num_atoms);

    cout << "Pos:" << endl;

    cout << pos << endl;

    cout << "Pos[0]:" << endl;

    cout << pos.col(0) << endl; // = mat2.col(j);

    ArrayXf pos_1(num_dims); pos_1 << 1.0, 2.0, 3.0;

    pos.col(1) = pos_1;

    cout << "Pos:" << endl;

    cout << pos << endl;

// mat1.row(i) = mat2.col(j);

    // Matrix<float, num_dims, Dynamic> pos;

    // MatrixXf pos(num_dims, num_atoms);


    // VectorXf pos_b(3); pos_b << 1.0, 2.0, 3.0;

    // cout << pos_b << endl;

    return 0;

}