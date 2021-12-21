#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

template <class Item>
void swap(Item a[], int l, int r)
{
    Item tmp = a[l];
    a[l] = a[r];
    a[r] = tmp;
}

template <class Item>
Item* randArray(int n)
{
    Item* ret = new Item[n];
    for (int i = 0; i < n; i++)
    {
        ret[i] = rand() % 1000;
    }
    return ret;
}

template <class Item>
Item* copyArray(Item a[], int n)
{
    Item* ret = new Item[n];
    for (int i = 0; i < n; i++)
       ret[i] = a[i];
    return ret;
}

template <class Item>
void printArray(Item a[], int n)
{
    for (int i = 0; i < n; i++)
        cout<<a[i]<<" ";
    cout<<"\n";
}

template <class Item>
bool checkSort(Item a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i+1])
        {
            cout<<"Sort failed at: "<<i<<"\n";
            return false;
        }
    }
    cout<<"Sort complete.\n";
    return true;
}

#endif