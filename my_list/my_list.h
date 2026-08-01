#pragma once
#include<iostream>
#include<cassert>
using namespace std;
namespace xiejun
{
	template<class T>
	struct list_node
	{
		list_node(const T& val = T())
			:data(val),prev(nullptr),next(nullptr){}

		T data;
		list_node<T>* prev;
		list_node<T>* next;
	};

	template<class T,class Ref,class Ptr>
	struct list_Iterator
	{
		typedef list_node<T> Node;
		typedef Node* PNode;
		typedef list_Iterator <T, Ref, Ptr>Self;
		PNode node;
		list_Iterator(const PNode& cur)
			:node(cur)
		{
		}
		Ref operator*()
		{
			return node->data;
		}
		Ptr operator->()
		{
			return &node->data;
		}
		Self& operator++()
		{
			node = node->next;
			return *this;
		}

		Self operator++(int)
		{
			PNode tmp = node;
			node = node->next;
			return list_Iterator(tmp);
		}

		Self& operator--()
		{
				node = node->prev;
				return *this;
		}

		bool operator==(const Self&cur)const
		{
			return node == cur.node;
		}
		bool operator!=(const Self&cur)const
		{
			return node != cur.node;
		}
	};
	
	template<class T>
	class list
	{
	public:
		typedef list_node<T> node;
		typedef list_Iterator<T, T&, T*> iterator;
		typedef list_Iterator<T, const T&, const T*> const_iterator;
		typedef node* pnode;
		void Swap(list<T>& it)
		{
			swap(_head, it._head);
			swap(_size, it._size);
		}
		list<T>& operator=( list<T> ls)
		{
			Swap(ls);
			return *this;
		}
		void clear()
		{
			auto it = begin();
			while (it != end())
			{
				it=erase(it);
			}
		}
		void clear2()
		{
			while (_size)
			{
				pop_back();
			}
		}
		void Empty_init()
		{
			_head = new node();
			_size = 0;
			_head->next = _head;
			_head->prev = _head;
		}
		list()
			:_size(0),_head(new node())
		{
			_head->next = _head;
			_head->prev = _head;
		}
		list(const list<T>& ls)
		{
			Empty_init();
			for (auto& it : ls)
			{
				push_back(it);
			}
		}
		
		~list()
		{
			while (_size)
			{
				pop_back();
			}
			delete _head;
		}

		 //链表的尾插
		void push_back(const T& val)
		{
			pnode newnode = new node(val);
			_head->prev->next = newnode;
			newnode->next = _head;
			newnode->prev = _head->prev;
			_head->prev = newnode;
			_size++;
		}
		//链表的尾删
		void pop_back()
		{
			pnode cur = _head->prev;
			assert(cur != _head);
			cur->prev->next = _head;
			_head->prev = cur->prev;
			delete cur;
			_size--;
		}
		//链表的头插
		void push_front(const T& val)
		{
			pnode newnode = new node(val);
			newnode->next = _head->next;
			newnode->prev = _head;
			_head->next->prev = newnode;
			_head->next = newnode;
			_size++;
		}
		//链表的头删
		void pop_front()
		{
			assert(_size != 0);
			pnode cur = _head->next;
			_head->next = cur->next;
			cur->next->prev = _head;
			delete cur;
			_size--;
		}
		size_t size() const 
		{
			return _size;
		}

		bool Empty() const
		{
			return _size == 0;
		}

		iterator begin()
		{
			return iterator(_head->next);
		}
		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin()const
		{
			return const_iterator(_head->next);
		}
		const_iterator end()const
		{
			return const_iterator(_head);
		}
		iterator insert(iterator pos,const T& val)
		{
			assert(pos.node);
			pnode newnode = new node(val);
			newnode->next = pos.node;
			newnode->prev = pos.node->prev;
			pos.node->prev->next = newnode;
			pos.node->prev = newnode;
			++_size;
			return iterator(newnode);
		}
		iterator erase(iterator pos)
		{
			pnode cur = pos.node;
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			iterator next(pos.node->next);
			delete cur;
			--_size;
			return next;
		}
	private:
			size_t _size;
			pnode _head;
	};

}