
#include <stdlib.h>
#include <stdio.h>

#define INSERTION_SORT_BOUND 16 /* boundary point to use insertion sort */
//typedef int T;
#define uint32 unsigned int
/* explain function
 * Description:
 *   fixarray::Qsort() is an internal subroutine that implements quick sort.
 *
 * Return Value: none
 */
#define GREATER(a , b) (a > b)
template<typename T>
static void Qsort(T This[],uint32 first, uint32 last)
{
	uint32 stack_pointer = 0;
	int first_stack[32];
	int last_stack[32];

	for (;;)
	{
		if (last - first <= INSERTION_SORT_BOUND)
		{
			/* for small sort, use insertion sort */
			uint32 indx;
			T prev_val = This[first];
			T cur_val;

			for (indx = first + 1; indx <= last; ++indx)
			{
				cur_val = This[indx];
				if (prev_val > cur_val )
				{
					/* out of order: array[indx-1] > array[indx] */
					uint32 indx2;
					This[indx] = prev_val; /* move up the larger item first */

					/* find the insertion point for the smaller item */
					for (indx2 = indx - 1; indx2 > first; )
					{
						T temp_val = This[indx2 - 1];
						if (GREATER(temp_val, cur_val) )
						{
							This[indx2--] = temp_val;
							/* still out of order, move up 1 slot to make room */
						}
						else
							break;
					}
					This[indx2] = cur_val; /* insert the smaller item right here */
				}
				else
				{
					/* in order, advance to next element */
					prev_val = cur_val;
				}
			}
		}
		else
		{
			int pivot;

			/* try quick sort */
			{
				T temp;
				uint32 med = (first + last) >> 1;
				/* Choose pivot from first, last, and median position. */
				/* Sort the three elements. */
				temp = This[first];
				if (GREATER(temp, This[last]) )
				{
					This[first] = This[last]; This[last] = temp;
				}
				temp = This[med];
				if (GREATER(This[first], temp) )
				{
					This[med] = This[first]; This[first] = temp;
				}
				temp = This[last];
				if (GREATER(This[med], temp) )
				{
					This[last] = This[med]; This[med] = temp;
				}
				pivot = This[med];
			}
			{
				uint32 up;
				{
					uint32 down;
					/* First and last element will be loop stopper. */
					/* Split array into two partitions. */
					down = first;
					up = last;
					for (;;)
					{
						do
						{
							++down;
						} while (GREATER(pivot, This[down]) );

						do
						{
							--up;
						} while (GREATER(This[up], pivot) );

						if (up > down)
						{
							T temp;
							/* interchange L[down] and L[up] */
							temp = This[down]; This[down]= This[up]; This[up] = temp;
						}
						else
							break;
					}
				}
				{
					uint32 len1; /* length of first segment */
					uint32 len2; /* length of second segment */
					len1 = up - first + 1;
					len2 = last - up;
					/* stack the partition that is larger */
					if (len1 >= len2)
					{
						first_stack[stack_pointer] = first;
						last_stack[stack_pointer++] = up;

						first = up + 1;
						/*  tail recursion elimination of
						 *  Qsort(This,fun_ptr,up + 1,last)
						 */
					}
					else
					{
						first_stack[stack_pointer] = up + 1;
						last_stack[stack_pointer++] = last;

						last = up;
						/* tail recursion elimination of
						 * Qsort(This,fun_ptr,first,up)
						 */
					}
				}
				continue;
			}
			/* end of quick sort */
		}
		if (stack_pointer > 0)
		{
			/* Sort segment from stack. */
			first = first_stack[--stack_pointer];
			last = last_stack[stack_pointer];
		}
		else
			break;
	} /* end for */
}

void quickSort(float This[], uint32 the_len)
{
	Qsort(This, 0, the_len - 1);
}

void quickSort(unsigned int* This, uint32 the_len)
{
	Qsort<unsigned int>(This, 0, the_len - 1);
}

void quickSort(int This[], uint32 the_len)
{
	Qsort<int>(This, 0, the_len - 1);
}
#ifdef MAIN__ 
void ArraySort(int This[], uint32 the_len)
{
	Qsort(This,  0, the_len - 1);
}

#define ARRAY_SIZE 250000

int my_array[ARRAY_SIZE];

uint32 fill_array()
{
	int indx;
	uint32 checksum = 0; 
	for (indx=0; indx < ARRAY_SIZE; ++indx)
	{
		checksum += my_array[indx] = rand();
	}
	return checksum;
}

int main()
{
	int indx;
	uint32 checksum1; 
	uint32 checksum2 = 0;
	checksum1 = fill_array();

	ArraySort(my_array,  ARRAY_SIZE);

	for (indx=1; indx < ARRAY_SIZE; ++indx)
	{
		if (my_array[indx - 1] > my_array[indx])
		{
			printf("bad sort\n");
			return(1);
		}
	}

	for (indx=0; indx < ARRAY_SIZE; ++indx)
	{
		checksum2 += my_array[indx];
	}

	if (checksum1 != checksum2)
	{
		printf("bad checksum %d %d\n", checksum1, checksum2);
		return(1);
	}

	return(0);
}

#endif 
