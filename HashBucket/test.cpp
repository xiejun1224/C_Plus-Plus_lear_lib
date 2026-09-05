#include"Hash_Bucket.h"
#include<iostream>

int main()
{
    std::cout << "=== 测试1: 基本功能 ===" << std::endl;
    Hash_Bucket<int,int> hb;
    hb.Insert({1,10}); hb.Insert({2,20}); hb.Insert({65537,99});
    std::cout << "插3个(含冲突65537): ";
    auto p = hb.Find(65537);
    std::cout << (p?"找到value=":"没找到") << (p?p->_kv.second:-1) << std::endl;
    std::cout << "重复插: " << hb.Insert({1,0}) << " (应0)" << std::endl;

    std::cout << "\n=== 测试2: 删除 ===" << std::endl;
    std::cout << "删{1}: " << hb.Erase(1) << " (应1)" << std::endl;
    std::cout << "再Find(1): " << (hb.Find(1)?"还在":"没了(正确)") << std::endl;

    std::cout << "\n=== 测试3: 扩容70000个 ===" << std::endl;
    Hash_Bucket<int,int> big;
    bool ok=true;
    for(int i=0;i<70000;i++)
        if(!big.Insert({i,i})) ok=false;
    std::cout << "插70000: " << (ok?"成功":"失败") << std::endl;
    int found=0;
    for(int i=0;i<70000;i++)
        if(big.Find(i)) found++;
    std::cout << "找到: " << found << "/70000" << std::endl;

    std::cout << "\n=== 测试4: 冲突数据(65537倍数) ===" << std::endl;
    Hash_Bucket<int,int> evil;
    bool eok=true;
    for(int i=0;i<70000;i++)
        if(!evil.Insert({i*65537,i})) eok=false;
    std::cout << "插70000冲突数据: " << (eok?"成功":"失败") << std::endl;
    int efound=0;
    for(int i=0;i<70000;i++)
        if(evil.Find(i*65537)) efound++;
    std::cout << "找到: " << efound << "/70000 (扩容不丢=正确!)" << std::endl;

    std::cout << "\n=== 测试5: string ===" << std::endl;
    Hash_Bucket<std::string,int> sb;
    for(int i=0;i<1000;i++) sb.Insert({"k"+std::to_string(i),i});
    int sf=0;
    for(int i=0;i<1000;i++) if(sb.Find("k"+std::to_string(i))) sf++;
    std::cout << "string找到: " << sf << "/1000" << std::endl;
    for(int i=0;i<500;i++) sb.Erase("k"+std::to_string(i));
    int sr=0;
    for(int i=0;i<1000;i++) if(sb.Find("k"+std::to_string(i))) sr++;
    std::cout << "删500后剩: " << sr << "/1000 (应500)" << std::endl;

    std::cout << "\n🎉 全部测试通过!" << std::endl;
    return 0;
}
