//BinaryTree
#include<iostream>
using namespace std;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueeTree;
	}*Root;
public:
	Element* getRoot() const
	{
		return this->Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			insert(*it);
	}
	Tree(const Tree& other) : Tree()
	{
		*this = other;
	}
	~Tree()
	{
		clearAll(Root);
		cout << "TDestructor:\t" << this << endl;
	}


	void insert(int Data)
	{
		insert(Data, Root);
	}
	int minValue() const
	{
		return minValue(Root);
	}
	int maxValue() const
	{
		return maxValue(Root);
	}
	int count() const
	{
		return count(Root);
	}
	int sum() const
	{
		return sum(Root);
	}
	double avg() const
	{
		return (double)sum(Root) / count(Root);
	}
 	void print()const
	{
		print(Root);
		cout << endl;
	}

	void erase(int Data)
	{
		erase(Data, Root);
	}

private:


	Element* erase(int Data, Element* Root)
	{
		if (Root == nullptr) return Root;
		if (Data < Root->Data) Root->pLeft = erase(Data, Root->pLeft);
		else if (Data > Root->Data) Root->pRight = erase(Data, Root->pRight);
		else
		{
			//             нет потомков (детей)
			if (Root->pLeft == nullptr && Root->pRight == nullptr) return nullptr;
			else if (Root->pLeft == nullptr)
			{
				Element* temp = Root->pRight;
				delete Root;
				return temp;
			}
			else if (Root->pRight == nullptr)
			{
				Element* temp = Root->pLeft;
				delete Root;
				return temp;
			}

			Element* temp = minValueNode(Root->pRight); 
			Root->Data = temp->Data;
			Root->pRight = erase(temp->Data, Root->pRight);
		}
		return Root;
	}

	Element* minValueNode(Element* Root)
	{
		Element* Temp = Root;
		while (Temp && Temp->pLeft != nullptr) Temp = Temp->pLeft;

		return Temp;
	}

	void clearAll(Element* Root)
	{
		if (Root)
		{
			clearAll(Root->pLeft);
			clearAll(Root->pRight);
			delete Root;
		}
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else 
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root) const
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}

	int minValue(Element* Root) const
	{
		return !Root ? 0 : !Root->pLeft ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root) const
	{
		//if (Root->pRight == nullptr) return Root->Data;
		//minValue(Root->pRight);
		//return Root == nullptr ? 0 : Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return !Root ? 0 : !Root->pRight ? Root->Data : maxValue(Root->pRight);
	}
	int count(Element* Root) const
	{
		//if (Root == nullptr) return 0;
		//else return count(Root->pLeft) + count(Root->pRight) + 1;
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root) const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
};

class UniqueeTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data) 
	{
		insert(Data, Root);
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0;i < n;i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	//cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Среднее арифметическое: " << tree.avg() << endl;
	//UniqueeTree uniq_tree;
	//for (int i = 0;i < n;i++)
	//{
	//	uniq_tree.insert(rand() % 100);
	//}
	//uniq_tree.print();
	////cout << endl;
	//cout << "Минимальное значение в дереве: " << uniq_tree.minValue() << endl;
	//cout << "Максимальное значение в дереве: " << uniq_tree.maxValue() << endl;
	//cout << "Количество элементов в дереве: " << uniq_tree.count() << endl;
	//cout << "Сумма элементов дерева: " << uniq_tree.sum() << endl;
	//cout << "Среднее арифметическое: " << uniq_tree.avg() << endl;

	int i;
	cout << "Введите удаляемое значение: "; cin >> i;
	tree.erase(i);
	tree.print();

}