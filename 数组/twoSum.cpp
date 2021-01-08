/**
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

 

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
**/
/**
    target 可能为 正整数、0、负整数
**/
vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<int> ans(2, -1); //记录返回结果

    int sub_value;  
    map<int, int>::iterator iter;
    // key  ---- (num[i])
    //value ---- i
    map<int, int> map_index;    
    for(int i = 0; i < n; ++i) {
        sub_value = target - nums[i];
        iter = map_index.find(sub_value);
        if(map_index.end() != iter) {
            ans[0] = iter->second;
            ans[1] = i;
            break;
        }
        map_index.insert(pair<int, int>(nums[i], i));
    }

    return ans;
    }