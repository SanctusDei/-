#include <iostream>
#include "Sort_test.h"

void RadixSort(int *arr, int l, int r) {
    #define K 65535
    // round1
    int *cnt = (int *)malloc(sizeof(int)*K);
    int *temp = (int *)malloc(sizeof(int)*(r-l));
    memset(cnt,0,sizeof(int)*K);
    for (int i = l ; i < r;i++) cnt[arr[i]%K] +=1;
    for (int i = 1; i < K;i++) cnt[i] += cnt[i-1];
    for (int i = r-1;i >= l;--i) temp[--cnt[arr[i]%K]] = arr[i]; // 保证稳定性
    memcpy(arr+l, temp, sizeof(int)*(r-l));
    // round2
    memset(cnt,0,sizeof(int)*K);
    for (int i = l ; i < r;i++) cnt[arr[i]/K] +=1;
    for (int i = 1; i < K;i++) cnt[i] += cnt[i-1];
    for (int i = r-1; i >= l;--i) temp[--cnt[arr[i]/K]] = arr[i]; // 保证稳定性
    memcpy(arr+l, temp, sizeof(int)*(r-l));

    return ;
}


int main() {
    int *arr = getRandData(SMALL_DATA_N);
    TEST(RadixSort, arr, SMALL_DATA_N);
    int *arr2 = getRandData(BIG_DATA_N*10);
    TEST(RadixSort, arr2, BIG_DATA_N*10);
    free(arr);
    free(arr2);


    return 0;
}
