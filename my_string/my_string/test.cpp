#define _CRT_SECURE_NO_WARNINGS 1
#include "My_String.h"
using namespace std;
void test1()
{
    xiejun::string s1("hello world");
    cout << s1.c_str() << endl;      // hello world
    cout << s1.size() << endl;        // 11
    cout << s1.capacity() << endl;    // 11

    xiejun::string s2;                // ¿Õ×Ö·û´®
    cout << "'" << s2.c_str() << "'" << endl;
    cout << s2.size() << endl;
}
void test2()
{
    xiejun::string s1("hello");
    xiejun::string s2("world");
    s2 = s1;                    // ²âÊÔ¸³Öµ
    cout << s2.c_str() << endl; // hello

    s2 = s2;                    // ²âÊÔ×Ô¸³Öµ
    cout << s2.c_str() << endl; // hello£¨²»ÄÜ±À£©
}

void test3()
{
    xiejun::string str1("hello world");
    cout << str1.c_str() << endl;
    cout <<"²âÊÔ£º" << str1[3] << endl;
    xiejun::string::iterator it = str1.begin();
    while (it != str1.end())
    {
        cout << *it;
        ++it;
    }

    for (auto c : str1)
    {
        cout << c << endl;
    }
}

void test_push_back() {
    xiejun::string s1("hello");
    cout << s1.size() << endl;      //5
    s1.push_back('!');
    cout << s1.c_str() << endl;    // hello!
    cout << s1.size() << endl;     // 6

    // ²âÀ©ÈÝ£¨¿Õ×Ö·û´® push_back£©
    xiejun::string s2;
    s2.push_back('A');
    cout << s2.c_str() << endl;    // A
    cout << s2.size() << endl;     // 1
}

void test4()
{
    xiejun::string str1;
    str1 += 'x';
    cout << str1.c_str()<< endl;
    cout << str1.size() << endl;
}

void test5()
{
    xiejun::string str1("hellow");
    xiejun::string str2("xiejun");
    str1.swap(str2);
    cout << str1.c_str() << endl;
    cout << str2.c_str() << endl;
    cout << str1.size() << endl;
    str1.resize(10, 'x');
    for (auto i : str1)
    {
        cout << i;
    }
    cout << endl;
    cout << str1.size() << endl;
    str1.resize(3, 'x');
    for (auto i : str1)
    {
        cout << i;
    }
    cout << endl;
    cout << str1.size() << endl;
}

void test6()
{
    xiejun::string str("hello world");
    const char* ch = " hello Linux";
    str.append(ch);
    cout << str.c_str() << endl;
    xiejun::string str1("hello");
    cout << str1.c_str() << endl;
    str1 += " world";
    cout << str1.c_str() << endl;
}

void test_find() {
    xiejun::string s("hello world, hello Linux!");

    // ÕÒ×Ö·û
    size_t pos1 = s.find('w');
    cout << "find 'w': " << pos1 << endl;        // 6

    size_t pos2 = s.find('x');
    cout << "find 'x': " << pos2 << endl;        // 4294967295 (npos)

    // ÕÒ×Ó´®
    size_t pos3 = s.find("world");
    cout << "find \"world\": " << pos3 << endl;   // 6

    size_t pos4 = s.find("hello", 2);             // ´ÓÎ»ÖÃ2¿ªÊ¼ÕÒ
    cout << "find \"hello\" from pos=2: " << pos4 << endl;  // 13

    size_t pos5 = s.find("zzz");
    cout << "find \"zzz\": " << pos5 << endl;      // npos
}
void test_erase() {
    xiejun::string s1("hello world");
    s1.erase(5, 1);
    cout << s1.c_str() << endl;   // hello

    xiejun::string s2("hello world");
    s2.erase(6, 100);             // len ³¬³ö·¶Î§
    cout << s2.c_str() << endl;   // hello 
}
void test_insert() {
    xiejun::string s1("world");
    s1.insert(0, "hello ");
    cout << s1.c_str() << endl;   // hello world

    xiejun::string s2("helorld");
    s2.insert(3, "lo wwddwww");
    cout << s2.c_str() << endl;   // hello world
}
int main() 
{
    //test1();
    //test2();
    //test3();
    //test_push_back();
    //test4();
    //test5();
    //test6();
    //test_find();
    //test_erase();
    test_insert();
    return 0;
}