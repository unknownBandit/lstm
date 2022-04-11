#pragma once

#include <string>
#include <cmath>
#include "stringhelper.h"

namespace ConsoleApp1
{
	class Vector
	{
	private:
		double x = 0;
		double y = 0;
		double z = 0;

	public:
		double getX() const;
		void setX(double value);
		double getY() const;
		void setY(double value);
		double getZ() const;
		void setZ(double value);

		Vector();

		Vector(double x, double y, double z);

		Vector(const Vector& other);

	private:
		double GetLength();

	public:
		double getLength() const;

		void Scale(double factor);

		bool Unitize();

		void Add(Vector* other);

		std::wstring ToString();

		Vector* operator + (const Vector& b);
		double operator *(const Vector& b);

		//C# TO C++ CONVERTER TODO TASK: Operator overloads are only converted if the first parameter type is the same as the enclosing type:
		static Vector* operator *(double a, const Vector& b);
		//static methods
		static Vector* Addition(Vector* a, Vector* b);

		static double DotProduct(Vector* a, Vector* b);

		static Vector* CrossProduct(Vector* a, Vector* b);
	};

}

