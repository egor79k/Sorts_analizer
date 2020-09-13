#include <iostream>


template <typename T>
void bubble_sort (T *array, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size - i - 1; ++j)
			if (array[j] > array[j + 1])
			{
				std::swap (array[j], array[j + 1]);
				/*T tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;*/
			}
}



template <typename T>
void quick_sort(T *array, size_t size)
{
	int i = 0;
	int j = size - 1;

	T mid = array[size / 2];

	do {        
		while(array[i] < mid)
			++i;

		while(array[j] > mid)
			--j;
	
		if (i <= j)
		{
			std::swap (array[i], array[j]);
			/*T tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;*/

			++i;
			--j;
		}
	}
	while (i <= j);

	if(j > 0)
		quick_sort(array, j + 1);

	if (i < size)
		quick_sort(&array[i], size - i);
}



template <typename T>
void selection_sort (T *array, size_t size)
{
	for (size_t i = 0; i < size - 1; ++i)
	{				
		size_t min_index = i;
		
		for (size_t j = i + 1; j < size; ++j)
		{			
			if (array[j] < array[min_index])				
				min_index = j;
		}
						
		std::swap (array[i], array[min_index]);
	}
}


/*
template <typename T>
void merge(T *array, int first, int last)
{
	int middle = 0;
	int start  = 0;
	int final  = 0;
	T *mas = new T[100];
	middle = (first + last) / 2;
	start = first;
	final = middle + 1;

	for (int j = first; j <= last; ++j)
		if ((start <= middle) && ((final > last) || (array[start] < array[final])))
		{
			mas[j] = array[start];
			++start;
		}
		else
		{
			mas[j] = array[final];
			++final;
		}
	
	for (int j = first; j <= last; ++j)
		array[j] = mas[j];
	
	delete[] mas;
}

template <typename T>
void merge_sort_recursive (T *array, int first, int last)
{
	if (first < last)
	{
		merge_sort_recursive (array, first, (first + last) / 2);
		merge_sort_recursive (array, (first + last) / 2 + 1, last);
		merge (array, first, last);
	}
}

template <typename T>
void merge_sort (T *array, size_t size)
{
	merge_sort_recursive<T> (array, 0, size);
}
*/


template <typename T>
void gnome_sort (T *array, size_t size)
{
	int i = 1;
	int j = 2;
	while (i < size)
	{
		if (array[i - 1] > array[i])
		{
			i = j;
			j = j + 1;
		}
		else
		{
			std::swap (array[i - 1], array[i]);
			i = i - 1;
			if (i == 0)
			{
				i = j;
				j = j + 1;
			}
		}
	}
}