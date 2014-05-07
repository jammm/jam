#include"minheap.h"
#include<iostream>




class heap
{
	int a[100];
	int size,len;
	heap(int x):size(x-1),len(x-1)
	{}
	int parent(int);
	int left(int);
	int right(int);
	void max_heapify(int);
	void build_max_heap();
}

int heap::parent(int i)
{
	return (i>>1);
}

int heap::left(int i)
{
	return (i<<1) + 1;
}

int heap::right(int i)
{
	return (i<<1) + 2;
}

void heap::max_heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int largest;

	if(l<=size&&a[l]->key>a[i]->key)
		largest = l;
	else
		largest = i;

	if(r<=size&&a[r]->key>a[largest]->key)
		largest = r;

	if(i!=largest)
	{
		std::swap(a[i],a[largest]);
		max_heapify(largest);
	}
}

void heap::build_min_heap()
{
	for(int i=(len/2);i>=0;i--)
	{
		min_heapify(i);
	}
}


void heap::decrease(int i,int x)
{
	if(x>a[i]->key)
	{
		std::cout<<"\nElement greater!";
	}
	else
	{
		a[i]->key = x;
		while(i>0&&a[i]<a[parent(i)])
		{
			std::swap(a[i],a[parent(i)]);
			i = parent(i);
		}
	}
}

void heap::insert(node *x)
{
	size+=1;
	len+=1;
	a[size] = x;
	decrease(size,a[size]->key);
}

bool heap::isPresent(node *x)
{
	for(int i=0;i<=size;i++)
		if(a[i]->ele == x->ele) return true;
	return false;
}

node *heap::extract_min()
{
	node *min = a[0];
	a[0] = a[size];
	size--;
	len--;
	min_heapify(0);
	return min;
}

bool heap::empty()
{
	return size==-1;
}



