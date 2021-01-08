#include <iostream>
#include <vector>
#include "algo_sort.h"

using namespace std;

template<class Type>
void show(vector<Type>& nums) {
    for (auto& val : nums) {
        std::cout << val << " ";
    }
    cout << endl;
}

void pleaseInput() {
    cout << "1. 冒泡排序\n"
        << "2. 选择排序\n"
        << "3. 插入排序\n"
        << "4. 希尔排序\n"
        << "5. 归并排序\n"
        << "6. 快速排序\n"
        << "7. 堆排序\n"
        << "8. 计数排序\n"
        << "9. 桶排序\n"
        << "10. 基数排序\n"
        << "0. 退出\n";
}

int main() {
    while (true) {
        vector<int> nums = { 2, 53, 32, 32, 3, 2, 435, 6, 9, 45, 44, 7, 13, 39, 66 };
        int func;
        pleaseInput();
        cin >> func;
        cout << "排序前："; show(nums);
        switch (func) {
        case 1:
            cout << "冒泡排序: ";
            bubble_sort(nums);
            break;
        case 2:
            cout << "选择排序: ";
            select_sort(nums);
            break;
        case 3:
            cout << "插入排序: ";
            insert_sort(nums);
            break;
        case 4:
            cout << "希尔排序: ";
            shell_sort(nums);
            break;
        case 5:
            cout << "归并排序: ";
            merge_sort(nums);
            break;
        case 6:
            cout << "快速排序: ";
            quick_sort(nums);
            break;
        case 7:
            cout << "堆排序: ";
            heap_sort(nums);
            break;
        case 8:
            cout << "计数排序: ";
            counting_sort(nums);
            break;
        case 9:
            cout << "桶排序: ";
            bucket_sort(nums);
            break;
        case 10:
            cout << "基数排序: ";
            radix_sort(nums);
            break;
        case 0:
            return 0;
        default:;
        }
        show(nums);
    }

    return 0;
}
