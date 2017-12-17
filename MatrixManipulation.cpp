// MatrixManipulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrixManipulation.h"
#include "NetLayer.h"
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
Matrix<T> operator*(Matrix<T> a, Matrix<T> b) {
	if (a[0].size() != b.size()) {
		//problem with matrix sizes cannot do multiplication
		//error class to be added later
		cout << "bad matrix dimensions" << endl;
		cout << "size of m1 = " << a[0].size() << " size of m2 = " << b.size() << endl;
 		Matrix<T> m;
		return m;
	}

	Matrix<T> result;
	
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

template<typename T>
static void MM::printMatrix(Matrix<T> m) {
	for (size_t i = 0; i < m.size(); i++) {
		for (size_t j = 0; j < m[0].size(); j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}
template<typename T>
static void MM::printVector(vector<T> m) {
	for (size_t i = 0; i < m.size(); i++) {
		cout << m[i] << " ";
	}
	cout << endl;
}

void test() {
	std::cout << std::endl;

	Matrix<double> matrix_a = { { 1, 2, 3 },{ 4, 5, 6 } };
	Matrix<double> matrix_b = { { 7, 8 },{ 9, 10 },{ 11, 12 } };
	std::vector<double> v = {1,2,3};
	std::cout << "Matrix a: " << std::endl;
	MM::printMatrix(matrix_a);
	std::cout << "Matrix b: " << std::endl;
	MM::printMatrix(matrix_b);

	//check transpose
	std::cout << "checking transpose of a (should have 2 columns, 3 rows): " << std::endl;
	Matrix<double> transposed = MM::transpose(matrix_a);
	MM::printMatrix(transposed);
	std::cout << "checking transpose of b (should have 3 columns, 2 rows): " << std::endl;
	MM::printMatrix(MM::transpose(matrix_b));

	//matrix_a * v;

	//check dot product overload
	std::cout << "checking dot product overload: " << std::endl;
	Matrix<double> overl = matrix_a * matrix_b;
	MM::printMatrix(overl);
}



