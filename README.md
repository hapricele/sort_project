# Sorting Algorithms Project

## Overview
This is a collaborative project by students of group AA-24-08 that implements and compares three fundamental sorting algorithms: **Bubble Sort**, **Selection Sort**, and **Merge Sort**. The project tests these algorithms on different types of datasets and measures their performance.

## Algorithms Implemented

### 1. Bubble Sort
- **Time Complexity**: O(n²) worst/average case, O(n) best case
- **Space Complexity**: O(1)
- **Description**: Compares adjacent elements and swaps them if they're in the wrong order. Repeats until the array is sorted.
- **Best for**: Educational purposes, small datasets

### 2. Selection Sort
- **Time Complexity**: O(n²) in all cases
- **Space Complexity**: O(1)
- **Description**: Finds the minimum element and places it at the beginning. Repeats for remaining unsorted portion.
- **Best for**: Small to medium datasets, minimal memory usage

### 3. Merge Sort
- **Time Complexity**: O(n log n) in all cases
- **Space Complexity**: O(n)
- **Description**: Divide-and-conquer approach. Divides array into halves, recursively sorts them, then merges the sorted halves.
- **Best for**: Large datasets, guaranteed O(n log n) performance

## Project Structure

```
sort_project/
├── sortingproject.cpp          # Main C++ program
├── array1_integers_0_to_1000.txt       # Test dataset 1: integers 0-1000
├── array2_integers_-1000_to_1000.txt   # Test dataset 2: integers -1000 to 1000
├── array3_mixed_0_to_1000.txt          # Test dataset 3: mixed float/int 0-1000
├── array4_mixed_-1000_to_1000.txt      # Test dataset 4: mixed float/int -1000 to 1000
└── README.md                    # This file
```

## How to Compile and Run

### Prerequisites
- C++ compiler (g++, clang, or MSVC)
- Standard C++ library

### Compilation
```bash
g++ -o sortingproject sortingproject.cpp
```

### Execution
```bash
./sortingproject
```

The program will automatically test all three algorithms on all four datasets and display:
- Number of elements in each dataset
- First 10 elements of the dataset
- Execution time for each algorithm (in ms or μs)
- Verification that the sorted result is correct

## Features

- **Multiple Data Structures**: Works with both `std::list` and `std::forward_list`
- **Performance Measurement**: Uses high-resolution clock to measure execution time
- **Data Validation**: Includes functions to verify that arrays are correctly sorted
- **Flexible Input**: Parses CSV-formatted data files with both integer and floating-point values
- **Comprehensive Testing**: Tests on four different datasets with varying characteristics

## Team Members
- Малышева (Malysheva)
- Грицкевича (Gritskvich)
- Озерова (Ozerova)
- Зернина (Zernina)

## Data Files

### Dataset Characteristics

1. **array1_integers_0_to_1000.txt**
   - Type: Positive integers
   - Range: 0-1000
   - Properties: Pre-generated random integers

2. **array2_integers_-1000_to_1000.txt**
   - Type: Integers
   - Range: -1000 to 1000
   - Properties: Both positive and negative values

3. **array3_mixed_0_to_1000.txt**
   - Type: Mixed integers and floating-point numbers
   - Range: 0-1000
   - Properties: Realistic data with decimals

4. **array4_mixed_-1000_to_1000.txt**
   - Type: Mixed integers and floating-point numbers
   - Range: -1000 to 1000
   - Properties: Both positive/negative and decimal values

## Performance Analysis

The program outputs execution times for each algorithm on each dataset, allowing for empirical comparison:

- **Bubble Sort**: Slowest on large datasets, good for demonstration
- **Selection Sort**: Middle ground, consistent O(n²) performance
- **Merge Sort**: Fastest on large datasets, optimal for production use

## Code Organization

- **Input Functions**: `readListFromFile()`, `readForwardListFromFile()`
- **Sorting Functions**: `bubbleSortList()`, `selectionSortList()`, `mergeSortFL()`
- **Utility Functions**: `printFirst()`, `isSortedList()`, `isSortedFL()`
- **Main Test Function**: `testFile()`

## Notes

- The program converts floating-point numbers to integers by truncating decimal places
- Times are displayed in milliseconds (ms) for Bubble Sort and microseconds (μs) for other algorithms
- All algorithms maintain stable sorting for identical elements within their constraints

## Future Improvements

- Implement additional sorting algorithms (QuickSort, HeapSort)
- Add command-line argument support for custom test files
- Create visualization of sorting process
- Implement parallel sorting for multi-threaded comparison

## License

This is an educational project created for learning purposes.
