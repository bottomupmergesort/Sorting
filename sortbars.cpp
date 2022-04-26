//STL components
#include <random>  //pnrg
#include <vector>  //vector array
#include <thread>  //for this_thread::sleep_for()
#include <chrono>  // for chrono::duration
#include <utility>
#define min(A, B) (A < B) ? A:B
//for graphics
#include <BearLibTerminal.h>

#define INFLOOP for (;;)

using namespace std;

const bool BARS = true;
const bool STARS = false;

bool style = BARS;

class Bar 
{
    public:
    int x;
    int y;
    int height;
    string color;
    Bar(int X, int ht)
    {
        x = X; y = 38 - ht; height = ht;
        color = "red";
    }
    //operators for sorting
    bool operator<(const Bar& o) const {
        return height < o.height;
    }
    bool operator>(const Bar& o) const {
        return height > o.height;
    }
};

void drawBars(const vector<Bar>& arr)
{
    terminal_clear();
    terminal_print(1, 1, "Algorithms: 1) insertion sort, 2) selection sort, 3) quicksort");
    terminal_print(1, 2, "            4) mergesort(REC), 5) mergesort(ITR)");
    terminal_print(1, 3, "PRESS: <SPACE> for new array, <TAB> to toggle style");
    for (int x = 0; x < arr.size(); x++)
    {
        terminal_bkcolor(color_from_name(arr[x].color.c_str()));
        if (style == BARS)
        {
            for (int y = 38; y > 38 - arr[x].height; y--)
                terminal_put(x, y, ' ');
        } else {
            terminal_put(x, 38 - arr[x].height, ' ');
        }
        terminal_bkcolor(color_from_name("black"));
    }
    terminal_refresh();
}

void exch(vector<Bar>& arr, int l, int r)
{
    if (l > -1 && r > -1)
    {
        Bar tmp = arr[l];
        arr[l] = arr[r];
        arr[r] = tmp;
    }
    drawBars(arr);
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(50));
}

void selsort(vector<Bar>& a, int l, int r)
{
    for (int i = l; i < r; i++)
    {
        int lo = i;
        for (int j = i; j < r; j++)
        {
            if (a[j] < a[lo])
                lo = j;
        }
        exch(a, lo, i);
    }
}

void inssort(vector<Bar>& a, int l, int r)
{
    for (int i = l; i <= r; i++)
    {
        int j = i; Bar v = a[i];
        while (j > l && a[j-1] > v)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = v;
        exch(a, -1, -1);
    }
}

int findPivot(vector<Bar>& a, int l, int r)
{
    //random pivot selection
    return rand() % (r - l + 1) + l;
}

void quicksort(vector<Bar>& a, int l, int r)
{
    if (r > l) {
        int pivot = findPivot(a, l, r);
        exch(a, pivot, r);
        int i = l - 1;
        int j = r;
        Bar v = a[r];
        for (;;) {
            while (a[++i] < v);
            while (a[--j] > v) if (j == l) break;
            if (i >= j) break;
            exch(a, i, j);
        }
        exch(a, i, r);
        quicksort(a, l, i - 1);
        quicksort(a, i + 1, r);
    }
}

void mergesort(vector<Bar>& a, int l, int r)
{
    if (r - l <= 1)
        return;
    int m = (l + r) / 2;
    mergesort(a, l, m);
    mergesort(a, m, r);
    vector<Bar> tmp(a);
    int i = l, j = m, k = l;
    while (i < m && j < r)
    {
        tmp[k++] = (a[i] < a[j]) ? a[i++]:a[j++];
    }
    while (i < m) 
    {
        tmp[k++] = a[i++];
    }
    while (j < r)
    { 
        tmp[k++] = a[j++];
    }
    for (k = l; k < r; k++)
    {
        a[k] = tmp[k];
        drawBars(a);
    }
}

void mergesortITR(vector<Bar>& a)
{
    int l,m,r,p,q,k;
    vector<Bar> tmp(a);
    for (int i = 1; i < a.size(); i *= 2)
    {
        for (int j = 0; j < a.size(); j += 2*i)
        {
            m = min(a.size(), j + i);
            r = min(a.size(), j + 2* i);
            l = j; p = l; q = m; k = l;
            while (p < m && q < r)
            {
                tmp[k++] = (a[p] < a[q]) ? a[p++]:a[q++];
            }
            while (p < m) 
            {
                tmp[k++] = a[p++];
            }
            while (q < r) 
            {
                tmp[k++] = a[q++];
            }
            for (k = l; k < r; k++)
            {
                a[k] = tmp[k];
                drawBars(a);
            }   
        }
    }
}

vector<Bar> randVec(int n, int lo, int hi)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(lo, hi);
    vector<Bar> ret;
    for (int i = 0; i < n; i++)
    {
        ret.push_back(Bar(i, dist(gen)));
    }
    return ret;
}


void main_loop(int n, int lo, int hi)
{
    vector<Bar> to_sort(randVec(n, lo, hi));
    for (;;) {
        if (terminal_has_input())
        {
            char k = terminal_read();
            if (k == TK_Q)
                break;
            if (k == TK_SPACE)
            {
                to_sort = randVec(n, lo, hi);
            }
            if (k == TK_1)
                inssort(to_sort, 0, to_sort.size() - 1);
            
            if (k == TK_2)
                selsort(to_sort, 0, to_sort.size());
            
            if (k == TK_3)
                quicksort(to_sort, 0, to_sort.size() - 1);
            if (k == TK_4)
                mergesort(to_sort, 0, to_sort.size());
            if (k == TK_5)
                mergesortITR(to_sort);
            if (k == TK_TAB)
            {
                style = !style;
                drawBars(to_sort);
            }
        }
        terminal_clear();
        drawBars(to_sort);
        terminal_refresh();
    }
}

int main()
{
    terminal_open();
    terminal_set("window: size=80x40");
    terminal_refresh();
    main_loop(80, 2, 35);
    terminal_close();
    return 0;
}