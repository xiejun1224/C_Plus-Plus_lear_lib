#pragma once
#include <iostream>
#include<assert.h>
#include<cstring>
namespace xiejun

{

    class string

    {

        friend std::ostream& operator<<(std::ostream& _cout, const xiejun::string& s);

        friend std::istream& operator>>(std::istream& _cin, xiejun::string& s);

    public:

        typedef char* iterator;

    public:

        string(const char* str = "")
        {
			size_t len = strlen(str);
            _str = new char[len + 1];
            strcpy(_str, str);
			_size = len;
            _capacity = len;
        }

        string(const string& s);

            string& operator=(const string& s);

            ~string()
            {
                if (_str)
                {
                    delete[] _str;
                    _str = nullptr;
				}
            }



            //////////////////////////////////////////////////////////////

            // iterator

            iterator begin();

            iterator end();



            /////////////////////////////////////////////////////////////

            // modify

            void push_back(char c);

        string& operator+=(char c);

        void append(const char* str);

        string& operator+=(const char* str);

        void clear();

        void swap(string& s);

        const char* c_str()const
        {
			return _str;
        }



        /////////////////////////////////////////////////////////////

        // capacity

        size_t size()const
        {
			return _size;
        }

        size_t capacity()const
        {
			return _capacity;
        }

            bool empty()const;

            void resize(size_t n, char c = '\0');

        void reserve(size_t n);



        /////////////////////////////////////////////////////////////

        // access

        char& operator[](size_t index);

        const char& operator[](size_t index)const;



        /////////////////////////////////////////////////////////////

        //relational operators

        bool operator<(const string& s)const;

        bool operator<=(const string& s)const;

        bool operator>(const string& s)const;

        bool operator>=(const string& s)const;

        bool operator==(const string& s)const;

        bool operator!=(const string& s)const;



        // 返回c在string中第一次出现的位置

        size_t find(char c, size_t pos = 0) const;

        // 返回子串s在string中第一次出现的位置

        size_t find(const char* s, size_t pos = 0) const;

        // 在pos位置上插入字符c/字符串str，并返回该字符的位置

        string& insert(size_t pos, char c);

        string& insert(size_t pos, const char* str);



        // 删除pos位置上的元素，并返回该元素的下一个位置

        string& erase(size_t pos, size_t len);

    private:

        char* _str;

        size_t _capacity;

        size_t _size;
		static const size_t npos = -1;
    };

}
