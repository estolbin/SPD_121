#include<iostream>
#include<string>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List<T>;
	}*Head, *Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp):Temp(Temp)
		{
#ifdef DEBUG
			cout << "BItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstBaseIterator()
		{
#ifdef DEBUG
			cout << "BItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool operator==(const ConstBaseIterator& other) const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other) const
		{
			return this->Temp != other.Temp;
		}
		const T& operator*() const
		{
			return Temp->Data;
		}
	};
public:

	class ConstIterator: public ConstBaseIterator
	{
	public:
		ConstIterator(List::Element* Temp):ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "CItDestructor:\t" << this << endl;
#endif // DEBUG
		}
		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp):ConstReverseIterator(Temp){}
		~ReverseIterator(){}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	ConstIterator cbegin() const
	{
		return Head;
	}
	ConstIterator cend() const
	{
		return nullptr;
	}
	ConstReverseIterator crbegin() const
	{
		return Tail;
	}
	ConstReverseIterator crend() const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<T>& il) :List()
	{
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other):List()
	{
		*this = other;
		cout << "Copy constuctor:\t" << this << endl;
	}
	~List()
	{
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
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}

		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr) return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Index, T Data)
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

template<typename T>
void print(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}

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
	List<int> list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List<int>::ConstReverseIterator it = list.crbegin(); it != list.crend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	print(list);

	List<double> d_list = { 2.5, 3.14, 5.2, 8.3 };
	for (double i : d_list) cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator rit = d_list.rbegin(); rit != d_list.rend(); ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;

	List<std::string> s_list = { "Have", "a", "nice", "day" };
	for (std::string i : s_list) cout << i << tab; cout << endl;

	for (List<std::string>::ReverseIterator rit = s_list.rbegin(); rit != s_list.rend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;
#endif

}