#include <iostream>
#include <fstream>
#include <list>
#include <forward_list>
#include <string>
#include <chrono>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace chrono;

// ========================= Read Functions =========================

// Read integers from file into std::list
list<int> readListFromFile(const string filename) {
    ifstream in(filename);
    list<int> data;
    if (!in) return data;
    
    string line, number;
    while (getline(in, line)) {
        stringstream ss(line);
        while (getline(ss, number, ',')) {
            // Remove decimal points from numbers
            size_t dotPos = number.find('.');
            if (dotPos != string::npos) {
                number = number.substr(0, dotPos);
            }
            number.erase(remove(number.begin(), number.end(), ' '), number.end());
            try {
                data.push_back(stoi(number));
            } catch (...) {
                continue;
            }
        }
    }
    return data;
}

// Read integers from file into std::forward_list
forward_list<int> readForwardListFromFile(const string filename) {
    ifstream in(filename);
    forward_list<int> data;
    if (!in) return data;
    
    string line, number;
    auto it = data.before_begin();
    while (getline(in, line)) {
        stringstream ss(line);
        while (getline(ss, number, ',')) {
            // Remove decimal points from numbers
            size_t dotPos = number.find('.');
            if (dotPos != string::npos) {
                number = number.substr(0, dotPos);
            }
            number.erase(remove(number.begin(), number.end(), ' '), number.end());
            try {
                it = data.insert_after(it, stoi(number));
            } catch (...) {
                continue;
            }
        }
    }
    return data;
}

// ========================= Print Functions =========================

void printFirst(const list<int>& data, size_t n) {
    size_t cnt = 0;
    for (int x : data) {
        if (cnt >= n) break;
        cout << x << " ";
        cnt++;
    }
    if (data.size() > n) cout << "...";
    cout << endl;
}

// ========================= Validation Functions =========================

bool isSortedList(const list<int>& data) {
    if (data.empty()) return true;
    auto it = data.begin();
    auto next = it;
    next++;
    while (next != data.end()) {
        if (*next < *it) return false;
        it++;
        next++;
    }
    return true;
}

bool isSortedFL(const forward_list<int>& data) {
    if (data.empty()) return true;
    auto it = data.begin();
    auto next = it;
    next++;
    while (next != data.end()) {
        if (*next < *it) return false;
        it++;
        next++;
    }
    return true;
}

// ========================= Bubble Sort =========================

void bubbleSortList(list<int>& lst) {
    if (lst.empty()) return;
    bool swapped;
    auto last = lst.end();
    do {
        swapped = false;
        auto current = lst.begin();
        auto next = current;
        next++;
        while (next != last) {
            if (*next < *current) {
                swap(*current, *next);
                swapped = true;
            }
            current++;
            next++;
        }
        last = current;
    } while (swapped);
}

// ========================= Selection Sort =========================

void selectionSortList(list<int>& data) {
    auto pos = data.begin();
    while (pos != data.end()) {
        auto minPos = pos;
        auto checkPos = pos;
        checkPos++;
        while (checkPos != data.end()) {
            if (*checkPos < *minPos) {
                minPos = checkPos;
            }
            checkPos++;
        }
        if (minPos != pos) {
            int temp = *pos;
            *pos = *minPos;
            *minPos = temp;
        }
        pos++;
    }
}

// ========================= Merge Sort =========================

forward_list<int> mergeFL(forward_list<int> left, forward_list<int> right) {
    forward_list<int> result;
    auto itresult = result.before_begin();
    auto itleft = left.begin(), itright = right.begin();
    
    while (itleft != left.end() && itright != right.end()) {
        if (*itleft <= *itright) {
            itresult = result.insert_after(itresult, *itleft);
            itleft++;
        } else {
            itresult = result.insert_after(itresult, *itright);
            itright++;
        }
    }
    
    while (itleft != left.end()) {
        itresult = result.insert_after(itresult, *itleft);
        itleft++;
    }
    
    while (itright != right.end()) {
        itresult = result.insert_after(itresult, *itright);
        itright++;
    }
    
    return result;
}

forward_list<int> mergeSortFL(forward_list<int> list) {
    if (list.empty() || next(list.begin()) == list.end()) {
        return list;
    }
    
    auto slow = list.begin(), fast = next(list.begin());
    while (fast != list.end() && next(fast) != list.end()) {
        slow++;
        fast++;
        fast++;
    }
    
    forward_list<int> left, right;
    auto it = list.begin(), itleft = left.before_begin();
    while (it != next(slow)) {
        itleft = left.insert_after(itleft, *it);
        it++;
    }
    
    auto itright = right.before_begin();
    while (it != list.end()) {
        itright = right.insert_after(itright, *it);
        it++;
    }
    
    left = mergeSortFL(left);
    right = mergeSortFL(right);
    return mergeFL(left, right);
}

// ========================= Test Function =========================

void testFile(const string filename) {
    list<int> originalList = readListFromFile(filename);
    if (originalList.empty()) return;
    
    cout << "\n--- Testing file: " << filename << " ---" << endl;
    cout << "Total elements: " << originalList.size() << endl;
    cout << "First 10 elements: ";
    printFirst(originalList, 10);
    
    // Bubble Sort test
    cout << "\nBubble Sort: ";
    auto start = high_resolution_clock::now();
    list<int> bubbleData = originalList;
    bubbleSortList(bubbleData);
    auto end = high_resolution_clock::now();
    cout << "Time: " << duration_cast<milliseconds>(end - start).count() << " ms";
    cout << " | Is sorted: " << (isSortedList(bubbleData) ? "Yes" : "No") << endl;
    
    // Selection Sort test
    cout << "Selection Sort: ";
    start = high_resolution_clock::now();
    list<int> selData = originalList;
    selectionSortList(selData);
    end = high_resolution_clock::now();
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " us";
    cout << " | Is sorted: " << (isSortedList(selData) ? "Yes" : "No") << endl;
    
    // Merge Sort test
    cout << "Merge Sort: ";
    start = high_resolution_clock::now();
    forward_list<int> flData = readForwardListFromFile(filename);
    forward_list<int> sortedFL = mergeSortFL(flData);
    end = high_resolution_clock::now();
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << " us";
    cout << " | Is sorted: " << (isSortedFL(sortedFL) ? "Yes" : "No") << endl;
}

// ========================= Main Function =========================

int main() {
    cout << "====== Sorting Algorithms Test Program ======" << endl;
    
    testFile("array1_integers_0_to_1000.txt");
    testFile("array2_integers_-1000_to_1000.txt");
    testFile("array3_mixed_0_to_1000.txt");
    testFile("array4_mixed_-1000_to_1000.txt");
    
    cout << "\n====== Testing Complete ======" << endl;
    return 0;
}
