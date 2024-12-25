#include <iostream>
#include "Sort_test.h"

using namespace std;


//有哨插入排序
void InsertSort(int *arr, int l, int r) {   
    for(int i = l+1; i < r; i++) {
            int temp = arr[i];
            int j = i;
            while(j > l && temp < arr[j-1]) {
                    // j > l 判断会占用时间
                arr[j] = arr[j-1];
                j--;
            }
            arr[j] = temp;


        }
        
    }


int main() {
    int *arr = getRandData(SMALL_DATA_N);
    TEST(InsertSort, arr, SMALL_DATA_N);
    free(arr);


    return 0;
}