#ifndef SORT_H
#define SORT_H

void Sort(int array[], int nval, int& ncomp);
bool Compare(int a, int b);
void QuickSort(int left, int right, int& ncomp);
int Partition(int left, int right, int& ncomp);
int ChoosePivot(int left, int right);
void Swap(int a, int b);

#endif
