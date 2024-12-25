#include <iostream>
#include "Sort_test.h"

using namespace std;

void SelectSort(int *arr, int  l, int r) {
    for (int i = l; i < r - 1 ; ++i ) {

        int mini = i;
        for (int j = i + 1; j < r; ++j) {
            
            if(arr[j] < arr[mini]) 
                mini = j;
            
        }

        swap(arr[i], arr[mini]);
    }
}



int main() {

    int *arr = getRandData(SMALL_DATA_N);
    TEST(SelectSort, arr, SMALL_DATA_N);
    free(arr);

    return 0;

}


