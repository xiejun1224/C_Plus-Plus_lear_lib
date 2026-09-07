#include"unordered_set.h"
#include"unordered_map.h"
#include<iostream>

int main()
{
    std::cout << "========== 测试1: my_unordered_set ==========" << std::endl;
    my_unordered_set<int> s;
    std::cout << "insert 5: " << s.insert(5) << " (应1)" << std::endl;
    std::cout << "insert 1: " << s.insert(1) << std::endl;
    std::cout << "insert 9: " << s.insert(9) << std::endl;
    std::cout << "重复insert 5: " << s.insert(5) << " (应0)" << std::endl;

    std::cout << "遍历: ";
    for(auto it=s.begin(); it!=s.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "erase 1: " << s.erase(1) << " (应1)" << std::endl;
    std::cout << "erase 1 again: " << s.erase(1) << " (应0)" << std::endl;
    std::cout << "再遍历: ";
    for(auto it=s.begin(); it!=s.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "\n========== 测试2: string set ==========" << std::endl;
    my_unordered_set<std::string> ss;
    ss.insert("hello"); ss.insert("world"); ss.insert("abc"); ss.insert("bca");
    std::cout << "遍历: ";
    for(auto it=ss.begin(); it!=ss.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "\n========== 测试3: my_unordered_map ==========" << std::endl;
    my_unordered_map<int,std::string> m;
    m.insert({1,"one"});
    m.insert({2,"two"});
    m.insert({65537,"collision"});
    std::cout << "遍历: ";
    for(auto it=m.begin(); it!=m.end(); ++it)
        std::cout << "[" << it->first << ":" << it->second << "] ";
    std::cout << std::endl;

    std::cout << "\n========== 测试4: operator[] ==========" << std::endl;
    m[3] = "three";
    std::cout << "m[3] = " << m[3] << std::endl;
    m[1] = "uno";
    std::cout << "m[1] = " << m[1] << " (应uno)" << std::endl;

    std::cout << "\n========== 测试5: string map ==========" << std::endl;
    my_unordered_map<std::string,int> sm;
    sm["apple"] = 5;
    sm["banana"] = 3;
    sm["cherry"] = 8;
    std::cout << "sm[apple] = " << sm["apple"] << std::endl;
    std::cout << "遍历: ";
    for(auto it=sm.begin(); it!=sm.end(); ++it)
        std::cout << "[" << it->first << ":" << it->second << "] ";
    std::cout << std::endl;

    std::cout << "\n========== 测试6: 拷贝构造 ==========" << std::endl;
    my_unordered_map<int,std::string> m2(m);
    m2[100] = "hundred";
    int m2count=0; for(auto it=m2.begin(); it!=m2.end(); ++it) m2count++;
    int mcount=0; for(auto it=m.begin(); it!=m.end(); ++it) mcount++;
    std::cout << "m2元素数: " << m2count << " (应4), m元素数: " << mcount << " (应3, 深拷贝!)" << std::endl;

    std::cout << "\n========== 测试7: 大容量 ==========" << std::endl;
    my_unordered_map<int,int> big;
    for(int i=0;i<10000;i++) big.insert({i,i*2});
    int count=0;
    for(auto it=big.begin(); it!=big.end(); ++it) count++;
    std::cout << "插10000个遍历到: " << count << " (应10000)" << std::endl;
    std::cout << "big[9999] = " << big[9999] << " (应19998)" << std::endl;

    std::cout << "\n🎉 全部完成!" << std::endl;
    return 0;
}
