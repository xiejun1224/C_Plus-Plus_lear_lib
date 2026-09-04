#include"Hash.h"
#include<iostream>

int main()
{
    HashTable<int, int> ht;

    // 测试1: 插入（新接口：直接传pair）
    std::cout << "========== 测试1: 插入 ==========" << std::endl;
    std::cout << "插{1,100}: " << ht.Insert({1, 100}) << " (应1)" << std::endl;
    std::cout << "插{2,200}: " << ht.Insert({2, 200}) << " (应1)" << std::endl;
    std::cout << "插{12,1200}: " << ht.Insert({12, 1200}) << " (应1, 线性探测)" << std::endl;
    std::cout << "重复插{1,999}: " << ht.Insert({1, 999}) << " (应0, 拒绝重复)" << std::endl;

    // 测试2: 查找（新接口：直接传key）
    std::cout << "\n========== 测试2: 查找 ==========" << std::endl;
    HashData<int,int>* p = ht.Find(12);
    std::cout << "Find(12): " << (p ? "找到 value=" : "没找到") << (p ? p->_kv.second : -1) << std::endl;
    std::cout << "Find(99): " << (ht.Find(99) ? "找到了?" : "没找到(正确)") << std::endl;

    // 测试3: 删除（新接口）
    std::cout << "\n========== 测试3: 删除 ==========" << std::endl;
    std::cout << "Erase(1): " << ht.Erase(1) << " (应1)" << std::endl;
    std::cout << "再Find(1): " << (ht.Find(1) ? "还在" : "没了(正确)") << std::endl;
    std::cout << "再Erase(1): " << ht.Erase(1) << " (应0)" << std::endl;

    // 测试4: 扩容（50个元素触发）
    std::cout << "\n========== 测试4: 扩容 ==========" << std::endl;
    HashTable<int,int> big;
    bool allok = true;
    for(int i=0;i<50;i++)
    {
        if(!big.Insert({i,i*10})) allok=false;
    }
    std::cout << "插50个: " << (allok?"全部成功":"有失败") << std::endl;
    int found=0;
    for(int i=0;i<50;i++)
        if(big.Find(i)) found++;
    std::cout << "扩容后能找到: " << found << "/50 (应50)" << std::endl;

    // 测试5: 删25个后还能找到剩下的
    std::cout << "\n========== 测试5: 删一半 ==========" << std::endl;
    for(int i=0;i<25;i++) big.Erase(i);
    int remain=0;
    for(int i=0;i<50;i++)
        if(big.Find(i)) remain++;
    std::cout << "删25后剩余: " << remain << "/50 (应25)" << std::endl;

    // 测试6: 删除后再插入（测 --_n 是否生效！）
    std::cout << "\n========== 测试6: 删后插入 ==========" << std::endl;
    std::cout << "插{100,1}: " << big.Insert({100, 1}) << " (应1, 空间应充足)" << std::endl;
    std::cout << "Find(100): " << (big.Find(100) ? "找到(正确)" : "没找到?") << std::endl;

    std::cout << "\n🎉 全部测试完成!" << std::endl;
    return 0;
}
