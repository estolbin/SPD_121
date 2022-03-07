#include<iostream>
using namespace std;

#define tab "\t"

//class Iterator; 

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
		//friend class Iterator;
	}*Head, *Tail;
	size_t size;
public:

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(List::Element* Temp):Temp(Temp) {}
		~Iterator(){}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other) const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other) const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*() const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other):List()
	{
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		*this = other;
		cout << "Copy constuctor:\t" << this << endl;
	}
	Iterator begin()
	{
		return Head;
	}
	Element* end()
	{
		return nullptr;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//			Operators
	List& operator=(const List& other)
	{
		if(this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
		cout << "Copy assignment:\t" << this << endl;
		return *this;
	}
	//			Adding elements
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		//Element* New = new Element(Data);
		//New->pNext = Head;
		//Head->pPrev = New;
		//Head = New;
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr) return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}

	void insert(int Index, int Data)
	{
		if (Index > size) return;
		if (Index == 0) return push_front(Data);
		if (Index == size) return push_back(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index;i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - 1 - Index; i++) Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	//				Removing elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}

		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;

	}
	void pop_back()
	{
		if (Head == Tail) return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0) return pop_front();
		if (Index == size-1) return pop_back();
		if (Index >= size) return;

		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - i;i++) Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;

	}

	//				Methods
	void print() const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Amout elements in list: " << tab << size << endl;
	}
	void reverse_print() const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Amout elements in list: " << tab << size << endl;
	}
	//friend class Iterator;
};

//class Iterator
//{
//	List::Element* Temp;
//public:
//	Iterator(List::Element* Temp):Temp(Temp) {}
//	~Iterator(){}
//	Iterator& operator++()
//	{
//		Temp = Temp->pNext;
//		return *this;
//	}
//	Iterator operator++(int)
//	{
//		Temp = Temp->pNext;
//		return *this;
//	}
//	Iterator& operator--()
//	{
//		Temp = Temp->pPrev;
//		return *this;
//	}
//	Iterator operator--(int)
//	{
//		Temp = Temp->pPrev;
//		return *this;
//	}
//	bool operator==(const Iterator& other) const
//	{
//		return this->Temp == other.Temp;
//	}
//	bool operator!=(const Iterator& other) const
//	{
//		return this->Temp != other.Temp;
//	}
//	const int& operator*() const
//	{
//		return Temp->Data;
//	}
//	int& operator*()
//	{
//		return Temp->Data;
//	}
//};


//#define BASE_CHECK
//#define COPY_METHOD_CHECK
#define HOMEWORK


void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	List list;
	cout << "Insert size list: "; cin >> n;
	for (int i = 0; i < n;i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	cout << "Введите индекс: "; cin >> index;
	cout << "Значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);

	list.print();
	list.reverse_print();

#endif // BASE_CHECK

#ifdef COPY_METHOD_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	list.reverse_print();

	//List list2 = list;
	List list2;
	list2 = list;
	list2.print();
	list2.reverse_print();
#endif // COPY_METHOD_CHECK

#ifdef HOMEWORK
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif

}