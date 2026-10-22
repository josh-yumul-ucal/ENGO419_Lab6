#include "functions.h"
#include <iostream>
#include <fstream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main(){
    // readMatrix() checks matrix size, no need to check
    MatrixXd xhat = readMatrix("raw_xhat.txt", 5, 2);
    MatrixXd Cxhat = readMatrix("raw_Cxhat.txt", 10, 10);
    MatrixXd Cobs = readMatrix("Cl.txt", 26, 26);
    MatrixXd A = readMatrix("A.txt", 26, 10);

    // cout << "Adjusted Coordinates:\n" << xhat << endl;
    // cout << "Covariance Matrix of Parameters\n" << Cxhat << endl;   
    // cout << "Covariance Matrix of Observations\n" << Cobs << endl;
    // cout << "Design matrix\n" << A << endl;

    MatrixXd Cr = Cobs - A * Cxhat * A.transpose();
    cout << "Covariance of Residuals" << Cr << endl;

    // VectorXd redundancy = findRedundancy(Cr, Cobs);

    MatrixXd redundancy = Cr * Cobs.inverse();

    cout << "Redundancy Numbers\n" << redundancy.diagonal() << endl;

    // VectorXd MDB = findMDB(Cobs, redundancy, alpha, beta);

    // cout << "Minimum detectable blunders\n" << MDB << endl;

    return 0;
}
