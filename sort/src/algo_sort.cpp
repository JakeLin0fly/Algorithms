#include <iostream>
#include <vector>
using namespace std;

/**
 * 冒泡排序
 * 稳定性：稳定
 * 时间复杂度：O(n*n)
 * 空间复杂度：O(1)
**/
template<class Type>
void bubble_sort(vector<Type>& nums){
    int n = nums.size();
    bool flag = false; // 优化 一次遍历是否发生交换
    while(n > 1){
        for(int i = 0; i+1 < n; ++i){
            if(nums[i] > nums[i+1]){
                swap(nums[i], nums[i+1]);
                flag = true;
            }
        }
        if(!flag)	break;
        flag = false;
        --n;
    }
}


/**
 * 选择排序
 * 稳定性：不稳定（可能打破原来元素的相对位置）
 * 时间复杂度：O(n*n)
 * 空间复杂度：O(1)
**/
template<class Type>
void select_sort(vector<Type>& nums){
    int n = nums,size();
    while(n > 1){
        int max_index = 0;
        for(int i = 1; i < n; ++i){
            if(nums[max_index] < nums[i])
                max_index = i;
        }
        swap(nums[max_index], nums[n-1]);
        --n;
    }
}

/**
 * 插入排序
 * 稳定性：稳定
 * 时间复杂度：O(n*n)
 * 空间复杂度：O(1)
**/
template<class Type>
void insert_sort(vector<Type>& nums){
    int n = nums.size();
    for(int ordered = 1; ordered < n; ++ordered){
        Type value = nums[ordered];
        int i = ordered - 1;
        while(i >= 0 && nums[i] > value){
            nums[i+1] = nums[i];
            --i;
        }
        nums[i+1] = value;
    }
}

/**
 * 希尔排序
 * 稳定性：不稳定（可能打破原来元素的相对位置）
 * 时间复杂度：O(nlogn)
 * 空间复杂度：O(1)
**/
template<class Type>
void shell_sort(vector<Type>& nums){
    int n = nums.size();
    for(int gap = n / 2; gap > 0; gap /= 2){
        for(int i = gap; i < n; ++i){
            int value = nums[i];
            int j = i;
            while(j >= gap && value < nums[j-gap]){
                nums[j] = nums[j-gap];
                j -= gap;
            }
            nums[j] = value;
        }
    }
}