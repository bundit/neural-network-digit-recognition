//\/\/\/\/\/\/\/\/\/\/\/\/\/\//
//                           //
//  MatrixManipulation.cpp   //
//  Author: Bundit Hongmanee //
//                           //
//\/\/\/\/\/\/\/\/\/\/\/\/\/\//

#include "../include/MatrixManipulation.h"
#include <iostream>

// Dimension Error for matrix manipulation functions
class MatrixDimensionError : public std::exception {
public:
	const char * what() const throw() {
		return "Error - Invalid matrix dimensions";
	}
};

// Operator overloader for *
// Matrix by matrix multiplication
// Implements dot product of two matrices
template<typename T> 
Matrix<T> operator*(Matrix<T> a, Matrix<T> b) {
	if (a[0].size() != b.size()) { //throw error if dimensions not compatible
		MatrixDimensionError e;
        throw e;
	}
    
	Matrix<T> result;
	
	//Standard matrix multiplication algorithm
	for (size_t i = 0; i < a.size(); i++) {
		result.push_back({});
		for (size_t j = 0; j < b[0].size(); j++) {
			result[i].push_back({});
			result[i][j] = 0;
			for (size_t k = 0; k < a[0].size(); k++) {
				result[i][j] = result[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	return result;
}

// Operator overloader for *
// Scalar-Matrix multiplication
// Returns a matrix with each index multiplied by the scalar a
template<typename T>
Matrix<T> operator*(double a, Matrix<T> b) {
    Matrix<T> result;
    
    for (size_t i = 0; i < b.size(); i++) {
        result.push_back({});
        for (size_t j = 0; j < b[0].size(); j++) {
            result[i].push_back(a * b[i][j]);
        }
    }
    return result;
}

// Operator overloader for -
// Matrix by matrix subtration
// Implements subtraction of two matrices where each respective index of matrix a minus matrix b
template<typename T>
Matrix<T> operator-(Matrix<T> a, Matrix<T> b) {
	if (a.size() != b.size() || a[0].size() != b[0].size()) {
		MatrixDimensionError e;
		throw e;
	}
	Matrix<double> r;
	for (size_t i = 0; i < a.size(); i++) {
		r.push_back({});
		for (size_t j = 0; j < a[i].size(); j++) {
			r[i].push_back(a[i][j] - b[i][j]);
		}
	}
	return r;
}

// Generate the transpose of a given matrix
template<typename T>
Matrix<T> MM::transpose(Matrix<T> m) {
	Matrix<T> trans;

	for (size_t i = 0; i < m[0].size(); i++) {
		trans.push_back({});
		for (size_t j = 0; j < m.size(); j++) {
			trans[i].push_back(m[j][i]);
		}
	}
	return trans;
}

// Print the matrix m
template<typename T>
void MM::printMatrix(Matrix<T> m) {
	for (size_t i = 0; i < m.size(); i++) {
		for (size_t j = 0; j < m[0].size(); j++) {
            std::cout << m[i][j] << " ";
		}
        std::cout << std::endl;
	}
}

// Print the vector v
template<typename T>
void MM::printVector(std::vector<T> v) {
	for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
	}
    std::cout << std::endl;
}


// Testing Matrix Multiplication functions
void testMatrixManipulations() {
    using namespace std;
    
	Matrix<double> a{ {1,2,3},{4,5,6},{7,8,9} };
	Matrix<double> b{ {1,1,1} };
	vector<double> v{ 1,2,3 };
	Matrix<double> t;
    Matrix<double> sub1{ {-1,-2,-3},{-4,-5,-6},{-7,-8,-9} };

	cout << "Printing matrix a: " << endl;
	MM::printMatrix(a);
    cout << endl << "Printing matrix b: " << endl;
    MM::printMatrix(b);
    
	cout << endl << "Printing vector v: " << endl;
	MM::printVector(v);
    
	cout << endl << "Transposing matrix b: " << endl;
	t = MM::transpose(b);
	MM::printMatrix(t);
    
	cout << endl << "Dot product on matrix a and b: " << endl;
    MM::printMatrix(a*MM::transpose(b));
    
    cout << endl << "Subtration on matrix a and sub1" << endl;
	MM::printMatrix(a - sub1);
    
    cout << endl << "Equality on matrix a and a" << endl;
    cout << (a==a) << endl;
    
    int cons = 2;
    cout << "Constant * Matrix a" << endl;
    MM::printMatrix(cons*a);

}
//int main() {
//    testMatrixManipulations();
//}
