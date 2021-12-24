import java.util.Random;

class Quicksort {
	Random rng;
	void swap(int[] arr, int l, int r)
	{
		int temp = arr[l];
		arr[l] = arr[r];
		arr[r] = temp;
	}
	
	void insertionsort(int[] arr, int l, int r)
	{
		for (int i = l; i <= r; i++)
		{
			int j = i, v = arr[i];
			while (j > l && arr[j- 1] > v)
			{
				arr[j] = arr[j-1];
				j--;
			}
			arr[j] = v;
		}
	}

	int medianof3(int[] arr, int l, int r)
	{
		int mid = (l+r) / 2;
		if (arr[l] > arr[mid])
		  swap(arr, l, mid);

		if (arr[l] > arr[r])
		  swap(arr, l, r);

		if (arr[mid] > arr[r])
		  swap(arr, mid, r);
		swap(arr, mid, r);
		return partition(arr, l, r);
	}

	int randompivot(int arr[], int l, int r)
	{
		int pivot = rng.nextInt(r - l + 1) + l;
		swap(arr, r, pivot);
		return partition(arr, l, r);
	}

	int partition(int[] arr, int l, int r)
	{
		int i = l - 1;
		int j = r;
		int v = arr[r];
		for (;;)
		{
			while (arr[++i] < v);
			while (v < arr[--j]);
			if (i >= j) break;
			this.swap(arr, j, i);
		}
		this.swap(arr, i, r);
		return i;
	}

	void quicksort(int[] arr, int l, int r)
	{
		if (r - l <= 1) return;
		if (r - l < 12)
		{
			insertionsort(arr, l, r);
			return;
		} else {
			int i = medianof3(arr, l, r);
			quicksort(arr, l, i - 1);
			quicksort(arr, i + 1, r);
		}
	}

	void printArray(int[] arr)
	{
		for (int n : arr)
		{
			System.out.print(n + " ");
		}
		System.out.println();
	}
	Quicksort()
	{
		rng = new Random();
	}
    public static void main(String[] args)
    {
		Quicksort qs = new Quicksort();
        int[] arr = new int[20];
        for (int i = 0; i < arr.length; i++)
           arr[i] = qs.rng.nextInt(25);
		qs.printArray(arr);
		qs.quicksort(arr, 0, arr.length-1);
		qs.printArray(arr);
    }
}