#include <iostream>
#include <vector>
#include "BinarySearchTree.h"  // 假设 BinarySearchTree 类定义在这个头文件中


void testInsertAndPrint(BinarySearchTree<int> &bst, const std::vector<int> &values) {
    for (int value : values) {
        bst.insert(value);
    }
    std::cout << "插入元素 ";
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "后的树：" << std::endl;
    bst.printTree();
}

void testRemove(BinarySearchTree<int> &bst, int value) {
    std::cout << "删除节点值为 " << value  << " 后的树：" << std::endl;;
    bst.remove(value);
    bst.printTree();
}
void testBinarySearchTree() {
    BinarySearchTree<int> bst;

    std::cout << "--------------------------------------" << std::endl;
    std::cout<<"Module 1: "<<std::endl;
    // 测试删除空树
    bst.remove(10);
    std::cout << "对空树删除 10：" << std::endl;
    bst.printTree();  // 输出应为“Empty tree”

    bst.insert(15);
    std::cout << "插入 15 后的树：" << std::endl;
    bst.printTree();  

    // 测试删除不存在于树中元素的值 12
    bst.remove(12);
    std::cout << "删除 12 后的树：" << std::endl;
    bst.printTree();

    // 测试删除仅含有一个节点的树
    testRemove(bst, 15);
    
    std::cout << "--------------------------------------" << std::endl;
    std::cout<<"Module 2: "<<std::endl;

    // 测试删除根节点，根节点有一个子节点
    testInsertAndPrint(bst, {40, 30});  // 插入 40, 30
    testRemove(bst, 40);  // 删除 40

    // 测试删除根节点，根节点有两个子节点
    testInsertAndPrint(bst, {25, 35});  // 插入 25, 35
    testRemove(bst, 30);  // 删除 30

    // 测试删除叶子节点（非根节点）
    testRemove(bst, 25);  // 删除 25

    // 测试删除有一个子节点的非根节点
    testInsertAndPrint(bst, {60, 50});  // 插入 60, 50
    testRemove(bst,60);  // 删除 60

    std::cout << "--------------------------------------" << std::endl;
    std::cout<<"Module 3: "<<std::endl;

    // 测试删除有两个子节点的非根节点（右子树的最小节点没有子节点）
    testInsertAndPrint(bst, {45, 65, 80, 52});  // 插入 50, 80
    testRemove(bst, 50);  // 删除 50

    // 测试删除有两个子节点的非根节点（右子树的最小节点有一个子节点）
    testInsertAndPrint(bst, {60, 62});  // 插入 70, 90, 85
    testRemove(bst, 52);  // 删除 80

    // 测试删除有两个子节点的非根节点（右子树的最小节点就是右子节点）
    testInsertAndPrint(bst, {90, 100});  // 插入 95，形成右子节点
    testRemove(bst, 65);  // 删除 90

}

int main() {
    testBinarySearchTree();
    return 0;
}