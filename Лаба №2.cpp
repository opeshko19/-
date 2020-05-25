#include <iostream>

template<typename type>
class List {               //создаем общий класс для списка
private:
	template<typename type>
	class N {                    //создаем класс
	public:
		type data;
		N* next;	//указатель для следующей точки
		N* prev;	//указатель для предыдующей точки

		Node(type data, N* next = nullptr, N* prev = nullptr) //обнуляем указатели
		{
			this->data = data;
			this->next = next;
			this->prev = prev;
		}
	};

	size_t size;	// размер списка
	N<type>* h;		//указатель начала списка
	N<type>* t;		//указатель конца списка

public:
	List();
	~List();

	void Add(type data);
	void AddH(type data);
	type& operator[](const int index);
	size_t GetSize();
	void Insert(type data, int index);
	type Peek();
	void Delete(int index);
	void Clear();
};

template<typename type>
List<type>::List()
{
	size = 0;
	h = nullptr;
	t = nullptr;
}


template<typename type>
void List<type>::Add(type data)
{
	if (h == nullptr)
	{
		h = t = new N<type>(data);
	}
	else
	{
		N<type>* current = new N<type>(data, nullptr, t);
		t->next = current;
		t = current;
	}

	size++;
}

template<typename type>
void List<type>::AddH(type data)
{
	if (h == nullptr)
	{
		h = t = new N<type>(data);;
	}
	else
	{
		N<type>* current = new N<type>(data, h);
		h = current;
	}

	size++;
}

template<typename type>
type& List<type>::operator[](const int index)
{
	N<type>* current;
	int iterator;

	if (index <= size / 2)
	{
		current = h;
		iterator = 0;
		while (true)
		{
			if (iterator == index)
			{
				return current->data;
			}
			else
			{
				current = current->next;
				iterator++;
			}
		}
	}
	else
	{
		current = t;
		iterator = size - 1;
		while (true)
		{
			if (iterator == index)
			{
				return current->data;
			}
			else
			{
				current = current->prev;
				iterator--;
			}
		}
	}
}

template<typename type>
size_t List<type>::GetSize()
{
	return size;
}

template<typename type>
void List<type>::Insert(type data, int index)
{
	if (index == 0)
	{
		AddHead(data);
	}
	else if (index == size)
	{
		Add(data);
	}
	else
	{
		N<type>* previous;
		N<type>* current;

		if (index <= size / 2)
		{
			previous = h;

			for (int i = 0; i < index - 1; i++)
			{
				previous = previous->next;
			}

			current = new N<type>(data, previous->next, previous);
			previous->next->prev = current;
			previous->next = current;
		}
		else
		{
			previous = t;

			for (int i = size - 1; i > index; i--)
			{
				previous = previous->prev;
			}

			current = new N<type>(data, previous, previous->prev);
			previous->prev->next = current;
			previous->prev = current;
		}
	}

	size++;
}

template<typename type>
type List<type>::Peek()
{
	return t->data;
}

template<typename type>
void List<type>::Delete(int index)
{
	if (index == 0)
	{
		N<type>* temp = h;
		h = h->next;
		delete temp;
	}
	else if (index == size - 1)
	{
		N<type>* temp = t;
		t = t->prev;
		delete temp;
	}
	else
	{
		N<type>* previous;
		N<type>* toDelete;

		if (index <= size / 2)
		{
			previous = h;

			for (int i = 0; i < index - 1; i++)
			{
				previous = previous->next;
			}

			toDelete = previous->next;
			previous->next = toDelete->next;
			toDelete->next->prev = previous;
		}
		else
		{
			previous = t;

			for (int i = size - 1; i > index + 1; i--)
			{
				previous = previous->prev;
			}

			toDelete = previous->prev;
			previous->prev = toDelete->prev;
			toDelete->prev->next = previous;
		}

		delete toDelete;
	}
	size--;
}

template<typename type>
void List<type>::Clear()
{
	while (size > 0)
	{
		N<type>* temp = h;
		h = h->next;
		delete temp;
		size--;
	}
}

int main()
{
	List<int> list;

	for (int i = 0; i < 10; i++) //заполним список
		list.Add(i * 10);

	list.Insert(43, 6);//вставим на 6 позицию число 43
	
	list.Delete(10);//удаляем из списка 10 позицию

	for (int i = 0; i < list.GetSize(); i++)
		std::cout << list[i] << std::endl;

	for (int i = 0; i < 5; i++)
		list.Add(i * 2);

	for (int i = 0; i < list.GetSize(); i++)
		std::cout << list[i] << std::endl;
	
	list.Clear(); //очистим список

	return 0;
}