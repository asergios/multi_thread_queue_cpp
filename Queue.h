#include <mutex>
#include <condition_variable>

template <typename T>
class Queue
{
private:
	int *array;						// Pointer for array where elements will be stored
	int capacity;					// Total size of the Queue
	int count;						// Current total of elements in the queue
	int push_index; 				// Current index to where next element shall be added 
	int pop_index;  				// Current index for where next element shall be removed (first in)

public:
	std::mutex queue_mutex; 		// Protects against race conditions of shared variables
	std::condition_variable block; 	// Block thread while it waits for new data to be added or removed
	
	// Call constructor
	Queue(int size)
	{
		array = new T[size];
		capacity = size;
		count = 0;
		push_index = 0;
		pop_index = -1;
	}

	// Adds one element to the end of the queue;
	void Push(T element)
	{
		array[push_index] = element;					// Adds the new element
		push_index = (push_index + 1) % capacity;		// Values between 0 - (capacity-1)
		++count;										// Updates total elements in Queue
	}

	// Removes one element from the queue;
	T Pop()
	{
		pop_index = (pop_index + 1) % capacity;	    	// Values between 0 - (capacity-1)
		--count;										// Updates total elements in Queue
		return array[pop_index];						// Return removed element
	}

	// Returns the current number of elements in the queue;
	int Count()
	{
		return count;
	}

	// Returns the max size of the queue;
	int Size()
	{
		return capacity;
	}
};