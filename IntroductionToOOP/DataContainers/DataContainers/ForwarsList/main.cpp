//ForwarsList
#include<iostream>
using namespace std;

class Element
{
	int Data;
	Element* pNext;
	static unsigned int count;
public:
	Element(int Data, Element* pNext = nullptr):Data(Data), pNext(pNext) 
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwarsList;
};

unsigned int Element::count = 0;

class ForwarsList
{
	Element* Head;
public:
	ForwarsList()
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwarsList(const ForwarsList& other): ForwarsList()
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
	}
	~ForwarsList()
	{
		while (Head)
		{
			pop_front();
		}
		cout << "LDestructor:\t" << this << endl;
	}
	//			Operators
	ForwarsList& operator=(const ForwarsList& other)
	{
		if (this == &other) return *this;

		while (Head)
		{
			pop_front();
		}

		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		return *this;
	}

	//			Adding elements
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}

	void insert(int index, int Data)
	{
		if (index > Head->count)
		{
			cout << "Выход за пределы списка." << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}

	void erase(int index)
	{

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;

		delete Erased;
	}

	//		Removing elements
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	//			Methods
	void print() const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << Head->count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwarsList list;

	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();

	//list.pop_front();
	//list.print();

	//int index;
	//int value;
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.insert(index, value);

	//list.print();

	list.erase(2);
	list.print();

	ForwarsList list2 = list;
	list2.print();

	ForwarsList list3;
	list3 = list;
	list3.print();

}