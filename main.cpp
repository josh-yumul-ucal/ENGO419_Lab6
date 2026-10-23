#include "functions.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Eigen/Dense>
#include <string>
#include <cmath>

using namespace Eigen;
using namespace std;

int main(){
    // readMatrix() checks matrix size, no need to check, causes comp error if files:
    // 1. don't match matrix dimension size 2. are unreachable to the program
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

    // NOTE: Rows 10 and 20 correspond to dist: 5-7 and angle: 1-5-7, super small because 7's position is 
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

    
    cout << "\nGlobal External Reliability Measure" << endl;
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

    // PRINT SECTION: basically copy and pasted the for loops above and replaced all the couts with ofstream objects
    // Used comma-delimited headers to let Python do the parsing
    // Can switch to Excel if Python too inconvenient

    // Redundancy numbers
    ofstream redundancyFile("../results_redundancy.txt");
    redundancyFile << setprecision(15);
    redundancyFile << "obs,redundancy\n";
    for (int i = 0; i < n; i++){
        redundancyFile << i + 1 << "," << R(i) << "\n";
    }
    redundancyFile.close();
    cout << "Results successfully written to: results_redundancy.txt" << endl;

    // MDBs [m for distances, rad for angles]
    ofstream mdbFile("../results_MDB.txt");
    mdbFile << setprecision(15);
    mdbFile << "obs,MDB\n";
    for (int i = 0; i < n; i++){
        mdbFile << i + 1 << "," << MDB(i) << "\n";
    }
    mdbFile.close();
    cout << "Results successfully written to: results_MDB.txt" << endl;

    // ERV, one row per observation, one column per parameter [m]
    ofstream ervFile("../results_ERV.txt");
    ervFile << setprecision(15);
    ervFile << "obs";
    for (int j = 0; j < ERV.rows(); j++){
        ervFile << "," << names[j];
    }
    ervFile << "\n";
    for (int i = 0; i < n; i++){
        ervFile << i + 1;
        for (int j = 0; j < ERV.rows(); j++){
            ervFile << "," << ERV(j, i);
        }
        ervFile << "\n";
    }
    ervFile.close();
    cout << "Results successfully written to: results_ERV.txt" << endl;

    // Three most affect parameters of ERV [mm]
    ofstream top3File("../results_top3_ERV.txt");
    top3File << setprecision(15);
    top3File << "obs,param1,value1_mm,param2,value2_mm,param3,value3_mm\n";
    for (int i = 0; i < n; i++){
        top3File << i + 1;

        if (!isfinite(MDB(i))){
            top3File << ",nan,nan,nan,nan,nan,nan\n";
            continue;
        }

        VectorXd absERV = ERV.col(i).cwiseAbs();
        for (int j = 0; j < 3; j++){
            int index;
            absERV.maxCoeff(&index);
            top3File << "," << names[index] << "," << ERV(index, i) * 1000;
            absERV(index) = -1;
        }
        top3File << "\n";
    }
    top3File.close();
    cout << "Results successfully written to: results_top3_ERV.txt" << endl;

    // Global external reliability measure (unitless)
    MatrixXd CxhatInv = Cxhat.inverse();
    ofstream globalFile("../results_global_ERV.txt");
    globalFile << setprecision(15);
    globalFile << "obs,global_ERV\n";
    for (int i = 0; i < n; i++){
        globalFile << i + 1 << ",";

        if (!isfinite(MDB(i))){
            globalFile << "nan\n";
            continue;
        }

        VectorXd gradX = ERV.col(i);
        globalFile << gradX.transpose() * CxhatInv * gradX << "\n";
    }
    globalFile.close();
    cout << "Results successfully written to: results_global_ERV.txt" << endl;

    return 0;
}
