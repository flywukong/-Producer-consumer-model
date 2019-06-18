#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic> 
#include "array.h"
using namespace std;

static const int buffer_size = 5;//ѭ�����еĴ�С
static const int total_data = 30;//Ҫ�����Ĳ�Ʒ��Ŀ


static std::size_t read_offset = 0 ;//�����߶�ȡ���ݵ�λ��
static std::size_t write_offset = 0 ;//������д�����ݵ�λ��

//ԭ�Ӽ����� ��¼��������ߡ���������ɵ��ܶ�д��
static  std::atomic_long produced_item_counter = { 0 };
static  std::atomic_long consumed_item_counter = { 0 };

//Ĭ��ʹ��int���͵�buffer , ֧���޸����ͣ��޸ķ�������Array ���ɣ���int��Ϊstd::String

static Array<int , buffer_size> data_buffer; //ѭ������
static Array<int , total_data> produce_buffer; //����������Դ����

//static Array<std::string, buffer_size> data_buffer; //ѭ������
//static Array<std::string , total_data> produce_buffer; //����������Դ����


void make_producters(int num,  vector<thread> & productor_vector);
void make_consumers(int num, vector<thread> & consumer_vector);

