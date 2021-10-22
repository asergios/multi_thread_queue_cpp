#include<iostream>
#include<thread>
#include "Queue.h"
using namespace std;

void push_thread(Queue<int>* queue)
{
	while(1)
	{
		// Locks the Mutex
		std::unique_lock<std::mutex> lock(queue->queue_mutex);	
		// Queue is at full capacity, wait for a element to be removed
		while(queue->Count() == queue->Size())					
		{
			// Release the Mutex and suspend the execution of the thread
			queue->block.wait(lock);							
		}

		int random = rand() % 100 + 1;
		queue->Push(random);
		cout << "Push(" + to_string(random) + ")\n";	
		//this_thread::sleep_for(50ms);

		// Unlock Mutex before notifying to prevent other thread from waking up
	 	// 	just to be blocked again afterwards
		lock.unlock();	
		// Notify one thread that might be waiting										
		queue->block.notify_one();								
	}
}

void pop_thread(Queue<int>* queue)
{
	while(1)
	{
		// Locks the Mutex
		std::unique_lock<std::mutex> lock(queue->queue_mutex);	
		// Queue empty, wait for a element to be added
		while(queue->Count() == 0)								
		{
			// Release the Mutex and suspend the execution of the thread
			queue->block.wait(lock);							
		}

		cout << "Removed element:" + to_string(queue->Pop()) + "\n";	
		//this_thread::sleep_for(100ms);

		// Unlock Mutex before notifying to prevent other thread from waking up
	 	// 	just to be blocked again afterwards
		lock.unlock();
		// Notify one thread that might be waiting											
		queue->block.notify_one();								
	}
}

int main()
{

	cout << "Writing Thread 		Queue Reading 		Thread\n";	
	Queue<int> sample(2);
	cout << "New Queue<int>(2)\n";	
	thread t1(push_thread, &sample);
	thread t2(pop_thread, &sample);

	t1.join();
	t2.join();
	
    return 0;
}