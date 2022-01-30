#include<iostream>
#include<string>

using namespace std;

class Employee
{
	// можно еще добавить должность, название отдела, табельный номер...
	std::string first_name;
	std::string last_name;
public:
	const string& get_first_name() const { return first_name; }
	const string& get_last_name() const { return last_name; }
	void set_first_name(const string& first_name) { this->first_name = first_name; }
	void set_last_name(const string& last_name) { this->last_name = last_name; }

	Employee(const string& last_name, const string& first_name)
	{
		set_first_name(first_name);
		set_last_name(last_name);
		cout << "EConstructor:\t" << this << endl;

	}
	~Employee()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	virtual void print() const
	{
		cout << last_name << " " << first_name << endl;
	}

	virtual float get_amount() const { return 0; }
};

class PermanentEmployee : public Employee
{
	float salary;
public:
	float get_salary() const { return salary; }
	void set_salary(float salary) { this->salary = salary; }

	PermanentEmployee(const string& first_name, const string& last_name, float salary) :Employee(first_name, last_name)
	{
		set_salary(salary);
		cout << "PEConstructor:\t" << this << endl;
	}
	~PermanentEmployee()
	{
		cout << "PEDectructor:\t" << this << endl;
	}

	void print() const
	{
		Employee::print();
		cout << salary << endl;
	}

	float get_amount() const
	{
		return salary;
	}
};

class HourlyEmployee :public Employee
{
	float qty_hours;
	float cost_per_hour;
public:
	float get_qty_hours() const { return qty_hours; }
	float get_cost_per_hour() const { return cost_per_hour; }
	void set_qty_hours(float qty_hours) { this->qty_hours = qty_hours; }
	void set_cost_per_hour(float cost_per_hour) { this->cost_per_hour = cost_per_hour; }

	HourlyEmployee(const string& first_name, const string& last_name, float qty_hours, float cost_per_hour) :Employee(first_name, last_name)
	{
		set_qty_hours(qty_hours);
		set_cost_per_hour(cost_per_hour);
		cout << "HEConstrucor:\t" << this << endl;
	}
	~HourlyEmployee()
	{
		cout << "HEDestructor:\t" << this << endl;
	}

	void print() const
	{
		Employee::print();
		cout << qty_hours << " * " << cost_per_hour << " = " << qty_hours * cost_per_hour << endl;
	}

	float get_amount() const
	{
		return qty_hours * cost_per_hour;
	}

};

//#define CLASS_CHECK

void print_line()
{
	cout << "\n---\n";
}

void main()
{
	setlocale(LC_ALL, "");

#ifdef CLASS_CHECK
	Employee emp("Иванов", "Иван");
	emp.print();

	PermanentEmployee pemp("Петров", "Петр", 20000);
	pemp.print();
	cout << "Amount: " << pemp.get_amount() << endl;

	HourlyEmployee hemp("Сидоров", "Сидор", 150, 300);
	hemp.print();
	cout << "Amout: " << hemp.get_amount() << endl;

#endif // CLASS_CHECK

	Employee* department[] = {
		new PermanentEmployee("Петров", "Петр", 20000),
		new PermanentEmployee("Сидорова", "Снежана", 30000),
		new PermanentEmployee("Васнецова", "Алия", 50000),
		new HourlyEmployee("Кузнецов", "Василий", 50, 110.25),
		new HourlyEmployee("Смирнов", "Александр", 120, 190)
	};

	float res = 0;
	print_line();
	for (int i = 0; i < sizeof(department) / sizeof(Employee*);i++)
	{
		department[i]->print();
		if (i < (sizeof(department) / sizeof(Employee*)) - 1) 
		{
			print_line();
		}
		res += department[i]->get_amount();
	}

	cout << "\n----------------------------------------------\n";
	cout << "Зарплата отдела составляет: " << res << endl;


}