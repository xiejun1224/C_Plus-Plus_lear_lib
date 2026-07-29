#pragma once
#include<iostream>
#include<deque>
namespace xiejun {
	template<class T , class container = std::deque<T>>
	class queue {
	public:
		void push(const T& val)
		{
			con.push_back(val);
		}

		void pop()
		{
			con.pop_front();
		}
		T& front()
		{
			return con.front();
		}
		T& back()
		{
			return con.back();
		}

		const T& front()const
		{
			return con.front();
		}
		const T& back()const
		{
			return con.back();
		}

		bool empty()const
		{
			return con.empty();
		}

		size_t size()const
		{
			return con.size();
		}
	private:
		container con;

	};

}