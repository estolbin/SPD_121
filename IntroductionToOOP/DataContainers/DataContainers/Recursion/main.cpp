#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже " << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже " << endl;
}

//int factorial(int n)
long long int factorial(int n)
{
	//if (n == 1) return 1;
	//return n * factorial(n - 1);
	return n == 1 ? 1 : n * factorial(n - 1);
}

double power(double a, int n)
{
	//if (n == 0) return 1;
	////else if (n < 0) return 1 / a * power(a, n + 1);
	//else if (n < 0) return power(1 / a, -n);
	//else return a * power(a, n - 1);
	return n == 0 ? 1 : n > 0 ? a * power(a, n - 1) : power(1 / a, -n);
}

//#define ELEVATOR_CHECK
#define HOME_WORK

void main()
{
	setlocale(LC_ALL, "");

#ifdef ELEVATOR_CHECK
	int floor;
	cout << "Введите номер этажа: "; cin >> floor;
	elevator(floor);
#endif // ELEVATOR_CHECK


#ifdef HOME_WORK
	int num;
	cout << "Введите число, для факториала: "; cin >> num;
	cout << "Факториал числа равен: " << factorial(num) << "." << endl;

	double a;
	int n_pow;

	cout << "Число: "; cin >> a;
	cout << "Степень: "; cin >> n_pow;

	cout << "Число " << a << " в степени " << n_pow << " равно " << power(a, n_pow) << endl;
#endif // HOME_WORK


}