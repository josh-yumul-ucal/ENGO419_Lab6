#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <Eigen/Dense>
#include <string>
#include <fstream>

using namespace std;
using namespace Eigen;

MatrixXd readMatrix(const string& filename, int rows, int cols);

void writeMatrix(const MatrixXd& matrix, const string& name);

VectorXd findMDB(const MatrixXd& Cobs, const VectorXd& redundancy, double alpha, double beta);

// For task D, create a new VectorXd singleMDB so that we can compute the ERV with only one MDB at a time
VectorXd findERV(const MatrixXd& A, const MatrixXd Cobs, const VectorXd& MDB);

#endif