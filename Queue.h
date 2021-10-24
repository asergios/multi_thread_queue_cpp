#include <mutex>
#include <condition_variable>

template <typename T>
class Queue
{
private:
	int *array;			// Pointer for array where elements will be stored
	int capacity;		// Total size of the Queue
	int count;			// Current total of elements in the queue
	int push_index; 	// Current index to where next element shall be added 
	int pop_index;  	// Current index for where next element shall be removed (first in)

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
		// Adds the new element
		array[push_index] = element;		
		// Values between 0 - (capacity-1)			
		push_index = (push_index + 1) % capacity;	
		// Updates total elements in Queue	
		++count;										
	}

	// Removes one element from the queue;
	T Pop()
	{
		// Values between 0 - (capacity-1)
		pop_index = (pop_index + 1) % capacity;	  
		// Updates total elements in Queue  	
		--count;							
		// Return removed element			
		return array[pop_index];						
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

	bool IsFull()
	{
		return count == capacity;
	}

	bool IsEmpty()
	{
		return count == 0;
	}

	// Converts current elements in queue to std::string (useful to print)
	std::string ToString()
	{
		// If empty, return empty string
		if (count == 0) return "";

		// Initialize tmp string to build
		std::string tmp = "";
		int tmp_count = 0;
		// Starts from the oldest element (first to pop) until it reach value of count
		for (int i = (pop_index + 1) % capacity ; tmp_count < count ; i = (i + 1) % capacity)
		{
			tmp += std::to_string(array[i]) + ",";
			++tmp_count;
		}
		
		// Removes last comma
		tmp.pop_back();
		return tmp;
	}
};