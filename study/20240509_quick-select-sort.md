### [quick select]

```cpp
#include <vector>
#include <iostream>
using namespace std;

inline void swap(int& a, int& b) { int temp = a; a = b; b = temp; }

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int pivot_index = right;
    right--;

    while (1) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;

        if (left >= right) break;
        else {
            swap(arr[left], arr[right]);
            left++;
        }
    }
    swap(arr[left], arr[pivot_index]);

    return left;
}

int quick_select(vector<int>& arr, int left, int right, int k) {
    if (left >= right) return arr[left];

    int pivot_index = partition(arr, left, right);
    if (k < pivot_index) return quick_select(arr, left, pivot_index - 1, k);
    else if (k > pivot_index) return quick_select(arr, pivot_index + 1, right, k);
    else return arr[pivot_index];
}

void quick_sort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int pivot = partition(arr, left, right);
    quick_sort(arr, left, pivot - 1);
    quick_sort(arr, pivot + 1, right);
}

void print(const vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

// ==================================================================
int main() {
    vector<int> arr = { 1, 7, 4, 3, 2, 9, 4 };
    int n = arr.size();
    int k = 4;

    int num = quick_select(arr, 0, n - 1, k);
    print(arr);
    cout << k << " 번째 수 : " << num << "\n";

    quick_sort(arr, 0, n - 1);
    print(arr);

    return 0;
}
```
