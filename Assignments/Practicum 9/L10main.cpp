/*
*  This is the main program for Practicum                *
*  It generates a sequence of random shuffles of a set   *
*  of integers so that a sort function can be used and   *
*  Requires a function with prototype                    *
*     void Sort(int[],int,int&);                         *
*  which sorts am array of a specified length, returning *
*  the number of comparisons made between data values.   *
*/

#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

void Sort(int[],int,int&);

int main()
{
	int sample[10000];
	int i, j, k, n, temp, ncomp;

	srand(time(0));
#ifndef PRINT
	cout << "Performance of a sort algorithm\nNumber of values\nNumber of comparisons\n";
#endif	
	for (i=0;i<10000;i++)
		sample[i] = i;		// fill the array with consecutive integers
	for (i=1;i<101;i++)
	{
		n = 100*i;		// for n = 100,200,...,10000	
		for (j=0;j<n;j++)
		{
			k = rand()%(n-j)+j;	// shuffle the n integers
			if (k != j)
			{
				temp = sample[j];
				sample[j] = sample[k];
				sample[k] = temp;
			}
		}
		Sort(sample,n,ncomp);		//sort them
#ifdef PRINT
		cout << "For " << n << " values\n";	// print out to see if it sorts
		for (j=0;j<n;j++)
		{
			cout << sample[j];
			if (j%10 == 9)
				cout << endl;
			else
				cout << '\t';
		}
#else
		if (i%5 == 0)
			cout << n << '\t' << ncomp << endl;	// print out graph data
		else
			cout << "_\t" << ncomp << endl;
#endif	
	}
	return 0;
}
	
