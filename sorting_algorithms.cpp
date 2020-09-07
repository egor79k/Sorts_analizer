#include <iostream>

template <typename T>
void bubble_sort (T *array, size_t n)
{
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n - i - 1; ++j)
			if (array[j] > array[j + 1])
			{
				T tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}

	return;
}


template <typename T>
void print (T *array, size_t n)
{
	std::cout << '\n';
	for (size_t i = 0; i < n; ++i)
		std::cout << array[i] << ' ';
	std::cout << '\n';
	return;
}


int main ()
{
	int array[10] = {5, 2, 8, 3, 1, 4, 9, 7, 6, 0};

	print<int> (array, 10);

	bubble_sort<int> (array, 10);

	print<int> (array, 10);

	return 0;
}