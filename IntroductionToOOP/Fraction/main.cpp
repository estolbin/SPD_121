#include"Fraction.h"

//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSIONS_FROM_OTHER_TYPES_TO_CLASS
#define CONVERSIONS_FROM_CLASS_TO_OTHER_TYPES

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;		//Default constructor
	A.print();

	double b = 5;
	Fraction B = 5;	//Single-argument constructor
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;
	E.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);
	Fraction C = A * B;
	C.print();
	(A / B).print();
	A *= B;
	//A.print();
	cout << A << endl;
	//cout << 123 << endl;  
#endif // OPERATORS_CHECK

#ifdef TYPE_CONVERSIONS_BASICS
			//Warning: conversion from type to type possible loss of data.
//		l-value = r-value;
	int a = 2;		//No conversion
	double b = 3;	//Conversion from less to more
	int c = b;		//Conversion from more to less without data loss
	int d = 5.2;	//Conversion from more to less with data loss
	char e = 515;	//Conversion from int to char. Truncation (Усечение, урезание)
					//Arithmetical overflow
	cout << (int)e << endl;
#endif // TYPE_CONVERSIONS_BASICS

#ifdef CONVERSIONS_FROM_OTHER_TYPES_TO_CLASS
	//1. Single-argument constructor
	//2. Assignment operator

	//(type)value - C-Like notation
	//type(value) - Functional notation

	double a = 2;	//Conversion from 'int' to 'double'
	5;//Числовая константа типа 'int'
	Fraction A = (Fraction)5;	//Conversion from 'int' to 'Fraction'
	A;//Переменная типа 'Fraction'
	cout << A << endl;

	Fraction B;	//Default constructor
	cout << "\n--------------------------\n";
	B = Fraction(8);
	cout << "\n--------------------------\n";
	cout << B << endl;
#endif // CONVERSIONS_FROM_OTHER_TYPES_TO_CLASS

	/*
	----------------------------------------------------
	operator type()
	{
		
	}
	----------------------------------------------------
	*/

	/*Fraction A(5);
	int a = A;
	cout << a << endl;
	Fraction B(2, 1, 7);
	double b = B;
	cout << b << endl;*/

	//cout << ((double)Fraction(1, 2) == (double)Fraction(5, 10))<< endl;

	Fraction A = 2.76;	//From double to Fraction
						//From other to class (преобразование другого типа в наш тип)
	cout << A << endl;

	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;
}

//23 + 54*(88 - 33)^2 - 123 / 2