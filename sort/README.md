### 排序算法

排序算法可以分为内部排序和外部排序，**内部排序**是数据记录在内存中进行排序，而**外部排序**是因排序的数据很大，一次不能容纳全部的排序记录，在排序过程中需要访问外存。【*图片来自网络*】

![sort](./sort.png)

![sort2](./sort2.png)

#### 冒泡排序

> 顾名思义，就像一堆气泡，大的气泡往上冒，一次遍历完的结果是待排序的气泡中最大的气泡冒出到有序序列。

【步骤】

1. 从第一个元素开始比较相邻元素，若前者更大，则交换这两个元素；
2. 一次遍历完，一个元素完成有序；
3. 重复第一步，直到所有元素有序。

【**优化**】**当一次遍历结束，没有发生交换，整个序列便已完成排序。**

```cpp
/**
 * 冒泡排序
 * 稳定性：稳定
 * 时间复杂度：O(n*n)
 * 空间复杂度：O(1)
**/
template<class T>
void bubble_sort(vector<T>& nums){
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
```

#### 选择排序

> 每次遍历，选择待排序元素中最大元素，放置到待排序子数组最后位置。一次遍历至多只进行交换一次。

【步骤】

1. 遍历待排序子数组，选择最大待排序元素；
2. 将待排序最大元素放置在待排序子数组最后位置；
3. 重复第一步，直到所有元素有序。

```cpp
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
```

#### 插入排序

> 将待排序元素依次插入有序序列

【步骤】

1. 将第一个元素视为有序序列，往后为待排序序列；
2. 依次向有序序列插入元素到合适的位置。

```cpp
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
```

#### 希尔排序

> 也称递减增量排序算法，希尔排序是基于插入排序的以下两点性质而提出改进方法的：
>
> - 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率；
> - 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位；

【图解】

参考：https://www.cnblogs.com/chengxiao/p/6104371.html

```cpp
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
```



#### 归并排序

#### 快速排序

#### 堆排序

#### 计数排序

#### 桶排序

#### 基数排序



#### 