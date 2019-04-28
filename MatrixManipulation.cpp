// MatrixManipulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrixManipulation.h"
#include "NetLayer.h"
#include <vector>
#include <iostream>

using namespace std;

//Error throwing class for matrix dimension errors with dot products
class MatrixDimensionError : public std::exception {
public:
	const char * what() const throw() {
		return "Error with matrices dimensions";
	}
};
//
//Operator overloader for *
//Implements dot product of two matrices
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

//Operator overloader for -
//Impplements subtraction of two matrices
template<typename T>
Matrix<T> operator-(Matrix<T> a, Matrix<T> b) {
	if (a.size() != b.size() || a[0].size() != b[0].size()) {
		MatrixDimensionError e;
		throw e;
	}
	Matrix<double> r;
	for (size_t i = 0; i < a.size(); i++) {
		r.push_back({});
		for (size_t j = 0; j < a[0].size(); j++) {
			r[i].push_back(a[i][j] - b[i][j]);
		}
	}
	return r;
}

//Generate the transpose of a given matrix
template<typename T>
static Matrix<T> MM::transpose(Matrix<T> m) {
	Matrix<T> trans;

	for (size_t i = 0; i < m[0].size(); i++) {
		trans.push_back({});
		for (size_t j = 0; j < m.size(); j++) {
			trans[i].push_back(m[j][i]);
		}
	}
	return trans;
}

//Generates a (single row) vector from a column vector in matrix data type
template<typename T>
static vector<T> MM::colVecToVec(Matrix<T> m) {
	
	vector<double> vec;
	for (size_t i = 0; i < m.size(); i++) {
		vec.push_back(m[i][0]);
	}

	return vec;
}

//Print the matrix m
template<typename T>
static void MM::printMatrix(Matrix<T> m) {
	for (size_t i = 0; i < m.size(); i++) {
		for (size_t j = 0; j < m[0].size(); j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

//Print the vector v
template<typename T>
static void MM::printVector(vector<T> v) {
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

//Test function to solve linker errors
void test() {

	Matrix<double> a{ {1,2,3},{4,5,6},{7,8,9} };
	Matrix<double> b{ {1,1,1} };
	vector<double> v{ 1,2,3 };
	Matrix<double> t;

	cout << "Printing matrix a: " << endl;
	MM::printMatrix(a);
	cout << endl << "Printing vector v: " << endl;
	MM::printVector(v);
	cout << endl << "Transposing matrix b: " << endl;
	t = MM::transpose(b);
	MM::printMatrix(t);
	cout << endl << "Converting column bt to vector: " << endl;
	MM::printVector(MM::colVecToVec(t));
	cout << endl << "Dot product on matrix a and b: " << endl;
	MM::printMatrix(a*b);
	MM::printMatrix(a - a);

	//Matrix<string> s{ {} };
	//vector<string> ss{};
	//MM::printMatrix(s);
	//MM::printVector(ss);
}



