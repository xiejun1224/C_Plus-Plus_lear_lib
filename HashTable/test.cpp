#include"Hash_push.h"
#include<iostream>

int main()
{
    std::cout << "========== 测试1: int key ==========" << std::endl;
    HashTable<int, int> ht;
    std::cout << "插{1,100}: " << ht.Insert({1, 100}) << " (应1)" << std::endl;
    std::cout << "插{65537,999}: " << ht.Insert({65537, 999}) << " (应1, 冲突探测)" << std::endl;
    std::cout << "重复插{1,0}: " << ht.Insert({1, 0}) << " (应0)" << std::endl;
    HashData<int,int>* p = ht.Find(65537);
    std::cout << "Find(65537): " << (p ? "找到 value=" : "没找到") << (p ? p->_kv.second : -1) << std::endl;

    std::cout << "\n========== 测试2: string key (BKDR) ==========" << std::endl;
    HashTable<string, int> st;
    std::cout << "插{\"hello\",1}: " << st.Insert({"hello", 1}) << " (应1)" << std::endl;
    std::cout << "插{\"world\",2}: " << st.Insert({"world", 2}) << " (应1)" << std::endl;
    std::cout << "插{\"abc\",3}: " << st.Insert({"abc", 3}) << " (应1)" << std::endl;
    std::cout << "插{\"bca\",4}: " << st.Insert({"bca", 4}) << " (应1, 字母相同顺序不同)" << std::endl;
    std::cout << "重复插{\"hello\",99}: " << st.Insert({"hello", 99}) << " (应0)" << std::endl;

    HashData<string,int>* sp = st.Find("hello");
    std::cout << "Find(\"hello\"): " << (sp ? "找到 value=" : "没找到") << (sp ? sp->_kv.second : -1) << std::endl;
    std::cout << "Find(\"bca\"): " << (st.Find("bca") ? "找到(正确)" : "没找到?") << std::endl;
    std::cout << "Find(\"nope\"): " << (st.Find("nope") ? "找到了?" : "没找到(正确)") << std::endl;

    std::cout << "\n========== 测试3: 删除 ==========" << std::endl;
    std::cout << "Erase(\"world\"): " << st.Erase("world") << " (应1)" << std::endl;
    std::cout << "再Find(\"world\"): " << (st.Find("world") ? "还在" : "没了(正确)") << std::endl;

    std::cout << "\n========== 测试4: int扩容(10000个) ==========" << std::endl;
    HashTable<int,int> big;
    bool allok=true;
    for(int i=0;i<10000;i++)
        if(!big.Insert({i,i})) allok=false;
    std::cout << "插10000个: " << (allok?"全部成功":"有失败") << std::endl;
    int found=0;
    for(int i=0;i<10000;i++)
        if(big.Find(i)) found++;
    std::cout << "能找到: " << found << "/10000 (应10000)" << std::endl;

    std::cout << "\n========== 测试5: string扩容(5000个) ==========" << std::endl;
    HashTable<string,int> sb;
    bool sok=true;
    for(int i=0;i<5000;i++)
    {
        std::string key = "key_" + std::to_string(i);
        if(!sb.Insert({key,i})) sok=false;
    }
    std::cout << "插5000个string: " << (sok?"全部成功":"有失败") << std::endl;
    int sfound=0;
    for(int i=0;i<5000;i++)
    {
        std::string key = "key_" + std::to_string(i);
        if(sb.Find(key)) sfound++;
    }
    std::cout << "能找到: " << sfound << "/5000 (应5000)" << std::endl;

    std::cout << "\n🎉 全部测试完成!" << std::endl;
    return 0;
}
