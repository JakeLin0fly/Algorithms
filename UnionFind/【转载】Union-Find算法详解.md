【<font color=red>**声明**</font>】 **本文转载自 [Union-Find算法详解 - GitHub](https://github.com/labuladong/fucking-algorithm/blob/master/算法思维系列/UnionFind算法详解.md)** 

 Union-Find 算法，也就是常说的并查集算法，主要是解决图论中「**动态连通性**」问题的。

### 问题描述

简单说，动态连通性其实可以抽象成给一幅有 `N` 个结点的图连线，其中结点按 0~N 编号。

Union-Find 算法主要需要实现以下API：

```cpp
class UnionFind {
public:
    /* 将 a 和 b 连接(连通) */
    void connect(int a, int b);

    /* 判断 a 和 b 是否连通 */
    bool isConnected(int a, int b);

    /* 返回图中的连通分量 */
    int getCount();
}
```

这里所说的「连通」是一种等价关系，也就是说具有如下三个性质：

1、自反性：结点 `a` 和 `a` 是连通的。

2、对称性：如果结点 `a` 和 `b` 连通，那么 `b` 和 `a` 也连通。

3、传递性：如果结点 `a` 和 `b` 连通， `b` 和 `c` 连通，那么 `a` 和 `c` 也连通。

### 基本思路

假定我们使用森林（若干棵树）来表示图的动态连通性，用数组来具体实现这个森林。怎么用森林来表示连通性呢？我们设定树的每个节点有一个指针指向其父节点，如果是根节点的话，这个指针指向自己。

```cpp
class UnionFind {
public:
    UnionFind(int n);
    /* 将 a 和 b 连接(连通) */
    void connect(int a, int b);

    /* 判断 a 和 b 是否连通 */
    bool isConnected(int a, int b);

    /* 返回图中的连通分量 */
    int getCount() { return count; };
    
private:
    /* 返回结点 x 的根节点 */
    int findRoot(int x);
    
    /** 其他函数 **/
private:
    int count;			// 连通分量
    vector<int> parent;	// parent[i]: 结点 i 的父节点
};
```

如果某两个节点被连通，则让其中的（任意）一个节点的根节点接到另一个节点的根节点上：

```cpp
UnionFind::UnionFind(int n) : count(n) {
    // 初始时所有结点互不连通
    // 父节点指向自己
    for (int i = 0; i < n; ++i){
        parent.push_back(i);
    }
}
/* 判断 a 和 b 是否连通 */
void UnionFind::connect(int a, int b) {
    int rootA = findRoot(a);
    int rootB = findRoot(b);
    if (rootA == rootB)
        return ;
    // 将一棵树接在另一棵树上
    parent[a] = rootB;
    // 连通分量 -1
    --count;
}
/* 判断 a 和 b 是否连通 */
bool UnionFind::isConnected(int a, int b) {
    return findRoot(a) == findRoot(b);
}
/* 返回结点 x 的根节点 */
int UnionFind::findRoot(int x) {
    // 根结点有 x == parent[x]
    while (x != parent[x])
        x = parent[x];
    return x;
}
```

我们发现，主要 API `isConnected` 和 `connect` 中的复杂度都是 `findRoot` 函数造成的，所以说它们的复杂度和 `findRoot` 一样。`findRoot` 主要功能就是从某个节点向上遍历到树根，其时间复杂度就是树的高度。我们可能习惯性地认为树的高度就是 `logN`，但这并不一定。`logN` 的高度只存在于平衡二叉树，对于一般的树可能出现极端不平衡的情况，使得「树」几乎退化成「链表」，树的高度**最坏情况**下可能变成 `N`。

### 平衡性优化

我们一开始就是简单粗暴的把 `a` 所在的树接到 `b` 所在的树的根节点下面，那么这里就可能出现「头重脚轻」的不平衡状况。**我们其实是希望，小一些的树接到大一些的树下面，这样就能避免头重脚轻，更平衡一些**。解决方法是额外使用一个 `size` 数组，记录每棵树包含的节点数，我们不妨称为「重量」：

```cpp
class UnionFind {
public:
    UnionFind(int n);
    /* 将 a 和 b 连接(连通) */
    void connect(int a, int b);

    /* 判断 a 和 b 是否连通 */
    bool isConnected(int a, int b);

    /* 返回图中的连通分量 */
    int getCount() { return count; };
    
private:
    /* 返回结点 x 的根节点 */
    int findRoot(int x);
    
    /** 其他函数 **/
private:
    int count;			// 连通分量
    vector<int> parent;	// parent[i]: 结点 i 的父节点
    // 新增一个数组记录树的 “重量”
    vector<int> size;
};
```

```cpp
UnionFind::UnionFind(int n) : count(n) {
    // 初始时所有结点互不连通
    // 父节点指向自己
    for (int i = 0; i < n; ++i){
        parent.push_back(i);
        // 重量应该初始化 1
        size.push_back(1);
    }
}
/* 将 a 和 b 连接(连通) */
void UnionFind::connect(int a, int b) {
    int rootA = findRoot(a);
    int rootB = findRoot(b);
    if (rootA == rootB)
        return ;
    // 小树根节点接到大树根节点下 「较平衡」
    if (size[rootA] < size[rootB]){
        parent[rootA] = rootB;
        size[rootB] += size[rootA];
    } else {
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
    }
    // 连通分量 -1
    --count;
}
```

这样，通过比较树的重量，就可以保证树的生长相对平衡，树的高度大致在 `logN` 这个数量级，极大提升执行效率。此时，`findRoot` 、`connect`、`isConnected` 的时间复杂度都下降为 `O(logN)` 。

### 路径压缩

我们能不能进一步压缩每棵树的高度，使树高始终保持为常数？这样`findRoot` 就能以 `O(1)` 的时间找到某一节点的根节点，相应的， `connect` 和 `isConnected`  复杂度都下降为 `O(1)` 。要做到这一点，非常简单，只需要在 `findRoot`  中加一行代码：

```cpp
int UnionFind::findRoot(int x) {
    // 根结点有 x == parent[x]
    while (x != parent[x]) {
        // 「路径压缩」 减少查询迭代次数
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}
```

