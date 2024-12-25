#include <iostream>
#include "Sort_test.h"

using namespace std;

// Partition
int Partition(int *arr, int l, int r) {
    int p = arr[l];
    while(l < r) {
        while(l < r && arr[r] >= p) -- r;
        swap(arr[l], arr[r]);
        while(l < r && arr[l] <= p) ++l;
        swap(arr[l], arr[r]);
    }
    return l;
}

void QSort(int *arr, int l, int r) {
    if (l  < r) {
        int p = Partition(arr, l, r);
        QSort(arr, l, p-1);
        QSort(arr, p+1, r);
    }

}


int main() {

    int *arr = getRandData(SMALL_DATA_N*10);
    TEST(QSort, arr, SMALL_DATA_N*10);
    free(arr);
    int *arr2 = getRandData(BIG_DATA_N);
    TEST(QSort, arr2, BIG_DATA_N);
    free(arr2);

    return 0;
}