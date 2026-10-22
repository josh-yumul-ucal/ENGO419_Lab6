#include "functions.h"
#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include <iomanip>
#include <boost/math/distributions/normal.hpp>
namespace bm = boost::math;
using namespace std;
using namespace Eigen;

MatrixXd readMatrix(const string &filename, int rows, int cols){
    ifstream file("../../../" + filename);

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
    ofstream file(name);

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

VectorXd findRedundancy(const MatrixXd &Cr, const MatrixXd &Cobs){
    int n = Cobs.rows();
    VectorXd redundancy(n);

    for (int i = 0; i < n; i++){
        redundancy(i) = Cr(i,i) / Cobs(i,i);

        if (abs(redundancy(i)) < 1e-8){
            redundancy(i) = 0.0;
        }
    }

    return redundancy;
}

VectorXd findMDB(const MatrixXd &Cobs, const MatrixXd &redundancy, double alpha, double beta){
    // Calculating noncentrality parameter (lambda)
    bm::normal_distribution<double> normal;
    
    double zAlpha = bm::quantile(normal, 1 - alpha / 2);
    double zBeta = bm::quantile(normal, 1 - beta);

    double lambda = pow(zAlpha + zBeta, 2);


}
