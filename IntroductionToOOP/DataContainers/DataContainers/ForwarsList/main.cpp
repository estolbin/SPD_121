//ForwardList
#include<iostream>
using namespace std;

class ForwardList;

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

	friend class ForwardList;
    friend class Iterator;
    friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

unsigned int Element::count = 0;

class Iterator
{
    Element* Temp;
    public:
    Iterator(Element* Temp):Temp(Temp)
    {
       // cout << "ItConstructor:\t" << this << endl;
    }
    ~Iterator()
    {
        //cout << "ItDestructor:\t" << this << endl;
    }
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

class ForwardList
{
	Element* Head;
    unsigned int size;
public:
    Element* getHead() const { return Head; }
    unsigned int get_size() const { return size; }
    Iterator begin() { return Head; }
    Iterator end() { return nullptr; }
	ForwardList()
	{
		Head = nullptr;
        size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
    ForwardList(const initializer_list<int>& il):ForwardList()
    {
        //cout << typeid(il.begin()).name() << endl;

        for (int const* it = il.begin(); it != il.end(); it++)
        {
            push_back(*it);
        }
    }
	ForwardList(const ForwardList& other): ForwardList()
	{
	//	Element* Temp = other.Head;
	//	while (Temp)
	//	{
	//		push_back(Temp->Data);
	//		Temp = Temp->pNext;
	//	}

        *this = other;
        cout << "CopyConstructor:\t" << endl;
	}
    ForwardList(ForwardList&& other)
    {
        *this = std::move(other);
        cout << "MoveConstructor:\t" << this << endl;
    }
	~ForwardList()
	{
		while (Head)
		{
			pop_front();
		}
		cout << "LDestructor:\t" << this << endl;
	}
	//			Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;

		while (Head)
		{
			pop_front();
		}

        for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
        {
            push_back(Temp->Data);
        }
        cout << "CopyAssignment:\t" << this << endl;
        return *this;

	//	Element* Temp = other.Head;
	//	while (Temp)
	//	{
	//		push_back(Temp->Data);
	//		Temp = Temp->pNext;
	//	}
	//	return *this;
	}
    ForwardList& operator=(ForwardList&& other)
    {
        if (this == &other) return *this;
        while (Head) pop_front();
        this->Head = other.Head;
        this->size = other.size;
        other.Head = nullptr;
        other.size = 0;
        cout << "MoveAssignment:\t" << this << endl;
        return *this;
    }

    const int& operator[](unsigned int index)const
    {
        Element* Temp = Head;
        for (int i = 0; i < index; i++) Temp = Temp->pNext;
        return Temp->Data;
    }
    int& operator[](unsigned int index)
    {
        Element* Temp = Head;
        for (int i = 0; i< index; i++) Temp = Temp->pNext;
        return Temp->Data;
    }

	//			Adding elements
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
        Head = new Element(Data, Head);
        size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
        size++;
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
		//Element* New = new Element(Data);
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
        Temp->pNext = new Element(Data, Temp->pNext);
        size++;
	}

	void erase(int index)
	{
        // проверки
        if (index == 0) return pop_front();
        if (index == Head->count - 1) return pop_back();
        if (index >= Head->count)
        {
            cout << "Error: out of range" << endl;
            return;
        }
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;

		delete Erased;
        size--;
	}

	//		Removing elements
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
        size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
        size--;
	}

	//			Methods
	void print() const
	{
		//Element* Temp = Head;
		//while (Temp)
		//{
		//	cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		//	Temp = Temp->pNext;
		//}
		//cout << "Количество элементов списка: " << Head->count << endl;
//        for (Element* Temp = Head; Temp; Temp++)
//                cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
//
//        cout << "Количество элементов списка: " << size << endl;
//        cout << "Общее количество элементов : " << Head->count << endl;
        for (Iterator it = Head; it != nullptr; it++)
            cout << *it << "\t";
        cout << endl;
	}
    void unique()
    {
        // перебрать элементы массива и удалить не уникальные. 
        sort();
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
        {
            Element* Check = Temp->pNext;
            if (Temp->Data == Check->Data)
            {
                Temp->pNext = Temp->pNext->pNext;
                delete Check;
            }
        }
    }
    void sort()
    {
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
        {
            for (Element* Temp2 = Head; Temp2 != Temp->pNext; Temp2 = Temp2 -> pNext)
            {
                if (Temp2->pNext == nullptr) break;
                Element* Next = Temp2->pNext;
                if (Temp2->Data > Next->Data)
                {
                    int t = Temp2->Data;
                    Temp2->Data = Next->Data;
                    Next->Data = t;
                }
            }
        }
    }

    void reverse()
    {
        // создать временный список
        ForwardList temp;
        // скопировать элементы в обратном порядку
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
            temp.push_front(Temp->Data);

        // удалить текущий лист
        while (Head) pop_front();

        // перенести из временного списка в текущий
        *this = temp;
    }
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
    ForwardList cat = left;
    for (Element* Temp = right.getHead(); Temp; Temp = Temp->pNext)
        cat.push_back(Temp->Data);
    return cat;
}

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;

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

	ForwardList list2 = list;
	list2.print();

	ForwardList list3;
	list3 = list;
	list3.print();
#endif
    ForwardList list = { 3, 5, 8, 13, 21 };
//    for (Iterator it = list.getHead(); it!=nullptr; ++it)
//        cout << *it << "\t";
//    cout << endl;
    list.print();


    list.reverse();
    list.print();
    //ForwardList list2 = { 5, 8, 1 };
    //list2.print();

    //list2.sort();
    //list2.print();

    ForwardList list3 = { 5, 5, 1, 3, 8, 9, 9 };
    list3.print();
    list3.unique();
    list3.print();

    for (int i:list3)
    {
        cout << i << "\t";
    }
    cout << endl;

}
