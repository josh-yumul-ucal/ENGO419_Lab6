#include "functions.h"
#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include <iomanip>
#include <limits>
#include <boost/math/distributions/normal.hpp>
namespace bm = boost::math;
using namespace std;
using namespace Eigen;

MatrixXd readMatrix(const string &filename, int rows, int cols){
    ifstream file("../" + filename);

    if(!file.is_open()){
        throw runtime_error("Cannot open file: " + filename);
    }

    MatrixXd matrix(rows, cols);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(!(file >> matrix(i,j))){
                throw runtime_error("Error reading file: " + filename);
            }
        }
    }
    return matrix;
}

void writeMatrix(const MatrixXd& matrix, const string& name){
    ofstream file("../" + name);

    if (!file.is_open()){
        throw runtime_error("Error: Could not write matrix");
    }

    // file << fixed << setprecision(6);

    // for (int i = 0; i < matrix.rows(); i++){
    //     for (int j = 0; j < matrix.cols(); j++){
    //         file << matrix(i,j);

    //         if (j < matrix.cols() - 1){
    //             file << " ";
    //         }
    //     }
    //     file << "\n";
    // }
    // file.close();

    // Uses IOFormat object from Eigen library to print matrices
    IOFormat format(FullPrecision, DontAlignCols, " ", "\n");
    file << matrix.format(format);

    cout << "Matrix successfully written to: " << name << endl;
}


VectorXd findMDB(const MatrixXd &Cobs, const VectorXd &redundancy, double alpha, double beta){
    // Calculating noncentrality parameter (lambda)
    bm::normal_distribution<double> normal;

    double zAlpha = bm::quantile(normal, 1 - alpha / 2);
    double zBeta = bm::quantile(normal, 1 - beta);

    double delta = zAlpha + zBeta;
    cout << "Delta0: " << delta << endl;

    int n = Cobs.rows();
    VectorXd MDB(n);

    // Iterating through all residuals
    for (int i = 0; i < n; i++){
        // Standard deviation of the i-th observation
        double sigmaObs = sqrt(Cobs(i,i));

        // An observation with zero redundancy is not checked by any other observation,
        // so no blunder in it can be detected (MDB is infinite)
        if (redundancy(i) < 1e-8){
            MDB(i) = numeric_limits<double>::infinity();
            continue;
        }

        // MDB_i = sqrt(lambda) * sigma_i / sqrt(r_i)
        MDB(i) = delta * sigmaObs / sqrt(redundancy(i));
    }
    return MDB;
}

VectorXd findERV(const MatrixXd &A, const MatrixXd Cobs, const VectorXd &MDB){
    MatrixXd P = Cobs.inverse();
    return (A.transpose() * P * A).inverse() * A.transpose() * P * MDB;
}

