
#include "List.h"
#include <iostream>
template<typename Object>
void print_list(List<Object> _l)
{
    for(auto &it : _l)std::cout << it << " ";
    std::cout << std::endl;
}

int main()
{
    // 1. 测试构造函数、拷贝构造、移动构造、赋值操作符、移动赋值操作符
    List<int> list1 = {1, 2, 3, 4, 5};  // 初始化列表构造
    std::cout << "初始化列表构造list1: "; print_list<int>(list1);
    List<int> list2(list1);             // 拷贝构造
    std::cout << "拷贝构造list2: "; print_list<int>(list2);

    List<int> list3(std::move(list2)); 
    std::cout << "移动构造list3: "; print_list<int>(list3);

    List<int> list4;                    // 默认构造
    std::cout << "默认构造list4: "; print_list<int>(list4);
    std::cout << "利用list4验证一下empty(): " << list4.empty()<<std::endl;
    
    list3 = list4 = list1;                      // 拷贝赋值
    std::cout << "采用连等，将list1拷贝赋值到list4，并将list4拷贝赋值到list3"<<std::endl<<"list4: "; print_list<int>(list4); \
    std::cout <<"list3: ";print_list<int>(list3);
    std::cout << "再利用list4验证一下empty(): " << list4.empty()<<std::endl;

    List<int> list5 = {10, 11, 12};     
    list5 = std::move(list4);           // 移动赋值
    std::cout << "将list4移动赋值到list5: "; print_list<int>(list5);

    std::cout << "------------------------------"<<std::endl;

    // 2. 测试size, empty, clear, push_back, push_front, pop_back, pop_front
    std::cout << "测试size()函数: " << list1.size() << std::endl;
    list1.push_back(6);                 // 尾插
    std::cout << "在list1末尾插入元素6: "; print_list<int>(list1);

    list1.push_front(0);                // 头插
    std::cout << "再在list1开头插入元素0: "; print_list<int>(list1);
    std::cout << "再测试size()函数: " << list1.size() << std::endl;
    
    list1.pop_back();                   // 尾删
    std::cout << "删除list1末尾的元素: "; print_list<int>(list1);
    list1.pop_front();                  // 头删
    std::cout << "删除list1开头的元素: "; print_list<int>(list1);
    // std::cout << "Size after pop_back and pop_front: " << list1.size() << std::endl;

    list1.clear();                      // 清空列表
    std::cout << "调用clear函数清空list1的元素: "; print_list<int>(list1);
    std::cout << "此时的size: "<< list1.size() << std::endl;
    list1.clear();
    std::cout << "再次调用clear函数清空list1的元素，不会报错: "; print_list<int>(list1);
    std::cout << "------------------------------"<<std::endl;
   
    // 3. 测试insert和erase
    List<int> list6 = {1, 2, 3, 4};
    std::cout << "现在对于list6: "; print_list<int>(list6);
    auto itr = list6.begin();
    ++itr;                              // 移动到第二个元素
    list6.insert(itr, 100);             // 插入右值元素
    // std::cout << "After insert: ";
    std::cout << "在list6的第二个元素2之前插入右值元素100之后: "; print_list<int>(list6);
    int temp1 = 200;
    list6.insert(itr, temp1);
    std::cout << "在list6的第三个元素2之前插入左值元素200之后: "; print_list<int>(list6);

    list6.insert(list6.insert(itr, 300), 400);
    std::cout << "在list6的第四个元素2之前插入右值元素300，并利用其返回值（插入的元素）再向前插入400: "; print_list<int>(list6);


    itr = list6.begin();
    ++itr;                              // 再次移动到插入位置
    list6.erase(itr);                   // 删除该元素
    
    std::cout << "删除list6的第二个元素之后: "; print_list<int>(list6);
    itr = ++list6.begin();
    list6.erase(list6.erase(itr));                   // 删除该元素
    std::cout << "再次删除list6的第二个元素，并利用其返回值再删除之前的第三个元素: "; print_list<int>(list6);
    
    auto itr2 = list6.erase(++list6.begin(), list6.end());
    std::cout << "删除list6的第二个和最后一个元素（包括最后一个）之间的所有元素: "; print_list<int>(list6);
    list6.erase(list6.begin(), itr2);
    std::cout << "利用前一步的删除的返回值，再删除list6的第一个元素和最后一个元素之间的所有元素: "; print_list<int>(list6);
    
    std::cout << "------------------------------"<<std::endl;

    // 4. 测试front, back, begin, end, ++, --, *操作符
    List<int> list7 = {10, 20, 30, 40};
    
    std::cout << "现在对于list7: "; print_list<int>(list7);
    std::cout << "测试front函数得到list7的第一个元素: " << list7.front() << std::endl;
    std::cout << "测试back函数得到list7的最后一个元素: " << list7.back() << std::endl;

    auto it = list7.begin();
    List<int>::const_iterator i = list7.begin();
    i++; // 向前移动一位
    std::cout << "初始化迭代器，并通过*得到list7的第一个元素: " << *it << std::endl;
    
    // 前置++操作符
    std::cout << "利用前置*(++it)操作符得到list7的第二个元素: " << *(++it)  << std::endl;
    std::cout << "利用前置*(++i)操作符得到list7的第三个元素: " << *(++i)  << std::endl;
    
    // 前置--操作符
    std::cout << "利用前置*(--it)操作符得到list7的第一个元素: " << *(--it) << std::endl;
    std::cout << "利用前置*(--i)操作符得到list7的第二个元素: " << *(--i)  << std::endl;
    
    // 后置++操作符
    std::cout << "利用后置*(it++)操作符得到list7的第一个元素: " << *(it++)  << std::endl;
    std::cout << "利用后置*(i++)操作符得到list7的第二个元素: " << *(i++)  << std::endl;

    // 后置--操作符
    std::cout << "利用后置*(it--)操作符得到list7的第二个元素: " << *(it--) << std::endl;
    std::cout << "利用后置*(i--)操作符得到list7的第三个元素: " << *(i--)  << std::endl;

    std::cout << "------------------------------"<<std::endl;

    // 5. 测试const_iterator以及iterator的操作
    const List<int> const_list = {50, 60, 70};
    std::cout << "对于const_list: "; print_list<int>(const_list);
    auto const_it = const_list.begin();
    ++const_it;
    std::cout << "测试const_list的begin()并利用const_it得到第二个元素: " << *const_it << std::endl;
    auto const_itr = const_list.end();
    --const_itr;
    std::cout << "测试const_list的begin()并利用const_itr得到倒数第一个元素: " << *const_itr << std::endl;
    
    List<int>::const_iterator i1, i2;
    std::cout << "测试默认初始化是否为nullptr并相等: "  << (i1==i2)<< std::endl;
    std::cout << "测试i1是否和it不相等: "  << (i1!=it)<< std::endl;
    i1 = it;
    std::cout << "测试通过赋值之后，i1是否和it不相等: "  << (i1!=it)<< std::endl;
    std::cout << "------------------------------"<<std::endl;

    // 6. 测试移动语义 push_back, push_front
    List<std::string> stringList;
    std::string temp = "Hello,", temp2 = "Maplefaith";
    stringList.push_back("is");      // 右值push_back
    stringList.push_back(temp2);         // 左值push_back
    stringList.push_front("My name");     // 右值push_front
    stringList.push_front(temp);        // 左值push_front

    std::cout << "经过左右值push_back和push_front, 得到stringList: ";
    print_list<std::string>(stringList);

    return 0;
}