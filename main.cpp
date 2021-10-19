#include<iostream>
#include "Queue.h"
using namespace std;

int main()
{

	Queue<int> sample(5);

	// Fill queue
	sample.Push(1);
	sample.Push(2);
	sample.Push(3);
	// Pop from queue
	cout << sample.Pop();
	cout << sample.Pop();
	cout << sample.Pop();
	cout << sample.Pop();
	cout << sample.Pop();

    return 0;
}