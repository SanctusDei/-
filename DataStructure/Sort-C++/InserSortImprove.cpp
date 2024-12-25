#include <iostream>
#include "Sort_test.h"

using namespace std;



//有哨插入排序
void InsertSort(int *arr, int l, int r) {   
    for(int i = l+1; i < r; i++) {
            int temp = arr[i];
            int j = i;
            while(j > l && temp < arr[j-1]) {
                arr[j] = arr[j-1];
                j--;
            }
            arr[j] = temp;

        }
        
    }



//无哨插入排序(优化)
void unguarded_insert_sort(int *arr, int l, int r) {
    int ind = l,temp;
    for (int i = l+1; i < r; i++) {
        if(arr[i] < arr[ind]) ind = i;
    }
    temp = arr[ind];
    while(ind > l) {
        arr[ind] = arr[ind-1];
        ind--;   
    }
    //增加O(n)次操作
    //先将最小值提到数组首位
    arr[l] = temp;
    for(int i = l+1; i < r; i++) {
        int temp = arr[i];
        int j = i;
        while(temp < arr[j-1]) {
            arr[j] = arr[j-1];
            j--;
        }
        arr[j] = temp;
            
        // 减少了O(n2)比较 (j>l)
        }
        
    }
     
        




int main() {
    // 数据量小的时候无法体现优化

    int *arr = getRandData(SMALL_DATA_N);
    TEST(unguarded_insert_sort, arr, SMALL_DATA_N);
    TEST(InsertSort, arr, SMALL_DATA_N);
    free(arr);


    return 0;
}