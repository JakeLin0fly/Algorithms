//
// Created by JakeLin on 2021/1/8.
//

#ifndef SORT_ALGO_SORT_H
#define SORT_ALGO_SORT_H
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
void bubble_sort(vector<Type>& nums) {
    int n = nums.size();
    bool flag = false; // 优化 一次遍历是否发生交换
    while (n > 1) {
        for (int i = 0; i + 1 < n; ++i) {
            if (nums[i] > nums[i + 1]) {
                swap(nums[i], nums[i + 1]);
                flag = true;
            }
        }
        if (!flag)	break;
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
void select_sort(vector<Type>& nums) {
    int n = nums.size();
    while (n > 1) {
        int max_index = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[max_index] < nums[i])
                max_index = i;
        }
        swap(nums[max_index], nums[n - 1]);
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
void insert_sort(vector<Type>& nums) {
    int n = nums.size();
    for (int ordered = 1; ordered < n; ++ordered) {
        Type value = nums[ordered];
        int i = ordered - 1;
        while (i >= 0 && nums[i] > value) {
            nums[i + 1] = nums[i];
            --i;
        }
        nums[i + 1] = value;
    }
}

/**
 * 希尔排序
 * 稳定性：不稳定（可能打破原来元素的相对位置）
 * 时间复杂度：O(n*logn)
 * 空间复杂度：O(1)
**/
template<class Type>
void shell_sort(vector<Type>& nums) {
    int n = nums.size();
    for (int gap = n / 2; gap > 0; gap /= 2) { // 增量 gap
        for (int i = gap; i < n; ++i) {
            int value = nums[i];
            int j = i;
            // 增量为 gap 的子序列【插入排序】
            while (j >= gap && value < nums[j - gap]) { 
                nums[j] = nums[j - gap];
                j -= gap;
            }
            nums[j] = value;
        }
    }
}

/**
 * 归并排序
 * 稳定性：稳定
 * 时间复杂度：O(n*logn)
 * 空间复杂度：O(n)
**/
template<class Type>
void _merge_sort(vector<Type>& nums, int start, int end) {
    if (start >= end)
        return;
    int mid = start + (end - start) / 2;
    // 递归
    _merge_sort(nums, start, mid);    // [start, mid]
    _merge_sort(nums, mid + 1, end);  // [mid+1, end]
    // 合并
    vector<Type> temp(end - start + 1, 0); // 暂存数组 可只使用一个 O(n)
    int left = start, right = mid + 1, t = 0;
    while (left <= mid && right <= end) {
        if (nums[left] <= nums[right])
            temp[t++] = nums[left++];
        else
            temp[t++] = nums[right++];
    }
    while(left <= mid)
        temp[t++] = nums[left++];
    while(right <= end)
        temp[t++] = nums[right++];
    // 拷贝暂存的有序序列
    t = 0;
    while (start <= end){
        nums[start++] = temp[t++];
    }
}

template<class Type>
void merge_sort(vector<Type>& nums){
    _merge_sort(nums, 0, nums.size() - 1);
}



/**
 * 快速排序
 * 稳定性：不稳定（可能打破原来元素的相对位置）
 * 时间复杂度：O(n*logn)
 * 空间复杂度：O(logn)
**/
template<class Type>
void _quick_sort(vector<Type>& nums, int start, int end) {
    if (start >= end)
        return;
    // 基准 nums[start]
    int low = start, high = end;
    while (low < high) {
        while (low < high && nums[high] >= nums[start])  // 先从右找小于基准
            --high;
        while (low < high && nums[low] <= nums[start])   // 再从左找大于基准
            ++low;
        if (low < high)
            swap(nums[low], nums[high]);
    }
    // 最后将基准归位
    swap(nums[start], nums[low]);  
    // 递归
    _quick_sort(nums, start, low - 1);
    _quick_sort(nums, low + 1, end);
}

template<class Type>
void quick_sort(vector<Type>& nums) {
    _quick_sort(nums, 0, nums.size() - 1);
}

/**
 * 堆排序
 * 稳定性：不稳定（可能打破原来元素的相对位置）
 * 时间复杂度：O(n*logn)
 * 空间复杂度：O(1)
**/
// 自顶向下调整堆 [start, end]
template<class Type>
void adjustMaxHeap(vector<Type>& nums, int start, int end) {
    int dad = start; // 父结点
    int son = dad * 2 + 1;  // 子结点
    while (son <= end) {
        // 选择较大的子结点
        if (son + 1 <= end && nums[son] < nums[son + 1]) {
            ++son;
        }
        if (nums[son] <= nums[dad]) // 满足大顶堆条件
            break;
        else { // 不满足大顶堆添加 交换父子结点 继续向下调整
            swap(nums[dad], nums[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

template<class Type>
void heap_sort(vector<Type>& nums) {
    int n = nums.size();
    // 1. 构建堆 从第一个有孩子的结点开始调整
    for (int i = n / 2 - 1; i >= 0; --i) {
        adjustMaxHeap(nums, i, n - 1);
    }
    // 2. 依次取最大元素放置末尾
    --n;
    while (n > 0) {
        swap(nums[0], nums[n]);
        adjustMaxHeap(nums, 0, --n);
    }
}

/**
 * 计数排序
 * 稳定性：稳定
 * 时间复杂度：O(m+n)
 * 空间复杂度：O(m+n)
**/
template<class Type>
void counting_sort(vector<Type>& nums) {
    int n = nums.size();
    if (n <= 1)
        return;
    // 1. 得到待排序序列的最值 [min, max]
    int min = nums[0];
    int max = nums[0];
    for (int i = 1; i < n; ++i) {
        if (min > nums[i])
            min = nums[i];
        else if (max < nums[i])
            max = nums[i];
    }
    // 2. 统计 [min, max] 中值出现的次数
    int n_count = max - min + 1;
    vector<Type> count(n_count, 0);
    for (int i = 0; i < n; ++i) {
        ++count[nums[i] - min];
    }
    // 3. 对所有的计数累加，得到小于等于该元素的个数（即该元素排序的位置）
    for (int i = 1; i < n_count; ++i) {
        count[i] += count[i - 1];
    }
    // 4. 反向填充临时数组
    vector<Type> temp(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        temp[--count[nums[i] - min]] = nums[i];
    }
    // 5. 给目标数组赋值
    for (int i = 0; i < n; ++i) {
        nums[i] = temp[i];
    }
}

/**
 * 桶排序
 * 稳定性：稳定
 * 时间复杂度：O(n+m)
 * 空间复杂度：O(n+m)
**/
template<class Type>
void bucket_sort(vector<Type>& nums) {
    int n = nums.size();
}

/**
 * 基数排序
 * 稳定性：稳定
 * 时间复杂度：O(n*m)
 * 空间复杂度：O(n+m)
**/
template<class Type>
void radix_sort(vector<Type>& nums) {
    int n = nums.size();
}


#endif //SORT_ALGO_SORT_H