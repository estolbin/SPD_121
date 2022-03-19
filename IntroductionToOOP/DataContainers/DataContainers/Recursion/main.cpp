#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "�� � �������" << endl;
		return;
	}
	cout << "�� �� " << floor << " ����� " << endl;
	elevator(floor - 1);
	cout << "�� �� " << floor << " ����� " << endl;
}

int factorial(int n)
{
	if (n == 1) return 1;
	return n * factorial(n - 1);
}

double power(double a, int n)
{
	if (n == 0) return 1;
	return a * power(a, n - 1);
}

//#define ELEVATOR_CHECK
#define HOME_WORK

void main()
{
	setlocale(LC_ALL, "");

#ifdef ELEVATOR_CHECK
	int floor;
	cout << "������� ����� �����: "; cin >> floor;
	elevator(floor);
#endif // ELEVATOR_CHECK


#ifdef HOME_WORK
	int num;
	cout << "������� �����, ��� ����������: "; cin >> num;
	cout << "��������� ����� �����: " << factorial(num) << "." << endl;

	double a;
	int n_pow;

	cout << "�����: "; cin >> a;
	cout << "�������: "; cin >> n_pow;

	cout << "����� " << a << " � ������� " << n_pow << " ����� " << power(a, n_pow) << endl;
#endif // HOME_WORK


}