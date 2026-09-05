#pragma once
#include<iostream>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;

enum Status
{
    EXIST,
    DELETE,
    EMPTY
};

template<class K,class V>
struct HashData
{
    pair<K,V> _kv;
    Status _status=EMPTY;
};

template<class K>
struct Hash
{
    size_t operator()(const K& key)const
    {
        return (size_t)key;
    }
};
 template<>
 struct Hash<string>
 {
    size_t operator()(const string& st)const
    {
        size_t hashi=0;
        for(const auto& e : st)
        {
            hashi=hashi*131+e;
            //BKDR算法防止碰撞
        }

        return hashi;
    }
 };

template<class K,class V ,class hash=Hash<K>>
class HashTable
{
public:
    HashTable()
    :_m(16),_table(size_t(1) << _m),_n(0)
    {}

    size_t Hash_Pos(const size_t& key) const
    {
        //const函数不能调用非const函数所以扰动函数要加const
        size_t hashi=Disturb(key);
        return hashi&(_table.size()-1);
    }

    size_t Disturb(const size_t& key)const
    {
        size_t hashi=key^(key>>16);
        if(sizeof(size_t)>=8)
            hashi^=hashi>>32;
        return hashi;
    }
    bool Insert(const pair<K,V>& kv)
    {
        if(Find(kv.first))
        {
            return false;
        }
        //储存的数据大于0.7时扩容
        //if(_n*10/_table.size()>=7)
        //改成乘法避免除法的开销
        if(_n*10>=7*_table.size())
        {   
        //内存消耗过大 
            // HashTable newtable;
            // newtable._table.resize(2*_table.size());
            // newtable._m+=1+_m;
            // for(const auto& e: _table)
            // {
            //     if(e._status==EXIST)
            //     newtable.Insert(e._kv);
            // }
            // _n=newtable._n;
            // _m=newtable._m;
            // swap(_table,newtable._table);
            size_t newM=_m+1;
            size_t newsize=size_t(1)<<newM;
            vector<HashData<K,V>> newtable(newsize);
            for(const auto& e: _table)
            {
                if(e._status==EXIST)
                {
                    size_t HashVal=hash()(e._kv.first);
                    size_t hashi=Disturb(HashVal)&(newsize-1);
                    while(newtable[hashi]._status==EXIST)
                    {
                        hashi=(hashi+1)&(newsize-1);
                    }
                    newtable[hashi]._kv=e._kv;
                    newtable[hashi]._status=EXIST;
                }
            }
            swap(newtable,_table);
            _m=newM;
        }
        //x % y == x&(y-1)，例如x%16==保留0-15，按位于15也等于保留0-15
    hash _hash;
    size_t hashi=Hash_Pos(_hash(kv.first));
    while(_table[hashi]._status==EXIST)
    {
        hashi=(hashi+1)&(_table.size()-1);
    }
    _table[hashi]._kv=kv;
    _table[hashi]._status=EXIST;
    ++_n;
    return true;
    }    

    HashData<K,V>* Find(const K& key)
    {
        hash _hash;
        size_t hashi=Hash_Pos(_hash(key));
        size_t start=hashi;
        while(_table[hashi]._status!=EMPTY)
        {
            if(_table[hashi]._status==EXIST&&_table[hashi]._kv.first==key)
            {
                return &_table[hashi];
            }
            hashi=(hashi+1)&(_table.size()-1);
            if(hashi==start)
                break;
        }

        return nullptr;
    }
     const HashData<K,V>* Find(const K& key) const
    {
        hash _hash;
        size_t hashi=Hash_Pos(_hash(key));
        size_t start=hashi;
        while(_table[hashi]._status!=EMPTY)
        {
            if(_table[hashi]._status==EXIST&&_table[hashi]._kv.first==key)
            {
                return &_table[hashi];
            }
            hashi=(hashi+1)&(_table.size()-1);
            if(hashi==start)
                break;
        }

        return nullptr;
    }
    bool Erase(const K& key)
    {
        HashData<K,V>* d=Find(key);
        if(d==nullptr)
        return false;
        d->_status=DELETE;
        --_n;
        return true;
    }
private:
    size_t _m;
    vector<HashData<K,V>> _table;
    size_t _n;
};
