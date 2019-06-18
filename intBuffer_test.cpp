#include "pro-consumer.h"
#include <stdlib.h>

//生成 生产者和消费者
void test_intbuffer(int m , int n )

{
	 std::vector<std::thread> thread_vector1;
	 std::vector<std::thread> thread_vector2;


	 make_producters(m,thread_vector1);
	 make_consumers(n,thread_vector2);

	 for (auto &thr1 : thread_vector1)
	 {
		thr1.join();
	 }

	 for(auto &thr2 : thread_vector2)
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

    test_intbuffer( producer_num,consumer_num);

	return 0;
   
}
