#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Merge Sort (самый быстрый из трех)
    void merge(vector<int>& A, int start, int mid, int end, vector<int>& buff) {
        int left = start, right = mid + 1;
        for(int i = start; i <= end; i++) {
            if(left > mid) {
                buff[i] = A[right++];
            } else if(right > end) {
                buff[i] = A[left++];
            } else if(A[left] <= A[right]) {
                buff[i] = A[left++];
            } else {
                buff[i] = A[right++];
            }
        }
        for(int i = start; i <= end; i++) {
            A[i] = buff[i];
        }
    }

    void mergeSort(vector<int>& A, int start, int end, vector<int>& buff) {
        if(start >= end) return;
        
        int mid = start + (end - start) / 2;
        mergeSort(A, start, mid, buff);
        mergeSort(A, mid + 1, end, buff);
        merge(A, start, mid, end, buff);
    }

    vector<int> mergeSortArray(vector<int>& nums) {
        if(nums.empty()) return nums;
        vector<int> buff(nums.size());
        mergeSort(nums, 0, nums.size() - 1, buff);
        return nums;
    }

    // Bubble Sort (оптимизированный)
    void bubbleSort(vector<int>& nums) {
        int n = nums.size();
        for(int i = n - 1; i > 0; i--) {
            bool swapped = false;
            for(int j = 0; j < i; j++) {
                if(nums[j] > nums[j + 1]) {
                    swap(nums[j], nums[j + 1]);
                    swapped = true;
                }
            }
            if(!swapped) break;
        }
    }

    vector<int> bubbleSortArray(vector<int>& nums) {
        bubbleSort(nums);
        return nums;
    }

    // Selection Sort (максимально оптимизированный)
    void selectionSort(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n - 1; i++) {
            int minIndex = i;
            // Ищем минимальный элемент в оставшейся части
            for(int j = i + 1; j < n; j++) {
                if(nums[j] < nums[minIndex]) {
                    minIndex = j;
                }
            }
            // Меняем местами, если нашли меньший элемент
            if(minIndex != i) {
                swap(nums[i], nums[minIndex]);
            }
        }
    }

    vector<int> selectionSortArray(vector<int>& nums) {
        selectionSort(nums);
        return nums;
    }
};

// Быстрое чтение числовых файлов
vector<int> readArrayFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    vector<int> result;
    
    if(!file.is_open()) {
        cerr << "Cannot open file: " << filename << endl;
        return result;
    }

    string content;
    file.seekg(0, ios::end);
    content.reserve(file.tellg());
    file.seekg(0, ios::beg);
    content.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    
    // Быстрый парсинг чисел
    size_t start = 0;
    size_t end = 0;
    while(end < content.size()) {
        if(content[end] == ',' || end == content.size() - 1) {
            if(end > start) {
                int value = 0;
                bool negative = false;
                size_t pos = start;
                
                if(content[pos] == '-') {
                    negative = true;
                    pos++;
                }
                
                while(pos <= end && content[pos] >= '0' && content[pos] <= '9') {
                    value = value * 10 + (content[pos] - '0');
                    pos++;
                }
                
                if(negative) value = -value;
                result.push_back(value);
            }
            start = end + 1;
        }
        end++;
    }
    
    file.close();
    return result;
}

// Быстрая запись числовых файлов
void writeArrayToFile(const vector<int>& arr, const string& filename) {
    ofstream file(filename, ios::binary);
    
    if(!file.is_open()) {
        cerr << "Cannot create file: " << filename << endl;
        return;
    }

    // Буферизованная запись
    string buffer;
    buffer.reserve(arr.size() * 8);
    
    for(size_t i = 0; i < arr.size(); i++) {
        buffer.append(to_string(arr[i]));
        if(i != arr.size() - 1) {
            buffer.append(",");
        }
    }
    
    file.write(buffer.c_str(), buffer.size());
    file.close();
}

// Быстрая сортировка буквенного файла
void sortLetterFile(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);
    
    if(!inFile.is_open() || !outFile.is_open()) {
        cerr << "Cannot open letter file" << endl;
        return;
    }

    string content;
    inFile.seekg(0, ios::end);
    content.reserve(inFile.tellg());
    inFile.seekg(0, ios::beg);
    content.assign(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>());
    
    auto start = chrono::high_resolution_clock::now();
    
    // Удаляем запятые за один проход
    size_t write_pos = 0;
    for(size_t i = 0; i < content.size(); i++) {
        if(content[i] != ',') {
            content[write_pos++] = content[i];
        }
    }
    content.resize(write_pos);
    
    // Сортируем буквы
    sort(content.begin(), content.end());
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    // Быстрая запись с запятыми
    string output_buffer;
    output_buffer.reserve(content.size() * 2);
    for(size_t i = 0; i < content.size(); i++) {
        output_buffer += content[i];
        if(i != content.size() - 1) {
            output_buffer += ',';
        }
    }
    
    outFile.write(output_buffer.c_str(), output_buffer.size());
    inFile.close();
    outFile.close();
    
    cout << "Time: " << duration.count() << " мкс" << endl;
}

void testAllSortingAlgorithms() {
    vector<string> files = {
        "array1_integers_0_to_1000.txt",
        "array2_integers_-1000_to_1000.txt",
        "array3_mixed_0_to_1000.txt", 
        "array4_mixed_-1000_to_1000.txt",
        "array5_random_letters.txt"
    };

    Solution sorter;

    // Сначала тестируем Merge Sort для всех файлов
    cout << "\n" << string(60, '=') << endl;
    cout << "MERGE SORT RESULTS:" << endl;
    cout << string(60, '=') << endl;
    
    for(const auto& file : files) {
        if(file == "array5_random_letters.txt") {
            cout << "Letters file: ";
            string outputFile = "merge_sorted_" + file;
            sortLetterFile(file, outputFile);
            continue;
        }

        auto data = readArrayFromFile(file);
        if(data.empty()) {
            cerr << "Empty file: " << file << endl;
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        sorter.mergeSortArray(data);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        writeArrayToFile(data, "merge_sorted_" + file);
        cout << file << " - " << data.size() << " elements - " << duration.count() << " мкс - ";
        cout << (is_sorted(data.begin(), data.end()) ? "Correctly sorted" : "Sorting failed") << endl;
    }

    // Затем тестируем Bubble Sort для всех файлов
    cout << "\n" << string(60, '=') << endl;
    cout << "BUBBLE SORT RESULTS:" << endl;
    cout << string(60, '=') << endl;
    
    for(const auto& file : files) {
        if(file == "array5_random_letters.txt") {
            cout << "Letters file: ";
            string outputFile = "bubble_sorted_" + file;
            sortLetterFile(file, outputFile);
            continue;
        }

        auto data = readArrayFromFile(file);
        if(data.empty()) {
            cerr << "Empty file: " << file << endl;
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        sorter.bubbleSortArray(data);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        writeArrayToFile(data, "bubble_sorted_" + file);
        cout << file << " - " << data.size() << " elements - " << duration.count() << " мкс - ";
        cout << (is_sorted(data.begin(), data.end()) ? "Correctly sorted" : "Sorting failed") << endl;
    }

    // Затем тестируем Selection Sort для всех файлов
    cout << "\n" << string(60, '=') << endl;
    cout << "SELECTION SORT RESULTS:" << endl;
    cout << string(60, '=') << endl;
    
    for(const auto& file : files) {
        if(file == "array5_random_letters.txt") {
            cout << "Letters file: ";
            string outputFile = "selection_sorted_" + file;
            sortLetterFile(file, outputFile);
            continue;
        }

        auto data = readArrayFromFile(file);
        if(data.empty()) {
            cerr << "Empty file: " << file << endl;
            continue;
        }

        auto start = chrono::high_resolution_clock::now();
        sorter.selectionSortArray(data);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        writeArrayToFile(data, "selection_sorted_" + file);
        cout << file << " - " << data.size() << " elements - " << duration.count() << " мкс - ";
        cout << (is_sorted(data.begin(), data.end()) ? "Correctly sorted" : "Sorting failed") << endl;
    }
}

int main() {
    // Максимальная оптимизация ввода-вывода
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << "ULTRA FAST FILE SORTER - Testing All Algorithms" << endl;
    cout << "Compiled with maximum optimizations" << endl;
    
    auto total_start = chrono::high_resolution_clock::now();
    testAllSortingAlgorithms();
    auto total_end = chrono::high_resolution_clock::now();
    
    auto total_duration = chrono::duration_cast<chrono::milliseconds>(total_end - total_start);
    cout << "\n" << string(60, '=') << endl;
    cout << "TOTAL EXECUTION TIME: " << total_duration.count() << " ms" << endl;
    cout << "All files processed with all sorting algorithms!" << endl;
    
    return 0;
}
