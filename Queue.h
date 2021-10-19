
template <typename T>
class Queue
{
private:
	int *array;		// Pointer for array where elements will be stored
	int capacity;	// Total size of the Queue
	int count;		// Current total of elements in the queue
	int push_index; // Current index to where next element shall be added 
	int pop_index;  // Current index for where next element shall be removed (first in)

public:
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
		if(count == capacity) return;	// Implement Mutex Here

		array[push_index] = element;
		push_index = (push_index + 1) % capacity;	// Values between 0 - (capacity-1)
		count++;
	}

	// Removes one element from the queue;
	T Pop()
	{
		if(count == 0) return;			// Implement Mutex Here

		pop_index = (pop_index + 1) % capacity;	    // Values between 0 - (capacity-1)
		count--;
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
};