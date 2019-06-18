#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic> 
#include "array.h"
using namespace std;

static const int buffer_size = 5;//循环队列的大小
static const int total_data = 30;//要生产的产品数目


static std::size_t read_offset = 0 ;//消费者读取数据的位置
static std::size_t write_offset = 0 ;//生产者写入数据的位置

//原子计数器 记录多个消费者、生产者完成的总读写数
static  std::atomic_long produced_item_counter = { 0 };
static  std::atomic_long consumed_item_counter = { 0 };

//默认使用int类型的buffer , 支持修改类型，修改泛型数组Array 即可，如int改为std::String

static Array<int , buffer_size> data_buffer; //循环队列
static Array<int , total_data> produce_buffer; //生产者数据源队列

//static Array<std::string, buffer_size> data_buffer; //循环队列
//static Array<std::string , total_data> produce_buffer; //生产者数据源队列


void make_producters(int num,  vector<thread> & productor_vector);
void make_consumers(int num, vector<thread> & consumer_vector);

