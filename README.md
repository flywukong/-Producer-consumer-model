# README



## 项目介绍

### 问题描述
解决生产消费者问题，采用多生产者多消费者模式，问题描述如下
有1组生产者M个， 一组消费者N个， 一个容量为X的Buffer , 生产者往Buffer里面写入数据

消费者从Buffer中消费数据, 其中M > 1, N > 1, X > 0。 其中Buffer可以支持任意类型数据上传

###  代码设计

（1）在pro-consumer.h 全局变量中定义data_buffer , 循环队列实现缓冲区，另外为了生成测试数据源 produce_buffer表示生产者所有要上传的数据，total_data表示生产者要上传的总数据量

（2）使用泛型数组Array， 定义buffer , 从而能够支持不同的数据类型 

（3）消费者生产者模型方面，使用 互斥锁+条件变量的方法实现同布，使用计数器来跟踪多个消费者和生产者的进度

```
[wuchen@saltstack001 pro-consume]$ ll
total 28
-rw-rw-r-- 1 wuchen wuchen 1088 Jun 18 13:49 array.h
-rw-rw-r-- 1 wuchen wuchen 1630 Jun 18 14:14 cmake_install.cmake
-rw-rw-r-- 1 wuchen wuchen  278 Jun 18 15:43 CMakeLists.txt
-rw-rw-r-- 1 wuchen wuchen  745 Jun 18 16:04 intBuffer_test.cpp
-rw-r--r-- 1 wuchen wuchen 3675 Jun 18 16:04 pro-consumer.cpp
-rw-rw-r-- 1 wuchen wuchen  893 Jun 18 15:59 pro-consumer.h
-rw-r--r-- 1 wuchen wuchen 1211 Jun 18 16:07 README.md

```
intBuffer_test.cpp 为整形buffer的测试文件，pro-consumer.cpp实现了核心生产消费者线程模型，pro-consumer.h 定义了全局变量


###  编译执行

编程语言使用C++ , 使用了C11 智能指针和thread特性。

```
cmake .

make

./IntBufferTest  5 5
```
可执行程序IntBufferTest  后面跟的两个参数分别是生产者的数目 和消费者的数目 ,  如果要修改buffer缓冲区大小 可以在pro-consumer.h 修改buffer_size 长度

如果要修改不同的buffer 缓冲区类型，需要修改pro-consumer.h定义的Array 泛型类型，并且在pro-consumer.cpp中修改generateRandomArray实现，该函数实现了某种数据类型的数据源生产功能。




