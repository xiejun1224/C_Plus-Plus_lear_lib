#pragma once
#include"Hash_table.h"
template<class K,class hash=Hash<K>>
class my_unordered_set
{
    public:

     struct SetOfK
    {
        const K& operator()(const K& key)const
        {
            return key;
        } 
    };
    using iterator= typename Hash_table<K,K,hash,SetOfK>::Iterator;
    using const_iterator= typename Hash_table<K,K,hash,SetOfK>::Const_Iterator;

    iterator begin()
    {
        return _st.begin();
    }

    const_iterator begin()const
    {
        return _st.begin();
    }

    iterator end()
    {
        return _st.end();
    }

    const_iterator end()const
    {
        return _st.end();
    }

    bool insert(const K& key)
    {
        return _st.insert(key).second;
    }

    bool erase(const K& key)
    {
        return _st.erase(key);
    }

    iterator find(const K& key)
    {
       
        return iterator(_st.find(key),&_st);
    }

    const_iterator find(const K& key)const
    {
        return const_iterator(_st.find(key),&_st);
    }
    private:
        Hash_table<K,K,hash,SetOfK> _st;
};