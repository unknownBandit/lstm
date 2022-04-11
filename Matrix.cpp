//====================================================================================================
//The Free Edition of C# to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-csharp-to-cplus.html
//====================================================================================================

#include "Matrix.h"
#include <format>
#include <iostream>
using namespace std;



	int Matrix::getRow() const
	{
		return row;
	}

	void Matrix::setRow(int value)
	{
		row = value;
	}

	int Matrix::getCol() const
	{
		return col;
	}

	void Matrix::setCol(int value)
	{
		col = value;
	}

	Matrix::Matrix(int r, int c)
	{
		if (c < 1 || r < 1)
		{
			throw runtime_error("INVALID NUMBER OF ROWS OR COLUMNS IN MATRIX");
		}

		this->setCol(c);
		this->setRow(r);
		//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
		//ORIGINAL LINE: matrixData = new float[row, col];
		matrixData = RectangularVectors::RectangularFloatVector(getRow(), getCol());
	}

	Matrix::Matrix(int r, int c, std::vector<float>& data)
	{
		if (c < 1 || r < 1)
		{
			throw runtime_error("INVALID NUMBER OF ROWS OR COLUMNS IN MATRIX");
		}
		this->setCol(c);
		this->setRow(r);
		//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
		//ORIGINAL LINE: matrixData = new float[row, col];
		matrixData = RectangularVectors::RectangularFloatVector(getRow(), getCol());

		int datasize = data.size();
		int count = 0;
		while (count < datasize)
		{
			for (int m = 0; m < getRow(); m++)
			{
				for (int j = 0; j < getCol(); j++)
				{
					matrixData[m][j] = data[count];
					count++;
				}
			}
		}
	}

	Matrix::Matrix(int r, int c, float data)
	{
		if (c != 1 || r != 1)
		{
			throw runtime_error("INVALID NUMBER OF ROWS OR COLUMNS IN MATRIX");
		}
		this->setCol(c);
		this->setRow(r);
		//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
		//ORIGINAL LINE: matrixData = new float[row, col];
		matrixData = RectangularVectors::RectangularFloatVector(getRow(), getCol());

		
		matrixData[0][0] = data;
					
	}

	Matrix::Matrix(const Matrix& other)
	{
		this->setCol(other.getCol());
		this->setRow(other.getRow());
	}

	void Matrix::printMatrix()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << matrixData[i][j] << " ";
			}
			
		}
	}
	void Matrix::SetCell(int r, int c, int val)
	{
		matrixData[r][c] = val;
	}

	void Matrix::Fill(std::vector<float>& data)
	{
		int datasize = data.size();
		int count = 0;
		
		while (count < datasize)
		{
			for (int m = 0; m < getRow(); m++)
			{
				for (int j = 0; j < getCol(); j++)
				{
					matrixData[m][j] = data[count];
					count++;
				}
			}
		}
	}

	void Matrix::FillVertically(std::vector<float>& data)
	{
		int datasize = data.size();
		int count = 0;
		while (count < datasize)
		{
			for (int m = 0; m < getCol(); m++)
			{
				for (int j = 0; j < getRow(); j++)
				{
					matrixData[j][m] = data[count];
					count++;
				}
			}
		}
	}

	std::wstring Matrix::ToString()
	{
		std::wstring str = L"";
		for (int i = 0; i < getRow(); i++)
		{
			for (int j = 0; j < getCol(); j++)
			{
				str += matrixData[i][j] + '\t';
			}
			str += L"\n";
		}

		return str;
	}

	

	

	Matrix Matrix::ToMatrix(float x)
	{
		Matrix(temp) = Matrix(1, 1);
		temp.matrixData[0][0] = x;

		//C# TO C++ CONVERTER TODO TASK: A 'delete temp' statement was not added since temp was used in a 'return' or 'throw' statement.
		return temp;
	}

	Matrix Matrix::Sigmoid(Matrix* x)
	{
		Matrix(temp) = Matrix(x->getRow(), x->getCol());
		for (int i = 0; i < x->getRow(); i++)
		{
			for (int j = 0; j < x->getCol(); j++)
			{
				temp.matrixData[i][j] = static_cast<float>(1.0f / (1.0f + std::exp(-x->matrixData[i][j])));
			}
		}

		//C# TO C++ CONVERTER TODO TASK: A 'delete temp' statement was not added since temp was used in a 'return' or 'throw' statement.
		return temp;
	}

	Matrix Matrix::Tanh(Matrix* x)
	{
		Matrix(temp) = Matrix(x->getRow(), x->getCol());
		for (int i = 0; i < x->getRow(); i++)
		{
			for (int j = 0; j < x->getCol(); j++)
			{
				temp.matrixData[i][j] = static_cast<float>(std::tanh(x->matrixData[i][j]));
			}
		}

		//C# TO C++ CONVERTER TODO TASK: A 'delete temp' statement was not added since temp was used in a 'return' or 'throw' statement.
		return temp;
	}

	Matrix Matrix::Concatenation(Matrix* x, Matrix* y)
	{
		if (x->getRow() != y->getRow())
		{
			throw std::runtime_error("Cannot concatenate, uneven rows:\n");
		}
		Matrix(temp) = Matrix(x->getRow(), x->getCol() + y->getCol());
		// x.matrixData.CopyTo(temp.matrixData, 0);
		//     x.matrixData.
		// y.matrixData.CopyTo(temp.matrixData, x.matrixData.Length);

		for (int i = 0; i < x->getRow(); i++)
		{
			for (int j = 0; j < x->getCol(); j++)
			{
				temp.matrixData[i][j] = x->matrixData[i][j];
			}
		}

		for (int i = 0; i < y->getRow(); i++)
		{
			for (int j = 0; j < y->getCol(); j++)
			{

				temp.matrixData[i][j + x->getCol()] = y->matrixData[i][j];
			}
		}

		//C# TO C++ CONVERTER TODO TASK: A 'delete temp' statement was not added since temp was used in a 'return' or 'throw' statement.
		return temp;
	}

	Matrix Matrix::HadmardProduct(Matrix* x, Matrix* y)
	{
		if (x->getRow() != y->getRow() || x->getCol() != y->getCol())
		{
			throw std::runtime_error("Cannot compute Hadamard product, dimensions do not match:\n");
		}
		Matrix(temp) = Matrix(x->getRow(), x->getCol());

		for (int i = 0; i < temp.getRow(); i++)
		{
			for (int j = 0; j < temp.getCol(); j++)
			{
				temp.matrixData[i][j] = x->matrixData[i][j] * y->matrixData[i][j];
			}
		}

		//C# TO C++ CONVERTER TODO TASK: A 'delete temp' statement was not added since temp was used in a 'return' or 'throw' statement.
		return temp;
	}

	 Matrix Matrix::DotProductMatrix(Matrix* x, Matrix* y)
	{
		if (x->getCol() != y->getRow())
		{
			throw runtime_error("Cannot compute Dot product, dimensions do not match:\n");
		}

		Matrix RowTemp =  Matrix(x->getCol(), 1);
		Matrix ColTemp =  Matrix(y->getRow(), 1);
		Matrix Temp = Matrix(x->getRow(), y->getCol());
		int r = 0;

		for (int i = 0; i < x->getRow(); i++)
		{
			//Get Matrix x Rows
			for (int j = 0; j < x->getCol(); j++)
			{
				RowTemp.matrixData[r] [0] = x->matrixData[i][j];
				r++;
			}
			r = 0;
			//Gets Matrix y Rows and multiplies by x row
			for (int m = 0; m < y->getCol(); m++)
			{
				for (int p = 0; p < y->getRow(); p++)
				{
					ColTemp.matrixData[r][ 0] = y->matrixData[p][ m];
					r++;
				}
				r = 0;
				Temp.matrixData[i][m] = Matrix::DotProductAssistant(&RowTemp, &ColTemp);
			}

			r = 0;
		}
		return Temp;
	}

	//dot product that returns single value
    float Matrix::DotProductValue(Matrix* x, Matrix* y)
	{
		if (x->getCol() != y->getRow())
		{
			throw runtime_error("Cannot compute Dot product, dimensions do not match:\n");
		}

		Matrix RowTemp = Matrix(x->getCol(), 1);
		Matrix ColTemp = Matrix(y->getRow(), 1);
		float value = 0.0f;
		int r = 0;

		for (int i = 0; i < x->getRow(); i++)
		{
			//Get Matrix x getRow()s
			for (int j = 0; j < x->getCol(); j++)
			{
				RowTemp.matrixData[r][ 0] = x->matrixData[i][ j];
				r++;
			}
			r = 0;
			//Gets Matrix y Rows and multiplies by x row
			for (int m = 0; m < y->getCol(); m++)
			{
				for (int p = 0; p < y->getRow(); p++)
				{
					ColTemp.matrixData[r][0] = y->matrixData[p][m];
					r++;
				}
				r = 0;

				value += Matrix::DotProductAssistant(&RowTemp, &ColTemp);
			}

			r = 0;
		}
		return value;
	}

	float Matrix::DotProductAssistant(Matrix* x, Matrix* y)
	{
		float temp = 0.0f;
		for (int i = 0; i < x->getRow(); i++)
		{
			temp += x->matrixData[i][0] * y->matrixData[i][0];
		}

		return temp;
	}

	 Matrix Matrix::OuterProduct(Matrix * x, Matrix * y)
	{
		 if (x == nullptr || y == nullptr)
		 {
			 cout << "one is null"<< endl;
			 exit(0);
		 }

		if ((x->getRow() != 1 && x->getCol() != 1) && (y->getRow() != 1 && y->getCol() != 1))
		{
			throw runtime_error("Cannot compute Outer product product, wrong input:\n");
		}

		Matrix temp = Matrix(y->matrixData.size(), x->matrixData.size());
		Matrix* Xtemp = y;

		Matrix* Ytemp = x;
		//switching size to rx1
		if (x->getCol() != 1)
		{
			int count = 0;
			
			Xtemp = new  Matrix(x->getCol(), 1);
			for (int i = 0; i < x->getRow(); i++)
			{
				for (int j = 0; j < x->getCol(); j++)
				{
					Xtemp->matrixData[count][ 0] = x->matrixData[i][ j];
					count++;

				}
			}
		}
		if (y->getCol() != 1)
		{
			int count = 0;
			Ytemp = new Matrix(y->getCol(), 1);

			for (int i = 0; i < y->getRow(); i++)
			{
				for (int j = 0; j < y->getCol(); j++)
				{
					Ytemp->matrixData[count][ 0] = y->matrixData[i][ j];
					count++;
				}
			}
		}
		for (int i = 0; i < Ytemp->getRow(); i++)
		{
			for (int j = 0; j < Xtemp->getRow(); j++)
			{
				temp.matrixData[j][ i] = Ytemp->matrixData[i][0] * Xtemp->matrixData[j][0];
			}
		}
		return temp;
	}

	 bool Matrix::GreaterThan01(Matrix x)
	 {
		 bool isit = true;
		 Matrix temp = Matrix(x.row, x.col);
		 for (int i = 0; i < x.row; i++)
		 {
			 for (int j = 0; j < x.col; j++)
			 {
				 if (temp.matrixData[i][j] > 0.01)
					 isit = false;
			 }
		 }
		 return isit;
	 }