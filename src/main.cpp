#include<iostream>
#include<thread>
#include "Queue.h"
using namespace std;

void push_thread(Queue<int>* queue)
{
	while(1)
	{
		// Create value to be added
		int random = rand() % 100 + 1;

		// Locks the Mutex
		std::unique_lock<std::mutex> lock(queue->queue_mutex);	
		// Print status prefix
		cout << "Push(" + to_string(random) + ") ";
		// Queue is at full capacity, wait for a element to be removed
		while(queue->IsFull())					
		{
			cout << " // blocks \n";
			// Release the Mutex and suspend the execution of the thread
			queue->block.wait(lock);		
			cout << "// is released";					
		}

		// Add the element and print status
		queue->Push(random);

		// Print current elements in Queue
		cout << "		" + queue->ToString() + "\n";

		//this_thread::sleep_for(50ms);
		// Unlock Mutex before notifying to prevent other thread from waking up
	 	// 	just to be blocked again afterwards
		lock.unlock();	
		// Notify one thread that might be waiting										
		queue->block.notify_one();	
		//this_thread::sleep_for(20ms);							
	}
}

void pop_thread(Queue<int>* queue)
{
	while(1)
	{
		// Locks the Mutex
		std::unique_lock<std::mutex> lock(queue->queue_mutex);	
		// Queue empty, wait for a element to be added
		while(queue->IsEmpty())								
		{
			// Release the Mutex and suspend the execution of the thread
			queue->block.wait(lock);							
		}

		// Remove the element and print status
		cout << "					Pop() -> " + to_string(queue->Pop()) + "\n";	

		//this_thread::sleep_for(50ms);
		// Unlock Mutex before notifying to prevent other thread from waking up
	 	// 	just to be blocked again afterwards
		lock.unlock();
		// Notify one thread that might be waiting											
		queue->block.notify_one();								
	}
}

int main()
{

	cout << "Writing Thread		Queue		Reading Thread\n";	
	// Initialize Queue class
	Queue<int> sample(2);
	cout << "New Queue<int>(2)\n";	

	// Initialize Push and Pop thread
	thread t_push(push_thread, &sample);
	thread t_pop(pop_thread, &sample);

	// Join threads so that main does not return until threads finish their life cycle
	t_push.join();
	t_pop.join();
	
    return 0;
}