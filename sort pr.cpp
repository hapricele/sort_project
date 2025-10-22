#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        int minIdx = i;
        for (int j = i+1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid+1, right);
    merge(arr, left, mid, right);
}

void mergeSort(std::vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size()-1);
}

int main() {
    const int SIZE = 10000;
    std::vector<int> original(SIZE);
    
    srand(time(0));
    for (int i = 0; i < SIZE; ++i) {
        original[i] = rand() % 10000;
    }

    std::cout << "Original array (first 10): ";
    for (int i = 0; i < 10; ++i) {
        std::cout << original[i] << " ";
    }
    std::cout << "\n\n";

    std::vector<int> arr;

    // Bubble Sort
    arr = original;
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Bubble Sort (first 10): ";
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\nTime: " << elapsed.count() << " seconds\n\n";

    // Selection Sort
    arr = original;
    start = std::chrono::high_resolution_clock::now();
    selectionSort(arr);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Selection Sort (first 10): ";
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\nTime: " << elapsed.count() << " seconds\n\n";

    // Merge Sort
    arr = original;
    start = std::chrono::high_resolution_clock::now();
    mergeSort(arr);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Merge Sort (first 10): ";
    for (int i = 0; i < 10; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\nTime: " << elapsed.count() << " seconds\n\n";

    return 0;
}
