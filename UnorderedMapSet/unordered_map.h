#include"Hash_table.h"
template<class K,class V,class hash=Hash<K>>
class my_unordered_map
{
public:
    struct MapOfK
    {
        const K& operator()(const pair<const K,V>& kv) const
        {
            return kv.first;
        }
    };
    using iterator= typename Hash_table<K,pair<const K,V>,hash,MapOfK>:: Iterator;
    using const_iterator= typename Hash_table<K,pair<const K,V>,hash,MapOfK>::Const_Iterator;
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

    pair<iterator,bool> insert(const pair<const K,V>& kv)
    {
        return _st.insert(kv);
    }

    bool erase(const K& key)
    {
        return _st.erase(key);
    }

    V& operator[](const K& key)
    {
        pair<iterator,bool> ht=_st.insert(pair<const K,V>(key,V()));
        return ht.first->second;

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
    Hash_table<K,pair<const K,V>,hash,MapOfK> _st;

};