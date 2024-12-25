#include <iostream>
#include "Sort_test.h"

using namespace std;


int *temp;
void MSort(int *arr, int l, int r) {
    if(r-l==1) return ;
    int mid = (l+r)/2;
    MSort(arr,l,mid);
    MSort(arr,mid,r);
    int p1 = l,p2 = mid, k =0;
    
    while(p1 < mid || p2 < r) {
        if(p2 == r || (p1 < mid && arr[p1] <= arr[p2])) {
            temp[k++] = arr[p1++];
        } else 
            temp[k++] = arr[p2++];
    }
    for (int i= l; i < r;i++) {
        arr[i] = temp[i-l];
    }
    return ;

}


int main() {
    int *arr = getRandData(BIG_DATA_N);
    temp = (int *)malloc(sizeof(int) *BIG_DATA_N);
    TEST(MSort,arr, BIG_DATA_N);
    free(arr);
    free(temp);


    return 0;
}

