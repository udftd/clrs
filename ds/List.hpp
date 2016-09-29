#ifndef _FY_LIST_HPP_
#define _FY_LIST_HPP_

#include <utility>

template <typename T>
class List;
template <typename  T>
class const_iterator;
template <typename T>
class iterator;

template <typename T>
class Node
{
	public:
		Node(const T& d = T{}, Node* p = nullptr, Node* n = nullptr)
			: data{ d }, prev{ p }, next{ n }
		{}
		Node(T&& d, Node* p = nullptr, Node* n = nullptr)
			: data{ std::move(d) }, prev{ p }, next{ n }
		{}

	private:
		T		data;	
		Node*	prev;
		Node*	next;
		friend class List<T>;
		friend class const_iterator<T>;
		friend class iterator<T>;
};

template <typename T>
class const_iterator
{
	public:
		const_iterator()
			: current { nullptr }
		{}

		const T& operator * ()const
		{
			return retrieve();
		}

		const_iterator & operator ++ ()
		{
			current = current->next;
			return *this;
		}
		const_iterator & operator -- (int)
		{
			const_iterator old = *this;
			--(*this);
			return *old;
		}

		bool operator == (const const_iterator& rhs)const
		{
			return current == rhs.current;
		}
		bool operator != (const const_iterator& rhs)const
		{
			return !(*this == rhs);
		}


	protected:
		Node<T>* current;
		T& retrieve()const
		{
		   	return current->data; 
		}
		const_iterator(Node<T>* p) 
			: current{ p } 
		{}
		friend class List<T>;
};

template<typename T>
class iterator: public const_iterator<T> 
{
	public:
		iterator(){}
		T& operator * ()
		{
			return const_iterator<T>::retrieve();
		}
		const T& operator * ()const
		{
			return const_iterator<T>::operator*();
		}
		iterator operator ++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}
		iterator operator ++ ()
		{
			this->current = this->current->next;
			return *this;
		}
		iterator& operator -- ()
		{
			this->current = this->current->prev;
			return *this;
		}
		iterator operator -- (int)
		{
			iterator old = *this;
			--(*this);
			return old;
		}

	protected:
		iterator(Node<T>* p) : const_iterator<T>{ p } {}
		friend class List<T>;

};

template <typename T>
class List
{
	public:
		List() { init(); }
		~List() 
		{
			clear();
			delete head;
			delete tail;
		}
		List(const List& rhs)
		{
			init();
			for (auto& x : rhs)
				push_back(x);
		}
		List& operator = (const List& rhs)
		{
			List copy = rhs;
			std::swap(*this, copy);
			return *this;
		}
		List(List&& rhs)
			: theSize{ rhs.theSize },
			head{ rhs.head },
			tail{ rhs.tail }
		{
			rhs.theSize = 0;
			rhs.head = nullptr;
			rhs.tail = nullptr;
		}
		List& operator = (List&& rhs)
		{
			std::swap(theSize, rhs.theSize);
			std::swap(head, rhs.head);
			std::swap(tail, rhs.tail);
			return *this;
		}

	public:
		iterator<T> begin()
		{
			return iterator<T>(head->next);
		}
		const_iterator<T> begin()const
		{
			return const_iterator<T>(head->next);
		}
		iterator<T> end()
		{
			return iterator<T>(tail);
		}
		const_iterator<T> end()const
		{
			return const_iterator<T>(tail);
		}

		T& front()
		{
			return *begin();
		}
		const T& front()const
		{
			return *begin();
		}
		T& back()
		{
			return *--end();
		}
		const T& back()const
		{
			return *--end();
		}


	public:
		void clear()
		{
			while(!empty())
				pop_front();
		}

		int size()const
		{
			return theSize;
		}
		bool empty()const
		{
			return theSize == 0;
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		void push_back(T&& x)
		{
			insert(begin(), std::move(x));
		}
		void push_front(T&& x)
		{
			insert(end(), std::move(x));
		}
		void pop_back()
		{ 
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
		

		// insert before itr
		iterator<T> insert(iterator<T> itr, const T& x)
		{
			Node<T>* p = itr.current;
			++theSize;
			return iterator<T>(p->prev = p->prev->next = new Node<T>{x, p->prev, p});
		}
		iterator<T> insert(iterator<T> itr, const T&& x)
		{
			Node<T>* p = itr.current;
			++theSize;
			return iterator<T>(p->prev = p->prev->next = new Node<T>{ std::move(x), p->prev, p});
		}

		iterator<T> erase(iterator<T> itr)
		{
			Node<T> *p = itr.current;
			iterator<T> it(p->next);
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			--theSize;
			return it;
		}
		iterator<T> erase(iterator<T> from, iterator<T> to)
		{
			for(iterator<T> itr = from; itr != to;)
				itr = erase(itr);
			return to;
		}

	private:
		int				theSize;
		Node<T>*		head;
		Node<T>*		tail;

		void init()
		{
			theSize = 0;
			head = new Node<T>;
			tail = new Node<T>;
			head->next = tail;
			tail->prev = head;
		}

};

#endif




















