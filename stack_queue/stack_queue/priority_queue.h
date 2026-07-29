#pragma once
#include<iostream>
#include<vector>

#include<functional>

//模拟实现priority_queue类，并完成测试

namespace bit

{

    template<class T>
    struct less
    {
        bool operator()(const T& a, const T& b)const
        {
            return a < b;
        }
    };
    template<class T>
    struct greater
    {
        bool operator()(const T& a, const T& b)const
        {
            return a > b;
        }
    };
    template <class T, class Container = std::vector<T>, class Compare = less<T> >

    class priority_queue

    {

    public:
       void adjustUp(size_t child)
        {
            size_t parent = (child - 1) / 2;
            while (child != 0)
            {
                if (comp(c[parent], c[child]))
                {
                    std::swap(c[child], c[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                    break;
            }
        }
       void adjustDown(size_t parent, size_t n)
       {
           size_t child = parent * 2 + 1;
           while (child < n) {
               if (child + 1 < n && comp(c[child], c[child + 1]))
                   child += 1;
               if (comp(c[parent], c[child]))
               {
                   std::swap(c[parent], c[child]);
                   parent = child;
                   child = parent * 2 + 1;
               }
               else
                   break;
           }

       }
        priority_queue()
            :c()
        { }
        

        template <class InputIterator>

        priority_queue(InputIterator first, InputIterator last)
        {
            InputIterator it = first;
            while (it != last)
            {
                c.push_back(*it);
                ++it;
            }
            for (int i = (c.size() - 1 - 1) / 2; i >= 0; i--) {
                adjustDown(i, c.size());
            }
        }

        bool empty() const
        {
            return c.empty();
        }

        size_t size() const
        {
            return c.size();
        }

        const T& top() const
        {
            return c.front();
        }

        T& top() 
        {
            return c.front();
        }

        void push(const T& x)
        {
            c.push_back(x);
            adjustUp(c.size()-1);
        }

        void pop()
        {
            std::swap(c[0], c.back());
            c.pop_back();
            adjustDown(0, c.size());
        }

    private:

        Container c;

        Compare comp;

    };

}