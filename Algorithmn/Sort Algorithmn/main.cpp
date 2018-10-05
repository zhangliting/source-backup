#include <iostream>
#include "SortTestHelper.h"
#include <cmath>

using namespace std;

/**
 * 每次选择最小的元素，放到相应的位置。
 * @param arr
 * @param n
 */
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        //寻找[i, n)区间里的最小值
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

/**
 * 插入排序，将当前元素插入到已经排好序的数组中
 * @tparam T
 * @param arr
 * @param n
 */
template<typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
            swap(arr[j], arr[j - 1]);
        }
    }
}

template<typename T>
void insertionSortBetter(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        T e = arr[i];
        int j;
        for (j = i; j > 0 && arr[j - 1] > e; j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = e;
    }
}

/**
 * 冒泡排序
 * @tparam T
 * @param arr
 * @param n
 */
template<typename T>
void bubbleSort(T arr[], int n) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
            //每一次循环都将最大的元素放到最后的位置
        }
        n--;
    } while (swapped);
}

/**
 * 希尔排序， 间隔h进行插入排序，当间隔等于1的时候，做一次插入排序就可以了
 * @tparam T
 * @param arr
 * @param n
 */
template<typename T>
void shellSort(T arr[], int n) {
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        //h-sort the array
        for (int i = h; i < n; i++) {
            //对arr[i], arr[i-h],arr[i-2*h], arr[i-3*h]...使用插入排序
            T e = arr[i];
            int j;
            for (j = i; j >= h && e < arr[j - h]; j -= h) {
                arr[j] = arr[j - h];
            }
            arr[j] = e;
        }
        h /= 3;
    }
}


/**
 * 将arr[l...mid]和arr[mid+1...r]的两个有序数组合并
 * @tparam T
 * @param arr
 * @param l
 * @param mid
 * @param r
 */
template<typename T>
void __merge(T arr[], int l, int mid, int r) {
    T aux[r - l + 1];
    for (int i = l; i <= r; i++) {
        aux[i - l] = arr[i];
    }
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = aux[j - l];
            j++;
        } else if (j > r) {
            arr[k] = aux[i - l];
            i++;
        } else if (aux[i - l] < aux[j - l]) {
            arr[k] = aux[i - l];
            i++;
        } else {
            arr[k] = aux[j - l];
            j++;
        }
    }
}

/**
 * 递归使用归并排序，对arr[L....R]的范围进行排序
 * @tparam T
 * @param arr
 * @param l
 * @param r
 */
template<typename T>
void __mergeSort(T arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    //如果两个集合已经有序，不需要Merge, 对近乎有序的数组非常有效。
    if (arr[mid] > arr[mid + 1]) {
        __merge(arr, l, mid, r);
    }
}

/**
 * 归并排序，递归
 * @tparam T
 * @param arr
 * @param n
 */
template<typename T>
void mergeSort(T arr[], int n) {
    __mergeSort(arr, 0, n - 1);
}

template<typename T>
void mergeSortBU(T arr[], int n) {
    for (int sz = 1; sz <= n; sz += sz) {
        for (int i = 0; i < n; i += sz + sz) {
            //对arr[i...i+sz-1]和arr[i+sz...i+sz-1]进行合并
            __merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
        }
    }
}

template<typename T>
int __partition(T arr[], int l, int r) {
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];
    int j = l;
    //arr[l+1...j] < v; arr[j+1...i] > v
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < v) {
            j++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

template<typename T>
int __partition2(T arr[], int l, int r) {
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];

    int i = l + 1, j = r;
    //将=v的分布在左边和右边
    while (true) {
        while (i <= r && arr[i] < v) {
            i++;
        }
        while (j >= l + 1 && arr[j] > v) {
            j--;
        }
        if (i > j) {
            break;
        }
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    swap(arr[l], arr[j]);
    return j;
}

template<typename T>
void __quickSort(T arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int p = __partition2(arr, l, r);
    __quickSort(arr, l, p - 1);
    __quickSort(arr, p + 1, r);
}

/**
 * 快速排序， 先随机去一个值，将小于该值得放在左边，大于该值得放在右边，递归直到只剩一个值得时候
 * @tparam T
 * @param arr
 * @param l
 * @param r
 */
template<typename T>
void quickSort(T arr[], int n) {
    srand(time(NULL));
    __quickSort(arr, 0, n - 1);
}

// 对arr[l...r]范围的数组进行插入排序
template<typename T>
void insertionSort(T arr[], int l, int r) {

    for (int i = l + 1; i <= r; i++) {

        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j - 1] > e; j--)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }

    return;
}

template<typename T>
void __quickSort3Ways(T arr[], int l, int r) {

    if (r - l <= 15) {
        insertionSort(arr, l, r);
        return;
    }

    swap(arr[l], arr[rand() % (r - l + 1) + l]);

    T v = arr[l];

    int lt = l;     // arr[l+1...lt] < v
    int gt = r + 1; // arr[gt...r] > v
    int i = l + 1;    // arr[lt+1...i) == v
    while (i < gt) {
        if (arr[i] < v) {
            swap(arr[i], arr[lt + 1]);
            i++;
            lt++;
        } else if (arr[i] > v) {
            swap(arr[i], arr[gt - 1]);
            gt--;
        } else { // arr[i] == v
            i++;
        }
    }

    swap(arr[l], arr[lt]);

    __quickSort3Ways(arr, l, lt - 1);
    __quickSort3Ways(arr, gt, r);
}

/**
 * 三路快排
 * @tparam T
 * @param arr
 * @param n
 */
template<typename T>
void quickSort3Ways(T arr[], int n) {

    srand(time(NULL));
    __quickSort3Ways(arr, 0, n - 1);
}

template<typename Item>
class MaxHeap {
private:
    Item *data;
    int count;
    int capacity;

    void shiftUp(int k) {
        while (k > 1 && data[k / 2] < data[k]) {
            swap(data[k / 2], data[k]);
            k /= 2;
        }
    }

    void shiftDown(int k) {
        while (2 * k <= count) {
            //j始终指向较大的数
            int j = 2 * k;
            if (j + 1 <= count && data[j + 1] > data[j]) {
                j++;
            }
            if (data[k] >= data[j]) {
                break;
            }
            swap(data[k], data[j]);
            k = j;
        }
    }

public:
    MaxHeap(int capacity) {
        data = new Item[capacity + 1];
        count = 0;
        this->capacity = capacity;
    }

    MaxHeap(Item arr[], int n) {
        data = new Item[n + 1];
        capacity = n;

        for (int i = 0; i < n; i++) {
            data[i + 1] = arr[i];
        }
        count = n;
        for (int i = count / 2; i >= 1; i--) {
            shiftDown(i);
        }
    }

    ~MaxHeap() {
        delete[] data;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    void insert(Item item) {
        assert(count + 1 <= capacity);
        data[count + 1] = item;
        count++;
        shiftUp(count);
    }


    Item extractMax() {
        assert(count > 0);
        Item ret = data[1];

        swap(data[1], data[count]);
        count--;
        shiftDown(1);
        return ret;
    }

    Item getMax() {
        assert(count > 0);
        return data[1];
    }

public:
    void testPrint() {

        if (size() >= 100) {
            cout << "Fancy print can only work for less than 100 int";
            return;
        }

        if (typeid(Item) != typeid(int)) {
            cout << "Fancy print can only work for int item";
            return;
        }

        cout << "The Heap size is: " << size() << endl;
        cout << "data in heap: ";
        for (int i = 1; i <= size(); i++)
            cout << data[i] << " ";
        cout << endl;
        cout << endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while (n > 0) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level - 1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for (int level = 0; level < max_level; level++) {
            string line1 = string(max_level_number * 3 - 1, ' ');

            int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
            bool isLeft = true;
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
                putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
                isLeft = !isLeft;
            }
            cout << line1 << endl;

            if (level == max_level - 1)
                break;

            string line2 = string(max_level_number * 3 - 1, ' ');
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
                putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
            cout << line2 << endl;

            cur_tree_max_level_number /= 2;
        }
    }

private:
    void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft) {

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if (num >= 10) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        } else {
            if (isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine(string &line, int index_cur_level, int cur_tree_width) {

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
        assert(offset_left + 1 < line.size());
        int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert(offset_right < line.size());

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
};

template<typename T>
void heapSort1(T arr[], int n) {
    MaxHeap<T> maxHeap = MaxHeap<T>(n);
    for (int i = 0; i < n; i++) {
        maxHeap.insert(arr[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = maxHeap.extractMax();
    }
}

template<typename T>
void heapSort2(T arr[], int n) {
    MaxHeap<T> maxHeap = MaxHeap<T>(arr, n);
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = maxHeap.extractMax();
    }
}




int main() {

    int n = 10000;
    cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
    int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);
    int *arr5 = SortTestHelper::copyIntArray(arr1, n);
    int *arr7 = SortTestHelper::copyIntArray(arr1, n);
    int *arr8 = SortTestHelper::copyIntArray(arr1, n);
    int *arr6 = SortTestHelper::copyIntArray(arr1, n);
    int *arr9 = SortTestHelper::copyIntArray(arr1, n);
    int *arr12 = SortTestHelper::copyIntArray(arr1, n);
    int *arr13 = SortTestHelper::copyIntArray(arr1, n);
    int *arr4 = SortTestHelper::generateNearlyOrderedArray(n, 100);
    int *arr10 = SortTestHelper::generateNearlyOrderedArray(n, 100);
    int *arr11 = SortTestHelper::copyIntArray(arr10, n);
    SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("Insertion Sort Better", insertionSortBetter, arr3, n);
    SortTestHelper::testSort("Insertion Sort Better Similar", insertionSortBetter, arr4, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr5, n);
    SortTestHelper::testSort("Shell Sort", shellSort, arr6, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr7, n);
    SortTestHelper::testSort("Merge Sort2", mergeSortBU, arr8, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr9, n);
    SortTestHelper::testSort("Quick Sort Similar", quickSort, arr10, n);
    SortTestHelper::testSort("Quick Sort Three Similar", quickSort3Ways, arr11, n);
    SortTestHelper::testSort("Heap Sort1", heapSort1, arr12, n);
    SortTestHelper::testSort("Heap Sort2", heapSort2, arr13, n);

    MaxHeap<int> maxHeap = MaxHeap<int>(100);
    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        maxHeap.insert(rand() % 100);
    }
    while (!maxHeap.isEmpty()) {
        cout << maxHeap.extractMax() << " ";
    }
    cout << endl;


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;
    delete[] arr8;
    delete[] arr9;
    delete[] arr10;
    delete[] arr11;
    delete[] arr12;
    delete[] arr13;

    return 0;
}