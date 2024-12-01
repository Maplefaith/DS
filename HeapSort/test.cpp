#include "HeapSort.h"
#include <iostream>
#include <random>
#include <chrono>
#include <map>
#include <bits/stdc++.h>

const int len = 1000000;
std::vector<int> generateRandomSequence(int length, int min, int max) {
    // 创建随机数生成器和分布
    std::random_device rd;            // 用于生成种子的随机设备
    std::mt19937 gen(rd());           // 基于随机设备的 Mersenne Twister 随机数生成器
    std::uniform_int_distribution<> dis(min, max); // 均匀分布 [min, max]

    std::vector<int> sequence(length);  // 创建一个指定长度的 vector

    // 生成指定长度的随机数序列并填充到 vector 中
    for (int i = 0; i < length; ++i) {
        sequence[i] = dis(gen);  // 生成一个随机数并存入 vector
    }

    return sequence;
}

std::vector<int> generateOrderedSequence(int length, int min, int ratio){
    std::vector<int> sequence(length);
    for (int i = 0; i < length; ++i) {
        sequence[i] = min + i*ratio;  // 连续递增的序列
    }
    return sequence;
}

std::vector<int> generateReverseSequence(int length, int min, int ratio){
    std::vector<int> sequence(length);
    for (int i = 0; i < length; ++i) {
        sequence[length-1-i] = min + i*ratio;  // 连续递增的序列
    }
    return sequence;
}

bool check(std::vector<int> &V){
    int prev=0;
    for(unsigned int i=1;i<V.size();++i){
        if(V[i] < V[prev])return false;
        prev=i;
    }
    return true;
}

void test(){
    std::chrono::duration<double> duration, delta;
    // int number=1;
    std::map<std::string, std::vector<int>> Ses = {};
    // std::vector<std::vector<double>> time={{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
    // for(int i=0;i<number;i++){
    Ses = {
        {"Random Sequence", generateRandomSequence(len, 1, len*10)}, // random sequence
        {"Ordered Sequence", generateOrderedSequence(len, 1, 2)}, // ordered sequence
        {"Reverse Sequence", generateReverseSequence(len, 1, 2)}, // reverse sequence
        {"Repetitive Sequence", generateRandomSequence(len, 1, len/10),} // repetitive sequence
        };
    // int j=0;
    for(auto& it:Ses){
        std::make_heap(it.second.begin(), it.second.end());
        std::vector<int> it2 = it.second;
        // std::cout<<"Sorting " << it.first <<", time cost: ";
        auto start = std::chrono::high_resolution_clock::now();
        HeapSort<int>(it.second);
        auto end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        // time[j][0] +=duration.count();
        std::cout<<"mine = " << duration.count() <<"("<<check(it.second)<<")";

        start = std::chrono::high_resolution_clock::now();
        // HeapSort1<int>(it2);
        // std::make_heap(it2.begin(), it2.end());
        std::sort_heap(it2.begin(), it2.end());
        end = std::chrono::high_resolution_clock::now();
        delta = duration - (end - start);
        duration = end - start;
        // time[j][1] +=duration.count();
        // time[j][2] +=delta.count();
        // ++j;
        std::cout<<", std = " << duration.count() <<"("<<check(it2)<<")"<<", delta = "<<delta.count()<<std::endl;   
    }
    // }
    // int j=0;
    // for(auto& it:Ses){
    //     std::cout << "Sorting "<< it.first<<": ";
    //     for(auto &itr:time[j]){
    //         itr /=number;
    //         std::cout<<itr<<" ";
    //     }
    //     std::cout<<std::endl;
    //     j++;
    // }
    std::cout<<std::endl;
}

int main()
{
    test();
    return 0;
}


/*
        for(auto itr:it.second){
            std::cout<<itr<<" ";
        }
        std::cout<<std::endl;
        for(auto itr:it2){
            std::cout<<itr<<" ";
        }
        std::cout<<std::endl;
        */