# 选做部分
实现了关于remove的合理的功能。
## 功能设计
通过设计一个输入量，来选择删除后currentPos的指向。
函数原型如下所示。
```c++
template <typename T>
void SingleLinkedList<T>::remove(bool Flag);
```
功能为：
- 如果是空链表，或者currentPos指向nullptr（当然在我们设计的功能里，用户并不能在一个有元素的链表里，尝试让currentPos指向nullptr），则不进行操作
- 如果仅有一个元素，则删除后成为空链表，表现为
```c++
size = 0;
head = nullptr;
currentPos = nullptr;
```
- 如果链表有两个及以上元素，在删除currentPos所指节点后，可以通过输入Flag选择currentPos指向的节点，即

$$
currentPos =  
\begin{cases}
prev & \text{（取前节点）} \quad \text{if} \quad \text{Flag} == \text{true} \\
next & \text{（取后节点）} \quad \text{if} \quad \text{Flag} == \text{false}
\end{cases}
$$

注意：若currentPos指向的节点为最后一个节点，则删除该节点后默认将currentPos指向删除后链表的最后一个节点（即删除之前的链表的倒数第二个节点）；同理，若currentPos指向的节点为第一个节点，则删除该节点后默认将currentPos指向删除后链表的第一个节点（即删除之前的链表的第二个节点）

## 程序代码
```c++
template <typename T>
void SingleLinkedList<T>::remove(bool Flag)
{
    if(size==1){ // 链表只有一个元素
        delete head;
        --size;
        head = nullptr;
        currentPos = nullptr;
    }
    else if(size>1 && currentPos!=nullptr){ // 链表有两个及以上元素 且currentPos有意义
        Node * p = currentPos->next; // 用于指向当前元素的下一个元素
        Node * temp = head; // 用于查找currentPos的位置
        Node * prev = nullptr; // 用于指向当前元素的上一个元素
        while(temp != currentPos){
            prev = temp;
            temp = temp->next;
        }
        --size;
        if(prev != nullptr){
            prev->next = currentPos->next;
        }
        else {
            head = currentPos->next;
        }
        delete currentPos;

        if((Flag && prev != nullptr) || p == nullptr){
            currentPos = prev;
        }
        if((!Flag && p!=nullptr) || prev == nullptr){
            currentPos = p;
        }        
    }
}
```
## 功能验证
在main.cpp的main函数中加入：
```c++
    SingleLinkedList<double> c1 = {1,2,3,4,5,6,7,8,9,10};
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    //1       2       3       4       5       6       7       8       9       10

    // 验证删除之后再向后移currentPos，当currentPos指向最后一个元素
    c1.remove(false);std::cout<<"After removal: "<<"backward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: backward
    // 1       2       3       4       5       6       7       8       9
    // cur: 9

    // 验证删除之后再向后移currentPos，当currentPos指向最后一个元素
    c1.remove(false);std::cout<<"After removal: "<<"backward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: backward
    // 1       2       3       4       5       6       7       8
    // cur: 8

    // 更新currentPos
    c1.find(4);
    std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 得到：
    // cur: 4

    // 验证删除之后再向后移currentPos
    c1.remove(false);std::cout<<"After removal: "<<"backward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: backward
    // 1       2       3       5       6       7       8
    // cur: 5

    // 验证删除之后再向后移currentPos
    c1.remove(false);std::cout<<"After removal: "<<"backward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: backward
    // 1       2       3       6       7       8
    // cur: 6
    
    // 验证删除之后再向前移currentPos
    c1.remove(true);std::cout<<"After removal: "<<"forward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: forward
    // 1       2       3       7       8
    // cur: 3

    // 验证删除之后再向前移currentPos
    c1.remove(true);std::cout<<"After removal: "<<"forward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: forward
    // 1       2       7       8
    // cur: 2

    // 验证删除之后再向前移currentPos
    c1.remove(true);std::cout<<"After removal: "<<"forward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: forward
    // 1       7       8
    // cur: 1
    
    // 验证删除之后再向前移currentPos，当currentPos指向第一个元素
    c1.remove(true);std::cout<<"After removal: "<<"forward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: forward
    // 7       8
    // cur: 7

    // 验证删除之后再向前移currentPos，当链表里只有一个元素
    c1.remove(true);std::cout<<"After removal: "<<"forward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: forward
    // 8
    // cur: 8

    // 验证删除空链表
    c1.remove(true);std::cout<<"After removal: "<<"forward"<<std::endl;
    c1.printList();std::cout<<"cur: "<<c1.getCurrentVal()<<std::endl;
    // 预计得到：
    // After removal: forward

    // cur: Empty current position! Can't get value!
    // 程序停止并退出
    return 0;
```

会有输出：
```c++
1       2       3       4       5       6       7       8       9       10
cur: 10
After removal: backward
1       2       3       4       5       6       7       8       9
cur: 9
After removal: backward
1       2       3       4       5       6       7       8
cur: 8
cur: 4
After removal: backward
1       2       3       5       6       7       8
cur: 5
After removal: backward
1       2       3       6       7       8
cur: 6
After removal: forward
1       2       3       7       8
cur: 3
After removal: forward
1       2       7       8
cur: 2
After removal: forward
1       7       8
cur: 1
After removal: forward
7       8
cur: 7
After removal: forward
8
cur: 8
After removal: forward

cur: Empty current position! Can't get value!
```
