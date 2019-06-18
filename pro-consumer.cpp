#include <iostream>
#include <condition_variable>
#include <mutex>

#include <algorithm>
#include <thread>
#include <vector>
#include <stdlib.h>
#include "pro-consumer.h"
using namespace std;


mutex mtx;//��������������Ʒ������
mutex producer_mutex;
mutex consumer_mutex;


std::condition_variable buffer_nofull;//��������ָʾ����������
std::condition_variable buffer_noempty;//��������ָʾ��������Ϊ�գ����ǻ������в�Ʒ

std::chrono::seconds t(1);
std::chrono::microseconds t1(1000);


void produce_item(int i)
{

	std::unique_lock<std::mutex> lck(mtx);
	// item buffer is full, just wait here.
	while (((write_offset + 1) % buffer_size) == read_offset)
	{
		std::cout << "Producer is waiting for an empty slot..." << std::endl;
		buffer_nofull.wait(lck);// �����ߵȴ�"��������Ϊ��"��һ��������.
	}                            //������������֮��Ͳ������������

	data_buffer[write_offset] = produce_buffer[i];//д���Ʒ
	write_offset++;

	if (write_offset == buffer_size)//д���λ������ڶ����������������
	{
		write_offset = 0;
	}

	buffer_noempty.notify_all();//֪ͨ������

	lck.unlock();//����
}

void  consume_item()

{
	std::unique_lock<std::mutex> lck(mtx);
	// item buffer is empty, just wait here.
	while (write_offset == read_offset)
	{
		std::cout << "Consumer is waiting for items..." << std::endl;
		buffer_noempty.wait(lck);// �ȴ�"��������Ϊ��"��һ��������.
	}

	auto data = data_buffer[read_offset];//��ȡ���� ���������߿���ѡ���data���� ���ݴ���


	read_offset++;

	if (read_offset >= buffer_size)
	{
		read_offset = 0;
	}

	buffer_nofull.notify_all();//֪ͨ����������
	lck.unlock();


}

void Producer_thread()
{
	bool ready_to_exit = false;
	while (1)
	{
		std::this_thread::sleep_for(t);
		std::unique_lock<std::mutex> lock(producer_mutex);
		if (produced_item_counter < total_data)
		{
			++produced_item_counter;
			produce_item(produced_item_counter);
			std::cout << "productor thread  finish the " <<  produced_item_counter << "th item : " << produce_buffer[produced_item_counter]<< std::endl;
		}
		else
		{
			ready_to_exit = true;
		}

		lock.unlock();

		if (ready_to_exit == true)
		{
			break;
		}
	}

	cout << "Producer thread " << std::this_thread::get_id()<< " is exiting..." << std::endl;
}

void Consumer_thread()
{
	bool read_to_exit = false;
	while (1)
	{
		std::this_thread::sleep_for(t1);
		std::unique_lock<std::mutex> lck(consumer_mutex);
		if (consumed_item_counter < total_data)
		{
			consume_item();
			
			++consumed_item_counter;
			std::cout << "consumer finish numer: " << consumed_item_counter << std::endl;
			
		}
		else
		{
			read_to_exit = true;
		}

		if (read_to_exit == true)
		{
			break;
		}
	}

	cout << "Consumer thread " << std::this_thread::get_id()<< " is exiting..." << std::endl;
}

//��Բ�ͬ���������� ���������Ҫ���岻ͬ��ʽȥ����produce_buffer�е�����
void generateRandomArray(int rangeL, int rangeR) {

    srand(time(NULL)); // �������
    for (int i = 0; i < total_data; i++)
    {
        produce_buffer[i] = rand() % (rangeR - rangeL + 1) + rangeL;
	}
}

void make_producters(int num,  vector<thread> & productor_vector){

	//׼����������Դ
	generateRandomArray(1,1000);	

	for(int i = 0; i < num; i++)
	{
		productor_vector.push_back(std::thread(Producer_thread));// �����������߳�.
	}

}

void make_consumers(int num, vector<thread> & consumer_vector){

    for(int i = 0; i < num; i++)
	{
		consumer_vector.push_back(std::thread(Consumer_thread));// �����������߳�.
	}

}

