/**
给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

示例:

输入:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 7
解释: 因为路径 1→3→1→1→1 的总和最小。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-path-sum
**/

int minPathSum(vector<vector<int>>& grid) {
    if(0 == grid.size() || 0 == grid[0].size())
        return 0;
    int m = grid.size();
    int n = grid[0].size();
    vector< vector<int> > memory = vector< vector<int> >(m, vector<int>(n));

    memory[0][0] = grid[0][0];
    /**每次只能向下或者向右移动一步**/
    //第一列
    for(int i = 1; i < m; ++i) {
        memory[i][0] = grid[i][0] + memory[i-1][0];
    }
     //第一行
    for(int i = 1; i < n; ++i) {
        memory[0][i] = grid[0][i] + memory[0][i-1];
    }
    
    for(int i = 1; i < m; ++i) {
        for(int j = 1; j < n; ++j) {
            memory[i][j] = grid[i][j] + ((memory[i-1][j] < memory[i][j-1])? memory[i-1][j] : memory[i][j-1]);
        }
    }

    return memory[m-1][n-1];
}