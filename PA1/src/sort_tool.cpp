// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<vector>
#include<random>
#define ll long long 
// Constructor
int heap_size;
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int size = data.size();
    for(int i = 1; i < size; i++){
        int temp = data[i];
        int j = i - 1;
        while (temp < data[j] && j != -1)
        {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = temp;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if(flag == 0)
    {
        if(low < high)
        {
            int q = Partition(data, low, high);
            QuickSortSubVector(data, low, q - 1, 0);
            QuickSortSubVector(data, q + 1, high, 0);
        }
    }
    else
    {
        if(low < high)
        { 
            int q = RandomizedPartition(data, low, high);
            QuickSortSubVector(data, low, q - 1, 1);
            QuickSortSubVector(data, q + 1, high, 1);
        }
    }
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    
    random_device rd;
    mt19937 generator(rd());

    // Define the range of random numbers
    int lowerBound = low;
    int upperBound = high;

    // Create a uniform distribution for integers in the specified range
    uniform_int_distribution<int> distribution(lowerBound, upperBound);

    // Generate a random number
    int randomNumber = distribution(generator);

    swap(data[randomNumber], data[high]);

    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    int x = data[high];
    int div = low - 1;

    for (int i = low; i < high; i++) {
        if (data[i] <= x) {
            div = div + 1;
            swap(data[i], data[div]);
        }
    }

    swap(data[div + 1], data[high]);

    return div + 1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is neededif(begin < end)
    if(low < high)
    {
        int mid;
        mid = (low + high)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid + 1, high);
        Merge(data, low, mid, 0, high);
    }
}

//  Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    ll int n_1 = middle1 - low + 1;
    ll int n_2 = high - middle1;
    //int size = high - low + 1;

    vector<int> L(n_1 + 1);
    vector<int> R(n_2 + 1);

    L[n_1] = 100000000;
    R[n_2] = 100000000;

    for (int i = 0; i < n_1; i++) {
        L[i] = data[low + i];
    }

    for (int i = 0; i < n_2; i++) {
        R[i] = data[middle1 + i + 1];
    }

    int l = 0, r = 0;
    for (int i = low; i <= high; i++) {
        if (L[l] <= R[r]) {
            data[i] = L[l];
            l++;
        } else {
            data[i] = R[r];
            r++;
        }
    }
}



// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    heapSize = data.size();
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    // cout << "Max : ";
    // display(a);
    // cout << "In for loop : \n";
    for (int i = (data.size()) - 1; i >= 1; i--)
    {
        //cout << "** I = " << i << endl;
        swap(data[0], data[i]);
        //cout << "largest = " << a[i] << ", \n";
        heapSize -= 1;
        MaxHeapify(data, 0); 
        // cout << "Max : ";
        // display(a);
        // cout << endl;
    }
    
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2*root + 1;
    int r = 2*root + 2;
    int largest;
    if (l < heapSize && data[l] > data[root])
    {
        largest = l;
    }
    else
    {
        largest = root;
    }
    if (r < heapSize && data[r] > data[largest])
    {
        largest = r;
    }
    if (largest != root)
    {
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = heapSize / 2 - 1; i >= 0; i--)
    {
        MaxHeapify(data, i);
    }
}