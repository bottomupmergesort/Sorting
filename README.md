# Sorting
Out-sorting the standard library

# So what's this all about?
When i first started digging into sorting algorithms, like so many other people i was amazed at the difference
between say, an shellsort and heapsort. Soon i learned all about algorithmic complexity and the big-O.

I devoured the literature, implementing insertion sort, heap sort, selection sort, quicksort, mergesort, shakersort, etc, etc.
and through it all there was a benchmark to which i rated my implementations: C++'s std::sort.

the C++ Standrd Library uses The introsort algorithm invented by david musser specfically for the standard library.
prior to circa the year 2000 the standard sort function in C++ was based on quicksort, and introsort in its self is an outgrowth
of quicksort, with all the bells and whistles you can expect from a tuned imlpementation:

-median of three partitioning
-insertion sort on small sublists

but musser came up with another twist that *guranteed* that quicksort would not devolve to its On^2 worst case:
if the recursion depth exceeds 2logn, intosort falls back to heapsort.

In my implementation of introsort i follow these rules as well, but instead of dropping to insertionsort everytime the partition being quicksorted
falls below threshold, i simply, skip this partition, and move on to the next one, and at the end do one insertionsort run on the entire *mostly* sorted
array. The results speak:

    Items      Introsort        std::sort       Mergesort/O     std::stable_sort
     25:        0.017707        0.003194        0.018559        0.005878
    250:        0.010228        0.010247        0.013128        0.018024
   2500:        0.121456        0.110576        0.153355        0.12855
  25000:        1.60394         1.62623         1.75316         2.09809
 250000:        16.6695         16.3898         19.2324         17.1437
 
 At 2 and a half million items, my implementation is .3ms behind std::sort, at two hundred and fifty thousand items, its its dead even.
 
 std::stable_sort is The C++ standard library implementation of mergesort. For my implementation of mergesort, i actually did very little tweaking.
 its a standard recursive top down apprach, but borrowing a page from quicksort, i insertion sort small partitions.
 
 The above table is a single run, chosen at random. If i were to average the runs, my insertion sort vs. std::sort, and my optimized mergesort vs std::stable_sort, there is no "by a mile" winner, which until quite recently i was unable to conquer std::sort or std::stable_sort at all. with a little more tuning im confident i will be able to hands down out sort both, every time.
 
 
