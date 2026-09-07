#pragma once
#include<iostream>
#include<vector>
#include<cassert>
#include<utility>
#include<string>
using namespace std;

//仿函数
template<class K>
struct Hash
{
    size_t operator()(const K& key)const
    {
        return size_t(key);
    }
};

//仿函数特化string
template<>
struct Hash<string>
{
    size_t operator()(const string& key)const
    {
        size_t hashval=0;
        for(auto& e:key)
        {
            hashval=hashval*131+e;
        }
        return hashval;
        
    }
};
//节点
template<class T>
struct Hash_Node
{
    Hash_Node(const T& data)
    :_data(data),_next(nullptr)
    {}
    T _data;
    Hash_Node<T>* _next;
};

//声明迭代器
template<class K, class T,class Hash,class KeyOfT ,class Ptr,class Ret>
class Hash_Iterator;

//哈希表
template<class K, class T,class Hash,class KeyOfT >
class Hash_table
{

    template<class K1, class T1,class Hash1,class KeyOfT1 ,class Ptr1,class Ret1>
    friend class Hash_Iterator;
public:
    using Node=Hash_Node<T>;
    using Iterator=Hash_Iterator<K,T,Hash,KeyOfT,T*,T&>;
    using Const_Iterator=Hash_Iterator<K,T,Hash,KeyOfT,const T*,const T&>;
    ~Hash_table()
    {
        for(auto& e : _table)
        {
            if(e)
            {
                Node* cur=e;
                while(cur)
                {
                    Node* next=cur->_next;
                    delete cur;
                    cur=next;
                }
            }
        }
    }
    Hash_table(const Hash_table& ht)
    :_m(ht._m),_n(0),_table(size_t(1)<<_m)
    {
        for(auto& e : ht._table)
        {
            if(e)
            {
                Node* cur=e;
                while(cur)
                {
                    Node* next=cur->_next;
                    insert(cur->_data);
                    cur=next;
                }
            }
        }
    }

    Hash_table& operator=(Hash_table ht)
    {
        swap(_table,ht._table);
        _m=ht._m;
        _n=ht._n;
        return *this;
    }
    Iterator begin()
    {
        for(auto& e:_table)
        {
            if(e)
            return Iterator(e,this);
        }
        return Iterator(nullptr,this);
    }
    Const_Iterator begin()const
    {
        for(auto& e:_table)
        {
            if(e)
            return Const_Iterator(e,this);
        }
        return Const_Iterator(nullptr,this);

    }

    Iterator end()
    {
        return Iterator(nullptr,this);
    }
    Const_Iterator end()const
    {
        return Const_Iterator(nullptr,this);
    }
    Hash_table()
    :_m(16),_n(0),_table(size_t(1)<<_m)
    {}
    //通过前面的位来打散后面的位
    size_t Disturb(const size_t& key)const
    {
        size_t hashi=key^(key>>16);
        if(sizeof(size_t)>=8)
        {
            hashi^=hashi>>32;
        }
        return hashi;
    }
//确定映射位置
    size_t Hash_Pos(const size_t& key)const
    {
        size_t hashi=Disturb(key);
        return hashi&(_table.size()-1);
    }
    pair<Iterator,bool> insert(const T& data)
    {
        K key=_kof(data);
        Node* cur=find(key);
        if(cur)
        {
            return {Iterator(cur,this),false};
        }
        //扩容
        if(_n==_table.size())
        {
            ++_m;
            vector<Node*> newtable(size_t(1)<<_m);
            for(size_t i=0;i<_table.size();i++)
            {
               Node* cur=_table[i];
               while(cur)
               {
                size_t newi=Hash_Pos(_hash(_kof(cur->_data)));
                Node* next=cur->_next;
                cur->_next=newtable[newi];
                newtable[newi]=cur;
                cur=next;
               }
            }
            swap(_table,newtable);   
        }
        Node*newnode=new Node(data);
        size_t pos=Hash_Pos(_hash(_kof(data)));
        newnode->_next=_table[pos];
        _table[pos]=newnode;
        ++_n;
        return {Iterator(newnode,this),true};
    }
//查找
    Node* find(const K& key)
    {
        size_t hashval=_hash(key);
        size_t hashi=Hash_Pos(hashval);
        Node*cur=_table[hashi];
        while(cur)
        {
            if(_kof(cur->_data)==key)
            return cur;
            cur=cur->_next;
        }

        return nullptr;
        
    }
     Node* find(const K& key)const
    {
        size_t hashval=_hash(key);
        size_t hashi=Hash_Pos(hashval);
         Node*cur=_table[hashi];
        while(cur)
        {
            if(_kof(cur->_data)==key)
            return cur;
            cur=cur->_next;
        }

        return nullptr;
        
    }

//删除 
    bool erase(const K& key)
    {
       size_t hashval=_hash(key);
       size_t hashi=Hash_Pos(hashval);
        if(_table[hashi])
        {
            if(_kof(_table[hashi]->_data)==key)
            {
                Node* del=_table[hashi];
                _table[hashi]=del->_next;
                delete del;
                --_n;
                return true;
            }
            else
            {
                Node*prev=_table[hashi];
                Node*cur=_table[hashi]->_next;
                while(cur)
                {
                    if(_kof(cur->_data)==key)
                    {
                        prev->_next=cur->_next;
                        delete cur;
                        --_n;
                        return true;
                    }
                    prev=cur;
                    cur=cur->_next;
                }
                return false;
            }
        }
        return false;

    }
    // Hash_table<K,T,Hash,KeyOfT>* get_table()
    // {
    //     return this;
    // }

private:
    size_t _m;
    size_t _n;
    vector<Node*> _table;
    Hash _hash;
    KeyOfT _kof;

};

template<class K, class T,class Hash,class KeyOfT ,class Ptr,class Ret>
class Hash_Iterator
{
public:
    using Node =Hash_Node<T>;
    using Self=Hash_Iterator<K,T,Hash,KeyOfT,Ptr,Ret>;

    Hash_Iterator(Node* node,const Hash_table<K,T,Hash,KeyOfT>* pnt)
    :_node(node),_pnt(pnt)
    {}

   Self& operator++()
    {
        Node* cur=_node;
        //当前链表还有下一个节点，直接返回下一个节点的迭代器
        if(cur->_next)
        {
          _node=_node->_next;
          return *this;
        }
        //下一个节点为空，寻找下一个不为空的桶
        size_t hashval=_pnt->_hash(_pnt->_kof(cur->_data));
        size_t hashi=_pnt->Hash_Pos(hashval)+1;
        while(hashi<_pnt->_table.size())
        {
           
               if(_pnt->_table[hashi])
                {
                    _node=_pnt->_table[hashi];
                    return *this;
                } 
                ++hashi;
        }
        _node=nullptr;
        return *this;
    }
    bool operator==(const Self& it)const
    {
        return _node==it._node&&_pnt==it._pnt;
    }

    bool operator!=(const Self& it)const
    {
        return _node!=it._node||_pnt!=it._pnt;
    }
    Ret operator*()
    {
        return _node->_data;
    }
    Ptr operator->()
    {
        return &_node->_data;
    }
private:
        Node* _node;
        const Hash_table<K,T,Hash,KeyOfT>* _pnt;

};

