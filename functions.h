#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <Eigen/Dense>
#include <string>
#include <fstream>

using namespace std;
using namespace Eigen;

MatrixXd readMatrix(const string& filename, int rows, int cols);




#endif