template <typename T>
class sort_counter
{
private:
	T object;
	static int compares_num;
	static int assigns_num;

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