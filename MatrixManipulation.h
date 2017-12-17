#pragma once
#include <vector>

using namespace std;

template<typename T>
using Matrix = vector<vector<T>>;

class MatrixManipulation
{
public:
	template<typename T>
	Matrix<T> operator*(Matrix<T>);

	template<typename T>
	Matrix<T> transpose(Matrix<T>);
};