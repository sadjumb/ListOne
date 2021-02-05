template<class T> class MyList;
template <class T>
class Node
{
private:
	Node* _pNext;
	T _data;
	Node(const T data = T(), Node* pNext = nullptr)
	{
		_data = data;
		_pNext = pNext;
	}
	friend class MyList<T>;
};

template<class T>
class MyList
{
public:
	MyList()
	{
		_size = 0;
		_head = nullptr;
	}
	MyList(const MyList& l1)
	{
		*this = l1;
	}

	~MyList()
	{
		while (_head != nullptr)
		{
			pop_front();
		}
	}

	bool empty() const
	{
		return (_head == nullptr);
	}
	int size() const
	{
		return _size;
	}

	void push_back(T data)
	{
		if (_head == nullptr)
		{
			_head = new Node<T>(data);
		}
		else
		{
			Node<T>* tmp = _head;
			while (tmp->_pNext != nullptr)
			{
				tmp = tmp->_pNext;
			}
			tmp->_pNext = new Node<T>(data);
		}
		_size++;
	}
	void pop_back()
	{
		Node<T>* tmp = _head;
		int counter = 0;
		if (_head != nullptr)
		{
			while (counter < _size - 2)
			{
				tmp = tmp->_pNext;
				counter++;
			}
			delete tmp->_pNext;
			tmp->_pNext = nullptr;
			--_size;
		}
	}

	void push_front(T data)
	{
		if (_head == nullptr)
		{
			_head = new Node<T>(data);
		}
		else
		{
			Node<T>* tmp = _head;
			_head = new Node<T>(data);
			_head->_pNext = tmp;
		}
		_size++;
	}
	void pop_front()
	{
		if (_head != nullptr)
		{
			Node<T>* tmp = _head->_pNext;
			delete _head;
			_head = nullptr;
			_head = tmp;
			_size--;
		}
	}

	void remove_at(int index)
	{
		if (index < 0 || index >= _size)
		{
			return;
		}
		else
		{
			if (index == 0)
			{
				this->pop_front();
			}
			else
			{
				Node<T>* tmp = _head;
				for (int i = 0; i < index - 1; ++i)
				{
					tmp = tmp->_pNext;
				}
				Node<T>* toDel = tmp->_pNext;
				tmp->_pNext = toDel->_pNext;
				delete toDel;
				toDel = nullptr;
				--_size;
			}
		}
	}
	void clear()
	{
		this->~MyList();
	}

	void insert(int index, T value)
	{
		if (index < 0 || index > _size)
		{
			return;
		}
		else
		{
			if (index == 0)
			{
				this->push_front(value);
			}
			else if (index == (_size - 1))
			{
				this->push_back(value);
			}
			else
			{
				Node<T>* tmp = _head;
				for (int i = 0; i < index - 1; ++i)
				{
					tmp = tmp->_pNext;
				}
				Node<T>* prev = tmp;
				tmp = tmp->_pNext;
				prev->_pNext = new Node<T>(value);
				prev = prev->_pNext;
				prev->_pNext = tmp;
			}
		}
		_size++;
	}

	T& operator[](const int index) const
	{
		Node<T>* tmp = _head;
		int counter = 0;
		while (tmp != nullptr)
		{
			if (counter == index)
			{
				return tmp->_data;
			}
			tmp = tmp->_pNext;
			counter++;
		}
		//баг
	}

	MyList& operator =(const MyList& l)
	{
		Node<T>* tmp = l._head;

		if (this != &l)
		{
			this->~MyList();
			while (tmp)
			{
				this->push_back(tmp->_data);
				tmp = tmp->_pNext;
			}
		}
		return *this;
	}
private:
	int _size{};
	Node <T>* _head;

};