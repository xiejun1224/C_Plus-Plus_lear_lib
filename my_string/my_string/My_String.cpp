#define _CRT_SECURE_NO_WARNINGS 1
#include "My_String.h"
namespace xiejun
{
	string::string(const string& s)
	{
		_str = new char[s._size + 1];
		strcpy(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
	}
	string& string::operator=(const string& s)
	{
		if (this == &s)
		{
			return *this;
		}
		delete[] _str;
		_str = new char[s._size + 1];
		strcpy(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}

	char& string::operator[](size_t index)
	{
		assert(index < _size);
		return _str[index];
	}
	const char& string::operator[](size_t index)const
	{
		assert(index < _size);
		return _str[index];
	}

	string::iterator string::begin()
	{
		return _str;
	}

	string::iterator string::end()
	{
		return _str + _size;
	}

	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* str = new char[n+1];
			strcpy(str, _str);
			delete[] _str;
			_str = str;
			_capacity = n;
		}
	}


	void string::push_back(char c)
	{
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		_str[_size] = c;
		++_size;
		_str[_size] = '\0';
	}


	string& string:: operator+=(char c)
	{
		push_back(c);
		return *this;
	}

	void string::clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}

	bool string::empty()const
	{
		return _size == 0;
	}

	void string::swap(string& s)
	{
		char* tmp = _str;
		_str = s._str;
		s._str = tmp;
		size_t stmp = _size;
		_size = s._size;
		s._size = stmp;
		size_t ctmp = _capacity;
		_capacity = s._capacity;
		s._capacity = ctmp;
	}

	void string::resize(size_t n, char c)
	{
		if (n > _size)
		{
			reserve(n);
			for (size_t i = _size; i < n; i++)
			{
				_str[i] = c;
			}
			_size = n;
		}
		else {
			_size = n;
		}
		_str[_size] = '\0';
	}

	void string::append(const char* str)
	{
		size_t n = _size + strlen(str);
		if (n > _capacity)
		{
			reserve(n > 2 * _capacity ? n : 2 * _capacity);
		}
		strcpy(_str + _size, str);
		_size = n;
	}


	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;
	}


	bool string::operator<(const string& s)const
	{
		return strcmp(_str, s._str) < 0;
	}

	bool string::operator<=(const string& s)const
	{
		return operator<(s) || operator==(s);
	}

	bool string::operator>(const string& s)const
	{
		return !operator<=(s);
	}

	bool string::operator>=(const string& s)const
	{
		return !operator<(s);
	}

	bool string::operator==(const string& s)const
	{
		return strcmp(_str, s._str) == 0;
	}

	bool string::operator!=(const string& s)const
	{
		return !operator==(s);
	}


	size_t string::find(char c, size_t pos ) const
	{
		for (size_t i = pos; i < size(); i++)
		{
			if (_str[i] == c)
				return i;
		}
		return npos;
	}


	size_t string::find(const char* s, size_t pos ) const
	{
		char*pn=strstr(_str+pos, s);
		if(pn)
		return pn - _str;
		return npos;
	}
	string& string::erase(size_t pos, size_t len)
	{
		assert(pos < _size);
		if (pos + len >= _size)
		{
			_size = pos;
		}
		else
		{
			size_t n = _size - (pos + len);
			size_t p = pos;
			size_t l = p+len;
			while (n--)
			{
				_str[p] = _str[l];
				p++;
				l++;
			}
			_size -= len;
		}
		_str[_size] = '\0';
		return *this;	
	}

	string& string::insert(size_t pos, char c)
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		size_t e = _size;
		while (e != pos)
		{
			_str[e] = _str[e-1];
			e--;
		}
		_str[pos] = c;
		++_size;
		_str[_size] = '\0';
		return *this;
	}


	string& string::insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}
		memmove(_str + pos + len, _str + pos,_size-pos+1);
		memcpy(_str + pos, str,len);
		_size += len;
		return *this;
	}

	std::ostream& operator<<(std::ostream& _cout, const xiejun::string& s)
	{
		_cout << s.c_str();
		return _cout;
	}
	std::istream& operator>>(std::istream& _cin, xiejun::string& s)
	{
		s.clear();
		const size_t n = 1024;
		char buff[n];
		char ch=_cin.get();
		 size_t i = 0;
		 while (ch != ' ' && ch != '\n')
		 {
			 buff[i++] = ch;
			 if (i == n - 1)
			 {
				 buff[i] = '\0';
				 s += buff;
				 i = 0;
			 }
			 ch = _cin.get();
		 }
		 if (i > 0)
		 {
			 buff[i] = '\0';
			 s += buff;
		 }

		return _cin;
	}

}