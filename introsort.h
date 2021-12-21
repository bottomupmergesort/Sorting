#ifndef INTROSORT_H
#define INTROSORT_H

#include <cmath>
#include "Array.h"
#include "heapsort.h"

template <class Item>
void medof3(Item a[], int m1, int m2, int m3)
{
   if (m2 < m1)
     swap(a, m1, m2);
   if (m3 < m2)
   {
       swap(a, m3, m2);
       if (m2 < m1)
         swap(a, m2, m1);
   }
}

template <class Item>
int partition(Item a[], int l, int r)
{
    medof3(a, l, (r+l) /2, r);
    swap(a, (r+l)/2, r);
    int i = l - 1;
    int j = r;
    Item v = a[r];
    while (true)
    {
        while (a[++i] < v);
        while (v < a[--j]);
        if (i >= j) break;
        swap(a, i, j);
    }
    swap(a, i, r);
    return i;
}

template <class Item>
void intro_sort(Item a[], int l, int r, int depthLimit)
{
    if (r <= 1) return;

    if (depthLimit == 0)
    {
        heapsort(a, l, r);
        return;
    }
    depthLimit--;
    if (r - l >= 16)
    {
        int i = partition(a, l, r);
        intro_sort(a, l, i-1, depthLimit);
        intro_sort(a, i+1, r, depthLimit);
    }
}

template <class Item>
void introsort(Item a[], int l, int r)
{
    int dl = 2 * log(r-l+1);
    intro_sort(a, l, r, dl);
    for (int i = l; i <= r; i++)
    {
        int j = i;
        Item v = a[j];
        while (j >= l && a[j-1] > v)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = v;
    }
}

#endif