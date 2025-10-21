
<<<<<<< HEAD
class Solution {
private:
    // Bubble Sort
    void bubbleSort(vector<int> &nums) {
        int endInd, currInd, size = nums.size();
        if (size <= 1) return;
        for (endInd = size - 1; endInd; endInd--)
            for (currInd = 0; currInd < endInd; currInd++)
                if (nums[currInd] > nums[currInd + 1])
                    swap(nums[currInd], nums[currInd + 1]);
    }

    // Selection Sort 1
    void selectionSort(vector<int> &nums) {
        int minInd, startInd, currInd, size = nums.size();
        if (size <= 1) return;
        for (startInd = 0; startInd < size - 1; startInd++) {
            for (currInd = startInd + 1, minInd = startInd; currInd < size; currInd++)
                if (nums[minInd] > nums[currInd])
                    minInd = currInd;
            if (minInd != startInd)
                swap(nums[startInd], nums[minInd]);
        }
    }

    // Merge Sort helpers vers 1
    void outPlaceMerge(vector<int> &nums, int low, int mid, int high) {
        if (low >= high) return;
        int l = low, r = mid + 1, k = 0, size = high - low + 1;
        vector<int> sorted(size, 0);
        while (l <= mid and r <= high)
            sorted[k++] = nums[l] < nums[r] ? nums[l++] : nums[r++];
        while (l <= mid) 
            sorted[k++] = nums[l++];
        while (r <= high) 
            sorted[k++] = nums[r++];
        for (k = 0; k < size; k++)
            nums[k + low] = sorted[k];
    }

    void mergeSort(vector<int> &nums, int low, int high) {
        if (low >= high) return;
        int mid = (high - low) / 2 + low;
        mergeSort(nums, low, mid);
        mergeSort(nums, mid + 1, high);
        outPlaceMerge(nums, low, mid, high);
    }

    void mergeSort(vector<int> &nums) {
        mergeSort(nums, 0, nums.size() - 1);
    }

public:
    // Основная функция для тестирования всех алгоритмов1 211312321
    void testAllSorts(vector<int>& nums) {
        vector<int> original = nums;
        
        cout << "Original array (first 10): ";
        for (int i = 0; i < min(10, (int)original.size()); i++) {
            cout << original[i] << " ";
        }
        if (original.size() > 10) cout << "...";
        cout << endl;

        testSort("Bubble Sort", [this](vector<int>& arr) { bubbleSort(arr); }, original);
        testSort("Selection Sort", [this](vector<int>& arr) { selectionSort(arr); }, original);
        testSort("Merge Sort", [this](vector<int>& arr) { mergeSort(arr); }, original);
        testSort("std::sort", [](vector<int>& arr) { sort(arr.begin(), arr.end()); }, original);
    }

private:
    void testSort(const string& name, function<void(vector<int>&)> sortFunc, vector<int>& nums) {
        vector<int> copy = nums;
        auto start = high_resolution_clock::now();
        sortFunc(copy);
        auto end = high_resolution_clock::now();
        
        auto duration = duration_cast<microseconds>(end - start);
        bool isSorted = true;
        for (int i = 1; i < copy.size(); i++) {
            if (copy[i] < copy[i-1]) {
                isSorted = false;
                break;
            }
        }
        
        cout << name << ": " << duration.count() << " μs, Sorted: " 
             << (isSorted ? "Yes" : "No") << endl;
    }

public:
    vector<int> generateTestData(int size, const string& type) {
        vector<int> data(size);
        random_device rd;
        mt19937 gen(rd());
        
        if (type == "random") {
            uniform_int_distribution<> dis(1, 10000);
            for (int i = 0; i < size; i++) data[i] = dis(gen);
        } 
        else if (type == "sorted") {
            for (int i = 0; i < size; i++) data[i] = i;
        }
        else if (type == "reversed") {
            for (int i = 0; i < size; i++) data[i] = size - i;
        }
        
        return data;
    }

    void comprehensiveTest() {
        cout << "=== COMPREHENSIVE SORTING TEST ===" << endl << endl;
        
        vector<int> testData = generateTestData(1000, "random");
        testAllSorts(testData);
    }

    vector<int> sortArray(vector<int>& nums) {
        vector<int> result = nums;
        mergeSort(result);
        return result;
    }
};

int main() {
    Solution solution;
    solution.comprehensiveTest();
    
    // Простой тест
    vector<int> simpleTest = {5, 2, 8, 1, 9, 3};
    cout << endl << "=== SIMPLE TEST ===" << endl;
    solution.testAllSorts(simpleTest);
    
    return 0;
}
=======
>>>>>>> 2eeb225d9ce0b9bccba5ee3181a2007a098938e1
