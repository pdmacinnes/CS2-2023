#include "sort.h"

static int n, nlast;
static int* value;
static int cCount = 0;

void Sort(int array[], int nval, int& ncomp) {
    n = nval;
    nlast = n - 1;
    value = array;
    cCount = 0;
    QuickSort(0, nlast, ncomp);
    ncomp = cCount;
}


bool Compare(int a, int b) {
    cCount++;
    return value[a] < value[b];
}


void QuickSort(int left, int right, int& ncomp) {
    if (left < right) {
        int pivotIndex = Partition(left, right, ncomp);
        QuickSort(left, pivotIndex - 1, ncomp);
        QuickSort(pivotIndex + 1, right, ncomp);
    }
}

int Partition(int left, int right, int& ncomp) {
    int pivotIndex = ChoosePivot(left, right);
    Swap(left, pivotIndex);
    int pivot = left;
    left++;

    while (left <= right) {
        while (left <= right && !Compare(left, pivot)) {
            left++;
        }
        while (left <= right && Compare(right, pivot)) {
            right--;
        }
        if (left < right) {
            Swap(left, right);
        }
    }

    Swap(pivot, right);
    return right;
}

int ChoosePivot(int left, int right) {
    return left;
}

void Swap(int a, int b) {
    int temp = value[a];
    value[a] = value[b];
    value[b] = temp;
}

