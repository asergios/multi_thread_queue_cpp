#include<iostream>
#include<thread>
#include "Queue.h"
using namespace std;

void push_thread(Queue<int>* queue)
{
	while(1)
	{
		std::unique_lock<std::mutex> lock(queue->queue_mutex);	// Locks the Mutex
		while(queue->Count() == queue->Size())					// Queue is at full capacity, wait for a element to be removed
		{
			queue->block.wait(lock);							// Release the Mutex and suspend the execution of the thread
		}

		int random = rand() % 100 + 1;
		queue->Push(random);
		cout << "Push(" + to_string(random) + ")\n";	
		//this_thread::sleep_for(50ms);

		lock.unlock();											// Unlock Mutex before notifying to prevent other thread from waking up
	 	 														// 	just to be blocked again afterwards
		queue->block.notify_one();								// Notify one thread that might be waiting
	}
}

void pop_thread(Queue<int>* queue)
{
	while(1)
	{
		std::unique_lock<std::mutex> lock(queue->queue_mutex);	// Locks the Mutex
		while(queue->Count() == 0)								// Queue empty, wait for a element to be added
		{
			queue->block.wait(lock);							// Release the Mutex and suspend the execution of the thread
		}

		cout << "Removed element:" + to_string(queue->Pop()) + "\n";	
		//this_thread::sleep_for(100ms);

		lock.unlock();											// Unlock Mutex before notifying to prevent other thread from waking up
	 	 														// 	just to be blocked again afterwards
		queue->block.notify_one();								// Notify one thread that might be waiting
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