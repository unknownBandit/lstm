#include "Vector.h"

namespace ConsoleApp1
{

	double Vector::getX() const
	{
		return x;
	}

	void Vector::setX(double value)
	{
		x = value;
	}

	double Vector::getY() const
	{
		return y;
	}

	void Vector::setY(double value)
	{
		y = value;
	}

	double Vector::getZ() const
	{
		return z;
	}

	void Vector::setZ(double value)
	{
		z = value;
	}

	Vector::Vector()
	{
		this->setX(0);
		this->setY(0);
		this->setZ(0);
	}

	Vector::Vector(double x, double y, double z)
	{
		this->setX(x);
		this->setY(y);
		this->setZ(z);
	}

	Vector::Vector(const Vector& other)
	{
		this->setX(other.getX());
		this->setY(other.getY());
		this->setZ(other.getZ());
	}

	double Vector::GetLength()
	{
		double sql = this->getX() * this->getX() + this->getY() * this->getY() + this->getZ() * this->getZ();
		double len = std::sqrt(sql);
		return len;
	}

	double Vector::getLength() const
	{
		return GetLength();
	}

	void Vector::Scale(double factor)
	{
		this->setX(this->getX() * factor);
		this->setY(this->getY() * factor);
		this->setZ(this->getZ() * factor);
	}

	bool Vector::Unitize()
	{
		double len = this->GetLength();
		if (len <= 0)
		{
			return false;
		}
		this->setX(this->getX() / len);
		this->setY(this->getY() / len);
		this->setZ(this->getZ() / len);
		return true;

	}

	void Vector::Add(Vector* other)
	{
		this->setX(this->getX() + other->getX());
		this->setY(this->getY() + other->getY());
		this->setZ(this->getZ() + other->getZ());
	}

	std::wstring Vector::ToString()
	{
		return StringHelper::formatSimple(L"[{0}, {1}, {2}]", this->getX(), this->getY(), this->getZ());
	}

	Vector* Vector::operator + (const Vector& b)
	{
		return Vector::Addition(this, b);
	}

	double Vector::operator *(const Vector& b)
	{
		return Vector::DotProduct(this, b);
	}

	//C# TO C++ CONVERTER TODO TASK: Operator overloads are only converted if the first parameter type is the same as the enclosing type:
	Vector* Vector::operator *(double a, const Vector& b)
	{
		Vector* (*(*v)) = new Vector(b);
		v->Scale(a);

		//C# TO C++ CONVERTER TODO TASK: A 'delete v' statement was not added since v was used in a 'return' or 'throw' statement.
		return v;
	}

	Vector* Vector::Addition(Vector* a, Vector* b)
	{
		double newx = a->getX() + b->getX();
		double newy = a->getY() + b->getY();
		double newz = a->getZ() + b->getZ();
		Vector* (*(*v)) = new Vector(newx, newy, newz);

		//C# TO C++ CONVERTER TODO TASK: A 'delete v' statement was not added since v was used in a 'return' or 'throw' statement.
		return v;
	}

	double Vector::DotProduct(Vector* a, Vector* b)
	{
		return a->getX() * b->getX() + a->getY() * b->getY() + a->getZ() * b->getZ();
	}

	Vector* Vector::CrossProduct(Vector* a, Vector* b)
	{
		double x = a->getY() * b->getZ() - a->getZ() * b->getY();
		double y = a->getZ() * b->getX() - a->getX() * b->getZ();
		double z = a->getX() * b->getY() - a->getY() * b->getX();
		return new Vector(x, y, z);
	}
}
