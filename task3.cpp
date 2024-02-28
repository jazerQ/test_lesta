#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

//для проведения эксперимента было выбрано 3 способа сортировки : counting_sort, timsort, quick_sort
//на маленьких значениях элементов массива непревзойденным лидером остается counting_sort
//при увеличении значения элемента вперед выходит quick_sort
//timsort при заявленных в лучшем времени O(n) и худшем O(n log(n)) показывает худший результат из трех
//
const int MIN_MERGE = 32;


 void countingSort(std::vector<int>& array) {
    int max = *std::max_element(array.begin(), array.end());
    auto count = std::vector<int>(max+1, int(0));

    for (int i = 0; i < array.size(); i++)
        ++count[array[i]];

    int b = 0;
    for (size_t i = 0; i < max+1; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            array[b++] = i;
        }
    }
}

int minRunLength(int n) {
    int r = 0;
    while (n >= MIN_MERGE) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}

void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    std::vector<int> left(len1), right(len2);
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
}


//сортировка тимсорт которая сортирует слиянием и вставками О(n log(n))
void timsort(std::vector<int>& arr) {
    int n = arr.size();
    int minRun = minRunLength(n);

    for (int i = 0; i < n; i += minRun)
        insertionSort(arr, i, std::min(i + minRun - 1, n - 1));

    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}



//алгоритм быстрой сортировки
void sort_quick(vector<int> &array, int size) {
    int left = 0;
    int right = size - 1;
    int pivot = array[size / 2];
    do {
        while (array[left] < pivot) {
            left++;
        }
        while (array[right] > pivot) {
            right--;
        }
        if (left <= right) {
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            left++;
            right--;
        }
    } while (left <= right);
    if (right >= 0) {
        sort_quick(array, right + 1);
    }
    if (left < size - 1) {
        sort_quick(array, size - left);
    }
}



vector<int> getArrayWithRandomNumbers(int size){
    vector<int> arr = {};
    for(int i = 0; i<size;i++){
        arr.push_back(rand()%3200000);
    }
    return arr;
}

int main() {
    vector<int> arr = getArrayWithRandomNumbers(10000);
    vector<int> arr1(arr);
    vector<int> arr2(arr);

    auto start = high_resolution_clock::now();
    countingSort(arr2);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);


    cout << "\nTime taken by counting_sort: " << duration.count() << " microseconds" << endl;

    start = high_resolution_clock::now();
    sort_quick(arr1, arr1.size());
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);


    cout << "\nTime taken by quicksort: " << duration.count() << " microseconds" << endl;




    start = high_resolution_clock::now();
    timsort(arr);
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);


    cout << "\nTime taken by timsort: " << duration.count() << " microseconds" << endl;

    return 0;
}

