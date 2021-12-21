#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <random>
#include "Array.h"
#include "introsort.h"
#include "heapsort.h"
#include "mergesort.h"
using namespace std;

template <class Item>
void stdsort(Item a[], int l, int r)
{
    std::sort(a+l, a+r+1);
}

template <class Item>
void stdstable(Item a[], int l, int r)
{
    std::stable_sort(a+l, a+r+1);
}

template <class Item>
double timedrun(Item a[], int l, int r, void sortfunc(Item a[], int l, int r))
{
    std::chrono::duration<double, std::milli> timing;
    auto t1 = std::chrono::steady_clock::now();
    sortfunc(a, l, r);
    auto t2 = std::chrono::steady_clock::now();
    timing = t2 - t1;
    return timing.count();
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, std::numeric_limits<int>::max());
    double a, b, c, d;
    cout<<"    Items      Introsort\tstd::sort\tMergesort/O\tstd::stable_sort\n";
    for (int n = 25; n <= 2500000; n *= 10)
    {
        int** to_sort = new int*[4];
        for (int j = 0; j < 4; j++)
                to_sort[j] = new int[n];
        for (int i = 0; i < n; i++)
        {
            int p = dist(gen);
            for (int j = 0; j < 4; j++)
                to_sort[j][i] = p;
        }
        int p = rand() % (566421);
        a = timedrun(to_sort[0], 0, n-1, introsort);
        b = timedrun(to_sort[1], 0, n-1, stdsort);
        c = timedrun(to_sort[2], 0, n, mergesort);
        d = timedrun(to_sort[3], 0, n-1, stdstable);
        cout<<setw(7)<<n<<": \t"<<a<<" \t"<<b<<" \t"<<c<<" \t"<<d<<"\n";
    } 
    int* test = randArray<int>(25);
    printArray(test, 25);
    mergesort(test, 0, 25);
    printArray(test, 25);
    return 0;
}