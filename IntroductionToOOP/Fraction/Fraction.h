#pragma once
#pragma warning(disable:4326)
#include<iostream>
using std::cin;
using std::cout;
using std::endl;



#define DEBUG

class Fraction;	//Просто объявление класса
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);

class Fraction	//Объявление и описание класса
{
	int integer;		//Целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель
public:
	int get_integer()const;
	int get_numerator()const;
	int get_denominator()const;
	void set_integer(int integer);
	void set_numerator(int numerator);
	void set_denominator(int denominator);

	//				Constructors:
	Fraction();
	explicit Fraction(int integer);
	Fraction(double decimal);
	Fraction(int numerator, int denominator);
	Fraction(int integer, int numerator, int denominator);
	Fraction(const Fraction& other);
	~Fraction();

	//				Operators:
	Fraction& operator=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	//				Type-cast operators:
	explicit operator int()const;
	explicit operator double()const;

	//				Methods:
	Fraction& reduce();
	Fraction& to_proper();
	Fraction& to_improper();
	Fraction inverted();

	void print()const;
};

std::ostream& operator<<(std::ostream& os, const Fraction& obj);
std::istream& operator>>(std::istream& is, Fraction& obj);