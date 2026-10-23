#include "functions.h"
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <string>
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
    double beta = 0.20;

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
    
    // Prints ERV to terminal, disabled for aesthetic reasons
    // cout << "External Reliability Vectors\n" << ERV << endl;
    writeMatrix(ERV, "ERV(backup).txt");

    string names[10] = {"X1", "Y1", "X3", "Y3", "X5", "Y5", "X6", "Y6", "X7", "Y7"};

    cout << "\nThree most affected parameters per observation [mm]" << endl;

    for (int i = 0; i < ERV.cols(); i++){
        cout << "Obs: " << i + 1 << endl;

        if (!isfinite(MDB(i))){
            cout << "Not checkable due to zero redundancy" << endl;
            continue;
        }

        // Within the loop, find the absolute values of each column of ERV
        VectorXd absERV = ERV.col(i).cwiseAbs();

        for (int j = 0; j < 3; j++){
            int index; 
            // &index sets it so that the maxCoeff function stores the index of the largest element in absERV
            absERV.maxCoeff(&index); 

            cout << names[index] << " = " << ERV(index, i) * 1000 << "  ";
            // Sets the current largest element to -1 so that it moves on to the next largest, is done 3 times to find the three largest
            absERV(index) = -1;
        }
        cout << endl;

    }

    
    cout << "\nGlobal External Reliability" << endl;
    for (int i = 0; i < n; i++){
        cout << "Obs: " << i + 1 << endl;

        if (!isfinite(MDB(i))){
            cout << "Not checkable due to zero redundancy" << endl;
            continue;
        }

        VectorXd gradX = ERV.col(i);
        double globalERV = gradX.transpose() * Cxhat.inverse() * gradX;

        cout << "lambda_x = " << globalERV << endl;

    }

    return 0;
}
