#include "functions.h"
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace std;

int main(){
    // readMatrix() checks matrix size, no need to check
    MatrixXd xhat = readMatrix("final_xhat.txt", 5, 2);
    MatrixXd Cxhat = readMatrix("final_Cxhat.txt", 10, 10);
    MatrixXd Cobs = readMatrix("final_Cl.txt", 24, 24);
    MatrixXd A = readMatrix("final_A.txt", 24, 10);

    // cout << "Adjusted Coordinates:\n" << xhat << endl;
    // cout << "Covariance Matrix of Parameters\n" << Cxhat << endl;   
    // cout << "Covariance Matrix of Observations\n" << Cobs << endl;
    // cout << "Design matrix\n" << A << endl;

    MatrixXd Cr = Cobs - A * Cxhat * A.transpose();
    writeMatrix(Cr, "final_Cr.txt");

    // Compute redundancy matrix R
    MatrixXd redundancy = Cr * Cobs.inverse();
    VectorXd R = redundancy.diagonal();

    // NOTE: Rows 10 and 20 correspond to dist: 5-6 and angle: 1-5-7, super small because 7's position is 
    // based on an angle and distance measurement, meaning that a blunder in its position would be undetectable
    cout << "Redundancy Numbers\n" << R << endl;

    double alpha = 0.05;
    double beta = 0.80;

    VectorXd MDB = findMDB(Cobs, R, alpha, beta);

    cout << "Minimum detectable blunders\n" << MDB << endl;

    int n = MDB.size();
    MatrixXd ERV(A.cols(), n);

    for (int i = 0; i < n; i++){
    VectorXd singleMDB = VectorXd::Zero(n);

    singleMDB(i) = MDB(i);
    
    if (!isfinite(MDB(i))){
        for (int j = 0; j < ERV.rows(); j++){
            ERV(j, i) = NAN;
        }
        continue;
    }

    ERV.col(i) = findERV(A, Cobs, singleMDB);
    }

    cout << "External Reliability Vectors\n" << ERV << endl;
    writeMatrix(ERV, "ERV(backup).txt");

    return 0;
}
