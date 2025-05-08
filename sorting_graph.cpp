// name -- shivam vishwakarma
// roll no -- 23/49071
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

long long insertionComparisons = 0;
int mergeComparisons = 0;
int heapComparisons =0;
int quickComparsions = 0;

// Insertion Sort

void insertionSort(int arr[], int n)
{
    
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            insertionComparisons++;
            arr[j + 1] = arr[j];
            j--;
        }
        insertionComparisons++; // For last unsuccessful comparison
        arr[j + 1] = key;
    }
    // cout << "No of comparisons :" << insertionComparisons << endl;
}



// merge sort
void merge(int arr[], int left, int mid, int right) {
    int* L = new int[mid - left + 1];
    int* R = new int[right - mid];

    for (int i = 0; i < mid - left + 1; i++) L[i] = arr[left + i];
    for (int i = 0; i < right - mid; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < mid - left + 1 && j < right - mid) {
        mergeComparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < mid - left + 1) arr[k++] = L[i++];
    while (j < right - mid) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        heapComparisons++;
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        heapComparisons++;
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    heapComparisons = 0;

    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

    // cout << "Number of comparisons: " << heapComparisons << endl;
}



// Quick Sort

int partition(int arr[], int start , int end){
    int pivot = arr[end];
    int i = (start - 1);
    for(int  j =start; j<end;j++ ){
        quickComparsions++;
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
            }

    }
    swap(arr[i+1], arr[end]);
    return (i+1);
}
int quickSort(int arr[], int start, int end){
    if(start < end){

        int pivot = partition(arr, start, end);

        quickSort(arr,start,pivot-1); 
        quickSort(arr, pivot+1,end); 
    }


}

int *generateRandomArray(int size)
{
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    return arr;
}

// print array

void printArray(int arr[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
        count++;
    }
    cout << endl;
    cout << "number of element is " << count << endl;
    cout << endl;
    
}


int main()
{
    ofstream file("sorting_result.csv");
    file << "Size,Insertion,Merge,Heap,Quick\n";
    srand(time(0));
    for (int i = 0; i < 50; i++) {
        long long insTotal = 0, mergeTotal = 0, heapTotal = 0, quickTotal = 0;

        
        int size = rand() % (1000 - 30 + 1) + 30;
        // int size = 10;
        for (int i = 0; i < 10; i++)
        {
            int *arr = generateRandomArray(size);
    
            int *arr1 = new int[size];
            int *arr2 = new int[size];
            int *arr3 = new int[size];
            for (int i = 0; i < size; i++)
            {
                arr1[i] = arr[i];
                arr2[i] = arr[i];
                arr3[i] = arr[i];
            }
    

            insertionSort(arr, size);

            mergeSort(arr1, 0,size-1);

            heapSort(arr2, size);

            quickSort(arr3, 0, size - 1);
            
            insTotal += insertionComparisons;
            mergeTotal += mergeComparisons;
            heapTotal += heapComparisons;
            quickTotal += quickComparsions;
        }

        file << size << "," << insTotal / 10 << "," << mergeTotal / 10 << "," << heapTotal / 10 << "," << quickTotal / 10 << "\n";
        cout << "Size: " << size << " done.\n";
    
        
    }

    return 0;
}