#include <cstdio>

template <typename T>
class sort_counter
{
private:
	T object;
	static int compares_num;
	static int swaps_num;
	template <typename Tp>
	friend void swap (sort_counter<Tp> &A, sort_counter<Tp> &B);

public:
	sort_counter (T obj) : object (obj) {}
	sort_counter (const sort_counter &other)    = default;
	sort_counter &operator= (const sort_counter &other) = default;
	~sort_counter () = default;

	bool operator< (const sort_counter &other)
	{
		++compares_num;
		return object < other.object;
	}

	bool operator> (const sort_counter &other)
	{
		++compares_num;
		return object > other.object;
	}

	int compares ()
	{ return compares_num; }

	int swaps ()
	{ return swaps_num; }

	void reset ()
	{
		compares_num = 0;
		swaps_num    = 0;
	}
};

template <typename T>
void swap (sort_counter<T> &A, sort_counter<T> &B)
{
	++sort_counter<T>::swaps_num;
	T tmp = A.object;
	A.object = B.object;
	B.object = tmp;
}


int main ()
{
	sort_counter<int> array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (int i = 0; i < 10; ++i)
	{
		if (array[i] < 25)
			printf ("| ");
	}
/*
	printf("comps: %d, swaps: %d\n", array[0].compares (), array[0].swaps ());
	array[0].reset ();
	printf("comps: %d, swaps: %d\n", array[0].compares (), array[0].swaps ());
*/}