#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <iostream>
#include  "Array.h"
using namespace std;



template <class Item>
void heapify(Item a[], int l, int r)
{
    int max = (r-l);
    int index; int left; int right;
    int i;
    while (i < max)
    {
        index = i;
        left = 2*i + 1;
        right = left + 1;
        if (left < max && a[left] > index)
          index = left;

        if (right < max && a[right] > index)
          index = right;

        if (index == i)
           return;

        swap(a, i, index);
        i = index;
    }
}

template <class Item>
void buildMaxHeap(Item a[], int l, int r)
{
    int i = (r+l) / 2;
    while (i >= l)
    {
        heapify(a, i, r-i);
        i--;
    }    
}

template <typename Item>
void heapsort(Item a[], int l, int r)
{
    buildMaxHeap(a, l, r);
    int last = r;
    while (last > l)
    {
        swap(a, l, last);
        heapify(a, l, last);
        last--;
    }
}

#endif