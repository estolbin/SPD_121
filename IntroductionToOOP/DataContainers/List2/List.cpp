#include"List.h"

template<typename T> List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstBaseIterator::~ConstBaseIterator()
{
#ifdef DEBUG
	cout << "BItDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other) const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other) const
{
	return this->Temp != other.Temp;
}
template<typename T> const T& List<T>::ConstBaseIterator::operator*() const
{
	return Temp->Data;
}

template<typename T> List<T>::ConstIterator::ConstIterator(List::Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "CItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "CItDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

template<typename T> typename List<T>::ConstIterator List<T>::cbegin() const
{
	return Head;
}
template<typename T> typename List<T>::ConstIterator List<T>::cend() const
{
	return nullptr;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::crbegin() const
{
	return Tail;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::crend() const
{
	return nullptr;
}
template<typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T> List<T>::List(const List& other) :List()
{
	*this = other;
	cout << "Copy constuctor:\t" << this << endl;
}
template<typename T> List<T>::~List()
{
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}
//			Operators
template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other) return *this;
	while (Head) pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
	cout << "Copy assignment:\t" << this << endl;
	return *this;
}
//			Adding elements
template<typename T> void List<T>::push_front(T Data)
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
template<typename T> void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr) return push_front(Data);
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T> void List<T>::insert(int Index, T Data)
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
template<typename T> void List<T>::pop_front()
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
template<typename T> void List<T>::pop_back()
{
	if (Head == Tail) return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T> void List<T>::erase(int Index)
{
	if (Index == 0) return pop_front();
	if (Index == size - 1) return pop_back();
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
template<typename T> void List<T>::print() const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Amout elements in list: " << tab << size << endl;
}
template<typename T> void List<T>::reverse_print() const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Amout elements in list: " << tab << size << endl;
}
//friend class Iterator;

template<typename T> void print(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}