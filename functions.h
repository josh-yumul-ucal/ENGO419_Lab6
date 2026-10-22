#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <Eigen/Dense>
#include <string>
#include <fstream>

using namespace std;
using namespace Eigen;

MatrixXd readMatrix(const string& filename, int rows, int cols);

void writeMatrix(const MatrixXd& matrix, const string& name);

VectorXd findRedundancy(const MatrixXd& Cr, const MatrixXd& Cobs);

VectorXd findMDB(const MatrixXd& Cobs, const MatrixXd& redundancy, double alpha, double beta);

#endif