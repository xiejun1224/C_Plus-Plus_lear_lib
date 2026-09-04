#pragma once
#include<iostream>
#include<vector>
#include<cassert>
#include<utility>
enum Status
{
    EXIST,
    EMPTY,
    DELETE
};

template<class K,class V>
struct HashData
{
    HashData()
    :_status(EMPTY)
    {}
    std::pair<K,V> _kv;
    Status _status;
};

template<class K,class V>
class HashTable
{
public:
    HashTable()
    :_table(11),_n(0)
    {}
    bool Insert(const std::pair<K,V> kv)
    {
        if(Find(kv.first))
        {
            return false;
        }
        if(_n*10/_table.size()>=7)
        {
            HashTable<K,V> newtable;
            newtable._table.resize(2*_table.size());
            for(const auto&e: _table)
            {
                if(e._status==EXIST)
                newtable.Insert(e._kv);
            }
            _n=newtable._n;
            std::swap(_table,newtable._table);

        }
        size_t hashi=kv.first%_table.size();
        while(_table[hashi]._status==EXIST)
        {
            hashi=(hashi+1)%_table.size();
        }
        _table[hashi]._kv=kv;
        _table[hashi]._status=EXIST;
        ++_n;
        return true;
    }

    HashData<K,V>* Find(const K& key)
    {
        size_t start=key%_table.size();
        size_t hashi=start;
        while(_table[hashi]._status!=EMPTY)
        {
            if(_table[hashi]._status==EXIST&&_table[hashi]._kv.first==key)
            {
                return &_table[hashi];
            }
            hashi=(hashi+1)%_table.size();
            if(hashi==start)
            break;
        }
        return nullptr;
    }
    const HashData<K,V>* Find(const K& key)const
        {
            size_t start=key%_table.size();
            size_t hashi=start;
            while(_table[hashi]._status!=EMPTY)
            {
                if(_table[hashi]._status==EXIST&&_table[hashi]._kv.first==key)
                {
                    return &_table[hashi];
                }
                hashi=(hashi+1)%_table.size();
                if(hashi==start)
                break;
            }
            return nullptr;
    }


    bool Erase(const K& key)
    {
        HashData<K,V>* d=Find(key);
        if(d)
        {
            d->_status=DELETE;
            --_n;
            return true;
        }
        return false;
    }
private:
    //映射数组
        std::vector<HashData<K,V>> _table;
    //数组中的元素
        size_t _n;
};
