#pragma once
#include<iostream>
#include<vector>
#include<cassert>
#include<utility>
using namespace std;

template<class K,class V>
struct Hash_Node
{
    Hash_Node(const pair<K,V>& kv)
    :_kv(kv),_next(nullptr)
    {}
    pair<K,V> _kv;
    Hash_Node* _next;
};

template<class K>
struct Hash
{
    size_t operator()(const K& key)const
    {
        return size_t(key);
    }
};

template<>
struct Hash<string>
{
    size_t operator()(const string& str)const
    {
        size_t Hash_Val=0;
        for(const auto& e: str)
        {
            Hash_Val=Hash_Val*131+e;
        }

        return Hash_Val;
    }

};

template<class K,class V,class hash=Hash<K>>
class Hash_Bucket
{
public:
    using Node=Hash_Node<K,V>;
    Hash_Bucket()
    :_m(16),_table(size_t(1)<<_m),_n(0)
    {}

    ~Hash_Bucket()
    {
        for(auto& e: _table)
        {
            Node* cur=e;
            while(cur)
            {
                Node* next=cur->_next;
                delete cur;
                cur=next;
            }
            e = nullptr;
        }
    }

    //打散
    size_t Disturb(const size_t& key)const
    {
        size_t hashi=key^key>>16;
        if(sizeof(size_t)>=8)
            hashi^=hashi>>32;
        return hashi;
    }
    //映射
    size_t Hash_Pos(const size_t& key)const
    {
        size_t hashi=Disturb(key);
        return hashi&(_table.size()-1);
    }


     bool Insert(const pair<K,V> kv)
     {
        if(Find(kv.first))
        {
            return false;
        }
        if(_n==_table.size())
        {
            ++_m;
            vector<Node*> newtable(size_t(1)<<_m);
            for(auto& e: _table)
            {
                if(e!=nullptr)
                {
					Node* cur=e;
					while(cur)
					{
						Node*next=cur->_next;
						 size_t hashi=Disturb(_hash(cur->_kv.first));
                   		 hashi&=newtable.size()-1;

                   		 cur->_next=newtable[hashi];
						 newtable[hashi]=cur;
						 cur=next;
					}
                }
				e=nullptr;

            }
            swap(_table,newtable);
        }
        Node* newnode=new Node(kv);
        
        size_t hashi=Hash_Pos(_hash(kv.first));
        newnode->_next=_table[hashi];
        _table[hashi]=newnode;
        ++_n;
        return true;
     }

     Node* Find(const K& key)
     {
        size_t hashi=Hash_Pos(_hash(key));
        Node*cur=_table[hashi];
        while(cur)
        {
            if(cur->_kv.first==key)
                return cur;
            cur=cur->_next;
        }
        return nullptr;
     }

      Node* Find(const K& key)const
     {
        size_t hashi=Hash_Pos(_hash(key));
        Node*cur=_table[hashi];
        while(cur)
        {
            if(cur->_kv.first==key)
                return cur;
            cur=cur->_next;
        }
        return nullptr;
     }

    bool Erase(const K& key)
    {
        if(Find(key)==nullptr)
            return false;
        Node*prev=nullptr;
        size_t hashi=Hash_Pos(_hash(key));
        Node*cur=_table[hashi];
        while(cur)
        {
            Node*next=cur->_next;
            if(cur->_kv.first==key)
            {
                if(prev==nullptr)
                {
                    _table[hashi]=next;
                }
                else
                {
                    prev->_next=next;
                }
                delete cur;
                return true;
            }
            prev=cur;
            cur=next;
        }
        return false;
    }
private:
    size_t _m;
    vector<Node*> _table;
    size_t _n;
    hash _hash;
};
