#include "pro-consumer.h"
#include <stdlib.h>

//生成 生产者和消费者
void test_intbuffer(int m , int n )

{
	 std::vector<std::thread> thread_produce;
	 std::vector<std::thread> thread_consume;


	 make_producters(m,thread_produce);
	 make_consumers(n,thread_consume);

	 for (auto &thr1 : thread_produce)
	 {
		thr1.join();
	 }

	 for(auto &thr2 : thread_consume)
	 {
		thr2.join();
	 
	 }
}

int main(int argc, char* argv[]) { 

	if (argc != 3)
	{	
		cout <<"Usage:  IntBufferTest  <#produce_nthread> <#consume_nthreads>"<<endl;
		return 0;
	}
	//生产者个数
    int producer_num = atoi(argv[1]);
	//消费者个数
    int consumer_num  = atoi(argv[2]);


    test_intbuffer(producer_num,consumer_num);
	return 0;
   
}
