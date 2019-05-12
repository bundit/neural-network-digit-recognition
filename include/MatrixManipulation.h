#pragma once
#include <vector>

// alias for Matrix object
template<typename T>
using Matrix = std::vector< std::vector<T> >;

class MM {
public:
	template<typename T>
	static void printMatrix(Matrix<T>);

	template<typename T>
	static void printVector(std::vector<T>);

	template<typename T>
	static Matrix<T> transpose(Matrix<T> m);
};
// Matrix dot product
template<typename T>
Matrix<T> operator*(Matrix<T>, Matrix<T>);
// Scalar-matrix multiplication
template<typename T>
Matrix<T> operator*(double a, Matrix<T> b);
// Matrix subtraction
template<typename T>
Matrix<T> operator-(Matrix<T>, Matrix<T>);

