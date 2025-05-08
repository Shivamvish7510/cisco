#include <iostream>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding random numbers
#include <fstream> // For writing data to file

using namespace std;

// Global comparison counters
long long insertionComparisons = 0;
long long mergeComparisons = 0;
long long heapComparisons = 0;
long long quickComparisons = 0;

// Insertion Sort
void insertionSort(int arr[], int n) {
    insertionComparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            insertionComparisons++;
            arr[j + 1] = arr[j];
            j--;
        }
        insertionComparisons++; // For last unsuccessful comparison
        arr[j + 1] = key;
    }
}

// Merge Sort
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
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        quickComparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Generate random array
int* generateArray(int size) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) arr[i] = rand() % 10000;
    return arr;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Main function
int main() {
    srand(time(0));
    ofstream file("sorting_results.csv");
    file << "Size,Insertion,Merge,Heap,Quick\n";

    for (int size = 30; size <= 1000; size += 10) {
        long long insTotal = 0, mergeTotal = 0, heapTotal = 0, quickTotal = 0;

        for (int i = 0; i < 10; i++) {
            int* arr1 = generateArray(size);
            int* arr2 = new int[size];
            int* arr3 = new int[size];
            int* arr4 = new int[size];

            for (int j = 0; j < size; j++) {
                arr2[j] = arr1[j];
                arr3[j] = arr1[j];
                arr4[j] = arr1[j];
            }


            insertionSort(arr1, size);
            mergeComparisons = 0; mergeSort(arr2, 0, size - 1);
            heapSort(arr3, size);
            quickComparisons = 0; quickSort(arr4, 0, size - 1);

            insTotal += insertionComparisons;
            mergeTotal += mergeComparisons;
            heapTotal += heapComparisons;
            quickTotal += quickComparisons;

            delete[] arr1;
            delete[] arr2;
            delete[] arr3;
            delete[] arr4;
        }

        file << size << "," << insTotal / 10 << "," << mergeTotal / 10 << "," << heapTotal / 10 << "," << quickTotal / 10 << "\n";
        cout << "Size: " << size << " done.\n";
       
    }

    file.close();
    return 0;
}