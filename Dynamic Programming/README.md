## Dynamic Programming ------ 动态规划

---

### 1 动态规划算法核心

实质是将计算过程**中间值**记录下来，以便后续再次需要计算时直接获取到结果。

### 2 动态规划算法形式

---

以求斐波拉契数列**Fibonacci**为例：

```c++
Fibonacci(n) = 1;	n = 1
Fibonacci(n) = 1;	n = 2
Fibonacci(n) = Fibonacci(n-1) + Fibonacci(n-2);	n > 2
```

递归算法（非动态规划），可能会重复计算同一fib(k)多次，开销大：

```c++
int fib(int n) {
	if(n <= 0)
		return 0;
	if(1 == n || 2 == n)
		return 1;
	
	return fib(n-1)+fib(n-2);
}
```

#### 2.1 自顶向下的备忘录法

---

**memory[n+1]** : n+1大小的数组保存求出的斐波拉契数列中的每一个值

```c++
int Fibonacci(int n) {
    int *memory;
    int res = 0;
	if(n <= 0)
        return 0;
    memory = new int[n+1];
    for(int i = 0; i < n; ++i){
        memory[i] = -1;	//-1 表示未记录计算值
    }
    res = fib(n, memory);
    delete[] memory;
    return res;
}

int fib(int n, int *memory) {
    //如果已经求出了fib（n）的值直接返回
    if(memory[n] != -1)
        return memory[n];
    //否则将求出的值保存在memory备忘录中
    if(n <= 2)
        memory[n]=1;
    else 
        memory[n]=fib(n-1, memory)+fib(n-2, memory);
    return memory[n];
}
```

#### 2.2 自底向上的动态规划

---

```c++
int fib(int n) {
    if(n <= 0)
        return n;
    int *memory = new int[n+1];
    int res;
    memory[0] = 0;
    memory[1] = 1;
    for(int i=2; i <= n; ++i) {
        memory[i] = memory[i-1] + memory[i-2];
	}
    res = memory[n];
    delete[] memory;
    return res;
}
```







### 参考

---

[HankingHu  算法-动态规划 Dynamic Programming--从菜鸟到老鸟](https://blog.csdn.net/u013309870/article/details/75193592)

