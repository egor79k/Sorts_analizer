template <typename T>
class sort_counter
{
private:
	T object;
	static int compares_num;
	static int assigns_num;
	//template <typename Tp>
	//friend void swap (sort_counter<Tp> &A, sort_counter<Tp> &B);

public:
	sort_counter () : object (T ()) {}
	sort_counter (T obj) : object (obj) {}
	sort_counter (const sort_counter &other) = default;
	sort_counter &operator= (const sort_counter &other)
	{
		if (this == &other)
			return *this;
		object = other.object;
		++assigns_num;
		return *this;
	}
	~sort_counter () = default;

	bool operator< (const sort_counter &other)
	{
		++compares_num;
		return object < other.object;
	}

	bool operator> (const sort_counter &other)
	{
		++sort_counter<T>::compares_num;
		return object > other.object;
	}

	static int compares ()
	{ return compares_num; }

	static int assigns ()
	{ return assigns_num; }

	static void reset ()
	{
		compares_num = 0;
		assigns_num  = 0;
	}
};


template <typename T> int sort_counter<T>::compares_num = 0;
template <typename T> int sort_counter<T>::assigns_num = 0;
/*
template <typename T>
void swap (sort_counter<T> &A, sort_counter<T> &B)
{
	printf ("\nswap\n");
	++assigns_num;
	T tmp = A.object;
	A.object = B.object;
	B.object = tmp;
}
*/

/*
int main ()
{
	sort_counter<int> array[10] = {5, 2, 8, 3, 1, 4, 9, 7, 6, 0};
	int size = 10;

	bubble_sort<sort_counter<int>> (array, 10);

	printf("\ncomps: %d, assigns: %d\n", array[0].compares (), array[0].assigns ());
}*/