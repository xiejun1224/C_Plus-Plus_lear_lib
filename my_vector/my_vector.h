#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>
namespace xiejun

{

    template<class T>

    class vector

    {

    public:

        // Vector的迭代器是一个原生指针

        typedef T* iterator;

        typedef const T* const_iterator;
        bool empty() const
        {
            return _finish == _start;
        }
        iterator begin()
        {
            return _start;
         }

        iterator end()
        {
            return _finish;
        }

        const_iterator begin()const
        {
            return _start;
        }

        const_iterator end() const
        {
            return _finish;
        }
    
            // construct and destroy

        vector()
            :_start(nullptr),_finish(nullptr),_endOfStorage(nullptr)
        {}

        vector(int n, const T& value = T())
        :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
        {
            reserve(n);
            while (_finish != _endOfStorage)
            {
                push_back(value);
            }
        }
        

            template<class InputIterator>

            vector(InputIterator first, InputIterator last)
              :_start(nullptr), _finish(nullptr), _endOfStorage(nullptr)
            {
                while (first != last)
                {
                    push_back(*first++);
                }
            }

        vector(const vector<T>& v)
            :_start(nullptr),_finish(nullptr),_endOfStorage(nullptr)
        {
            reserve(v.size());
            for (size_t i = 0; i < v.size(); i++)
            {
                push_back(v._start[i]);
            }
          
        }

        vector<T>& operator= (vector<T> v)
        {
            swap(v);
            return *this;
         }

            ~vector()
        {
            delete[] _start;
            _start = _finish = _endOfStorage = nullptr;
        }

            // capacity

        size_t size() const
        {
            return _finish - _start;
         }

        size_t capacity() const
        {
            return _endOfStorage - _start;

           }

        void reserve(size_t n)
        {
            if (n > capacity())
            {
                size_t old_size = size();
                T* tmp = new T[n];
                //memcpy(tmp, _start, sizeof(T) * size());string不行
                for (size_t i = 0; i < old_size; i++)
                {
                    tmp[i] = _start[i];
                }

                delete[] _start;
                _start = tmp;
                _finish = tmp + old_size;
                _endOfStorage = tmp + n;
                
            }
        }

        void resize(size_t n, const T& value = T())
        {
            reserve(n);
            if (n < size())
            {
                while (n != size())
                {
                    --_finish;
                }
            }
            else
            {
                while (size() != n)
                {
                    *_finish = value;
                    _finish++;
                }
            }
         
         }



            ///////////////access///////////////////////////////

                T& operator[](size_t pos)
            {
                assert(pos < size());
                return _start[pos];
            }

            const T& operator[](size_t pos) const
            {
                assert(pos < size());
                return _start[pos];
            }



            ///////////////modify/////////////////////////////

            void push_back(const T& x)
            {
              
                if (size() == capacity())
                {
                    reserve(capacity() ==0 ? 4 : 2 * capacity());
                }
                *_finish = x;
                ++_finish;
            }

            void pop_back()
            {
                assert(!empty());
                --_finish;
              
            }

            void swap(vector<T>& v)
            {
                std::swap(_start, v._start);
                std::swap(_finish, v._finish);
                std::swap(_endOfStorage, v._endOfStorage);
            }

            iterator insert(iterator pos, const T& x)
            {
                assert(pos >= _start && pos <= _finish);
                size_t n = pos - _start;
                if (size() == capacity())
                {
                    reserve(capacity() == 0 ? 4 : 2 * capacity());
                    pos = _start + n;
                }
                /*for (int i = size() - 1; i >= pos - _start; i--)
                {
                    _start[i + 1] = _start[i];
                }*/
                iterator end = _finish;
                while (end > pos)
                {
                    *end = *(end - 1);
                    --end;
                }
                _start[n] = x;
                ++_finish;
                return pos;
            }

            iterator erase(iterator pos)
            {
                iterator i = pos+1;
                while (i != _finish)
                {
                    *(i - 1) = *i;
                    i++;
                }
                --_finish;
                return pos;
            }

    private:

        iterator _start; // 指向数据块的开始

        iterator _finish; // 指向有效数据的尾

        iterator _endOfStorage; // 指向存储容量的尾

    };

}