#pragma once
#include <vector>

template<typename T>
using Matrix = std::vector<std::vector<T>>;

class MM {
public:
	template<typename T>
	static void printMatrix(Matrix<T>);

	template<typename T>
	static void printVector(std::vector<T>);

	template<typename T>
	static Matrix<T> transpose(Matrix<T> m);
};

template<typename T>
Matrix<T> operator*(Matrix<T>, Matrix<T>);

template<typename T>
Matrix<T> operator*(double a, Matrix<T> b);

template<typename T>
Matrix<T> operator-(Matrix<T>, Matrix<T>);

