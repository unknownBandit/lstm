#include<iostream>
#include "LSTM.h"
#include "Matrix.h"



	int main()
	{
		LSTM* foward = new LSTM();
		foward->Run(99);
		std::vector<float> fwa = { 1, 2, 3 };
		std::vector<float> fwb = { 4, 5 };
		Matrix m1 =  Matrix(1, 3, fwa);

		//you dont really need those they were just test all you need is the run function
		Matrix m2 = Matrix(2, 1, fwb);
		//Matrix m3 = Matrix::OuterProduct(&m1, &m2);
		//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		//std::wcout << m3.ToString() << std::endl;

		//C# TO C++ CONVERTER TODO TASK: A 'delete m2' statement was not added since m2 was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete m1' statement was not added since m1 was passed to a method or constructor. Handle memory management manually.
		delete foward;
	}
