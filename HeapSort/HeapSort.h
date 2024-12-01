#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

#include <vector>

template <typename Comparable>
void PercDown(std::vector<Comparable> &V, int i, int n){
    Comparable tmp = V[i];
    int child = 2*i+1; // from left Child
    while(child<n){
        if(child!=n-1 && V[child]<V[child+1])++child;
        if(tmp<V[child]) V[i] = V[child];
        else break; // the big parent need to wait to go up when we adjust its parent
        i = child;
        child = 2*i+1;
    }
    V[i] = tmp;
}

template <typename Comparable>
void HeapSort(std::vector<Comparable> &V){
    int len = V.size();
    // for(int j=len/2-1;j>=0;--j){
    //     PercDown(V, j, len);
    // }
    for(int j=len-1;j>0;--j){
        std::swap(V[0], V[j]);
        PercDown(V, 0, j);
    }
}

template <typename Comparable>
void PercUp(std::vector<Comparable>& V, int i) {
    Comparable tmp = V[i]; // 保存插入的值
    int parent = (i - 1) / 2; // 计算父节点的索引

    // 循环将当前值与其父节点比较，并根据需要上移
    while (i > 0 && tmp > V[parent]) { 
        V[i] = V[parent]; // 将父节点下移
        i = parent; // 更新当前节点为父节点
        parent = (i - 1) / 2; // 更新父节点索引
    }

    V[i] = tmp; // 最后将值放入正确位置
}

template <typename Comparable>
void HeapSort1(std::vector<Comparable> &V){
    int len = V.size();
    for(int j=1;j<len;++j){
        PercUp(V, j);
    }
    for(int j=len-1;j>0;--j){
        std::swap(V[0], V[j]);
        PercDown(V, 0, j);
    }
}
/*
template <typename Comparable>
void PercDown(std::vector<Comparable> &a, int i, int n){
    int child;Comparable tmp;
    for( tmp=std::move( a[i]);leftChild(i)<n; i= child ){
        child = leftchild( i );
        if( child !=n-1 && a[ child ]<a[ child+1])++child;
        if( tmp< a[ child])a[i]= std::move( a[ child ]);
        else break;
    }
    a[i]= std::move( tmp );
}
*/
#endif