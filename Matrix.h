#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "rectangularvectors.h"
#include "stringhelper.h"
using namespace std;


	class Matrix
	{
	private:
		int row = 0;
		int col = 0;

	public:
		int getRow() const;
		void setRow(int value);
		int getCol() const;
		void setCol(int value);
		vector<vector<float>> matrixData;

		Matrix(int r, int c);
		Matrix(int r, int c, vector<float>& data);

		Matrix(int r, int c, float data);


		//needs work
		Matrix(const Matrix& other);
		//Sets individual values in the matrix
		void SetCell(int r, int c, int val);


		//Fills matrix values using an array
		//neds an error message
		void Fill(std::vector<float>& data);
		void FillVertically(std::vector<float>& data);
		void printMatrix();
		std::wstring ToString();

		static Matrix ToMatrix(float x);

		static Matrix Sigmoid(Matrix* x);

		static Matrix Tanh(Matrix* x);

		static Matrix Concatenation(Matrix* x, Matrix* y);


		static Matrix HadmardProduct(Matrix* x, Matrix* y);

		static bool GreaterThan01(Matrix x);

		//dot product that returns the matrix
		static Matrix DotProductMatrix(Matrix* x, Matrix* y);

		//dot product that returns single value
		static float DotProductValue(Matrix* x, Matrix* y);

	
		static float DotProductAssistant(Matrix* x, Matrix* y);

	
		static Matrix OuterProduct(Matrix* x, Matrix* y);







	};


