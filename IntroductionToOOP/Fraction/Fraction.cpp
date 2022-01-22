#include"Fraction.h"

int Fraction::get_integer()const
{
	return integer;
}
int Fraction::get_numerator()const
{
	return numerator;
}
int Fraction::get_denominator()const
{
	return denominator;
}
void Fraction::set_integer(int integer)
{
	this->integer = integer;
}
void Fraction::set_numerator(int numerator)
{
	this->numerator = numerator;
}
void Fraction::set_denominator(int denominator)
{
	if (denominator <= 0)denominator = 1;
	this->denominator = denominator;
}

//				Constructors:
Fraction::Fraction()
{
	this->integer = 0;
	this->numerator = 0;
	this->denominator = 1;
#ifdef DEBUG
	cout << "DefaultConstruct:\t" << this << endl;
#endif // DEBUG
}
Fraction::Fraction(int integer)
{
	this->integer = integer;
	this->numerator = 0;
	this->denominator = 1;
#ifdef DEBUG
	cout << "1ArgConstructor:" << this << endl;
#endif // DEBUG
}
Fraction::Fraction(double decimal)
{
	decimal += 1e-11;
	//decimal - десятичная дробь
	//1) Сохраняем целую часть дробного числа:
	integer = decimal;	//implicit coversion (неявное преобразование)
	//2) Убираем целую часть из дробного числа:
	decimal -= integer;
	//3) Вытаскиваем максимально возможное количество десятичных разрядов 
	//из дробной части числа, и сохраняем все эти разряды в числитель:
	denominator = 1e+9;	//1*10^9
	numerator = decimal * denominator;
	reduce();
	cout << "1ArgConstructor:" << this << endl;
}
Fraction::Fraction(int numerator, int denominator)
{
	this->integer = 0;
	this->numerator = numerator;
	set_denominator(denominator);
#ifdef DEBUG
	cout << "Constructor\t" << this << endl;
#endif // DEBUG
}
Fraction::Fraction(int integer, int numerator, int denominator)
{
	this->integer = integer;
	this->numerator = numerator;
	set_denominator(denominator);
#ifdef DEBUG
	cout << "Constructor\t" << this << endl;
#endif // DEBUG
}
Fraction::Fraction(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
#ifdef DEBUG
	cout << "CopyConstructor:" << this << endl;
#endif // DEBUG
}
Fraction::~Fraction()
{
#ifdef DEBUG
	cout << "Destructor\t" << this << endl;
#endif // DEBUG
}

//				Operators:
Fraction& Fraction::operator=(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
#ifdef DEBUG
	cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG
	return *this;
}
Fraction& Fraction::operator*=(const Fraction& other)
{
	return *this = *this * other;
}
Fraction& Fraction::operator/=(const Fraction& other)
{
	return *this = *this / other;
}

//				Type-cast operators:
Fraction::operator int()const
{
	return integer;
}
Fraction::operator double()const
{
	return integer + (double)numerator / denominator;
}

//				Methods:
Fraction& Fraction::reduce()
{
	//https://www.webmath.ru/poleznoe/formules_12_7.php
	int numerator_gcf = (this->numerator); unsigned int denominator_gcf = this->denominator;
	while (numerator_gcf != 0 && denominator_gcf != 0)
	{
		if (abs(numerator_gcf) > denominator_gcf) { numerator_gcf = abs(numerator_gcf) % denominator_gcf; }
		else { denominator_gcf = denominator_gcf % abs(numerator_gcf); }
	}
	int gcf = numerator_gcf + denominator_gcf;
	if (this->numerator < 0) { this->numerator = -(abs(this->numerator) / gcf); }
	else { this->numerator = this->numerator / gcf; }
	this->denominator = this->denominator / gcf;
	return  *this;
}
Fraction& Fraction::to_proper()
{
	integer += numerator / denominator;
	numerator %= denominator;
	return *this;
}
Fraction& Fraction::to_improper()
{
	numerator += integer * denominator;
	integer = 0;
	return *this;
}
Fraction Fraction::inverted()
{
	to_improper();
	return Fraction(denominator, numerator);
}

void Fraction::print()const
{
	if (integer)cout << integer;
	if (numerator)
	{
		if (integer)cout << "(";
		cout << numerator << "/" << denominator;
		if (integer)cout << ")";
	}
	else if (integer == 0)cout << 0;
	cout << endl;
}



Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction	//Явно вызываем конструктор, и создаем временный безымянный объект,
	(//этот объект сразу же возвращается на место вызова.
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator/(Fraction left, Fraction right)
{
	return left * right.inverted();
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())cout << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())cout << "(";
		cout << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())cout << ")";
	}
	else if (obj.get_integer() == 0)cout << 0;
	return os;
}
std::istream& operator>>(std::istream& is, Fraction& obj)
{
	/*int integer, numerator, denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);*/
	obj = Fraction();	//Обнуляем объект - задаем ему значение по умолчанию
	const int SIZE = 256;
	char buffer[SIZE] = {};
	//is >> buffer;
	is.getline(buffer, SIZE);	//Вводит строку с пробелами
	char delimiters[] = "/( )";
	char* number[3] = {};	//Сюда будут сохраняться числа из исходной строки (из buffer)
	int n = 0;	//считает, сколько чисел мы вытащили из исходной строки
	/*
	for(start; stop; step)
	{

	}
	*/
	//http://cplusplus.com/reference/cstring/
	//http://cplusplus.com/reference/cstring/strtok/
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		number[n++] = pch;
	}
	switch (n)
	{
	case 1:obj.set_integer(atoi(number[0])); break;
		//atoi(str);	//принимает строку, и возвращает int-овое значение числа, 
						//хранящегося в этой строке
		//atoi(str);	//преобразует строку в число
	case 2:
		obj.set_numerator(atoi(number[0]));
		obj.set_denominator(atoi(number[1]));
		break;
	case 3:
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
	}
	return is;
}