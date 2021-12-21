#include "Array.h"

template <class Item>
void merge(Item a[], Item temp[], int l, int m, int r)
{
    int i = l, j = m, k = 0;
    while (i < m && j < r)
    {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i < m) temp[k++] = a[i++];
    while (j < r) temp[k++] = a[j++];
    for (k = l; k < r; k++)
        a[k] = temp[k-l];
}

template <class Item>
void merge_sort(Item a[], Item temp[], int l, int r)
{
    if (r - l <= 9)
    {
        for (int i = l; i < r; i++)
        {
            int j = i;
            Item v = a[j];
            while (j > l && a[j-1] > v)
            {
                a[j] = a[j-1];
                j--;
            }
            a[j] = v;
        }
    } 
    else
    {
        int m = (r+l) / 2;
        merge_sort(a, temp, l, m);
        merge_sort(a, temp, m, r);
        merge(a, temp, l, m, r);
    }
}

template <class Item>
void mergesort(Item a[], int l, int r)
{
    Item* temp = new Item[r+1];
    for (int i = 0; i < r; i++) temp[i] = 0;
    merge_sort(a, temp, l, r);
}