#include "functions.h"
#include <fstream>
#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

MatrixXd readMatrix(const string &filename, int rows, int cols){
    ifstream file(filename);

    if(!file.is_open()){
        throw runtime_error("Cannot open file: " + filename);
    }

    MatrixXd matrix(rows, cols);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            
        }
    }
}
