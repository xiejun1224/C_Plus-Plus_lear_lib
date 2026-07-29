#pragma once
#include <iostream>
#include <deque>
namespace xiejun {
	template<class T ,class container = std::deque<T>>
	class stack
	{
	public:
		void push(const T& val)
		{
			con.push_back(val);
		}

		void pop()
		{
			con.pop_back();
		}
		const T& top()const
		{
			return con.back();
		}
		T& top()
		{
			return con.back();
		}
		size_t size()const
		{
			return con.size();
		}
		bool empty()const
		{
			return con.empty();
		}
	private:
		container con;
	};

}
