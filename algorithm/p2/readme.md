## 只要包含了C++的头文件,生成的dll文件python就调用不了!!! 
找不到dependency

## 生成dll
g++(gcc) -shared  Fib.cpp -o Fib.dll -fPIC

## python调用dll
Fib = cdll.LoadLibrary("./Fib.dll")
Fib.get_timeof_DG(20)