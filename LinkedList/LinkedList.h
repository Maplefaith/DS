#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val){data = _val;}

        friend class SingleLinkedList<T>;
    };
    Node* head = nullptr;
    int size = 0;
    Node* currentPos = nullptr;
    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);
public:
    /// todo1: 返回当前位置的值
    T getCurrentVal() const;
    /// todo2: 设置当前位置的值
    void setCurrentVal(const T &_val);
    /// todo3: 如果链表为空，返回 true；否则返回 false
    bool isEmpty() const;
    /// todo4: 在 currentPos 后面插入一个元素，数据为 _val
    void insert(T _val); 
    /// todo5: 删除 currentPos 后面的元素
    void remove(); 
    void remove(bool Flag);
    int getSize() const;
    void emptyList();
    bool find (const T &_val);
    SingleLinkedList(){};
    ~SingleLinkedList(); 
    SingleLinkedList(std::initializer_list<T> _l);
    void printList() const;
    SingleLinkedList(const SingleLinkedList<T> &_l);
    SingleLinkedList<T>& operator=(const SingleLinkedList<T> &_l);


    /// 如果找到，返回 ture, currentPos 停留在第一个 _val 的位置。
    /// 否则返回 false, currentPos 不动。
    // bool find(const T &_val) const;  
};

template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    if(currentPos == nullptr){
        std::cout<< "Empty current position! Can't get value!" <<std::endl;
        exit(1);
    } 
    return currentPos->data;
}

template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if(currentPos == nullptr){
        std::cout<< "Empty current position! Can't set value!" <<std::endl;
        exit(1);
    }
    currentPos->data = _val;
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    if(head == nullptr && size == 0) return true;
    return false;
}

template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    Node* newNode = new Node(_val);
    if(size == 0 && head==nullptr){
        head = newNode;
        currentPos = head;
    }
    else{
        newNode->next = currentPos->next;
        currentPos->next = newNode;
        currentPos = newNode;
    }
    ++size;
}

template <typename T>
void SingleLinkedList<T>::remove()
{
    if(size==1){
        delete head;
        --size;
        head = nullptr;
        currentPos = nullptr;
    }
    else if(size>1 && currentPos!=nullptr){
        Node * p = currentPos->next;
        if(p!=nullptr){
            --size;
            if(p->next!=nullptr)
            {   
                currentPos->next = p->next;
                delete p;
            }
            else{
                delete p;
                currentPos->next = nullptr;
            }
        }
    }
}

// remove the element at currentPos and then move the currentPos forward/backward according to variable "Flag"
// Flag: true - move forward; but will move backward if currentPos is the head node
//      false - move backward; but will move forward if currentPos is the last node
template <typename T>
void SingleLinkedList<T>::remove(bool Flag)
{
    if(size==1){
        delete head;
        --size;
        head = nullptr;
        currentPos = nullptr;
    }
    else if(size>1 && currentPos!=nullptr){
        Node * p = currentPos->next;
        Node * temp = head;
        Node * prev = nullptr;
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

template<typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            return true;
        }
        p = p->next;    
    }
    return false;
}

template<typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node* newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* t = p;
        p = p->next; 
        delete t;
    }
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node* p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;    
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

template<typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}

template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node* newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}