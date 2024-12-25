#include <iostream>
#include <stdlib.h>
#include "Sort_test.h"

using namespace std;

/*

    ShellSort
    时间复杂度 O(nlogn)~O(n^2)
    O(n^2)   希尔增量序列:n/2 、n/4、n/8、n/16
    O(n^1.5) Hibbard增量序列: 1 、3、7...2^k-1;
    希尔排序时间复杂度不固定

*/

      
    
void shell_sort(int *arr, int l, int r) {
    int k = 2, n = (r - l), step;
    do  {
        step = n/k == 0 ? 1 :n / k;
        for (int i = l; i < step + l; i++) {
            for (int j = i + step; j < r; j += step) {
                int m = j ,temp = arr[j];
                while(m > i && temp < arr[m - step]) {

                    arr[m] = arr[m-step];
                    m -= step;

                }
                arr[m] = temp; 
            }

        }
    k*=2;
    } while(step != 1);
    return ;

}


void shell_srot_Hibbard(int *arr, int l, int r) {
    int step = 1, n = (r - l);
    while(step<= n/2) step = step*2+1;
    do  {
        step /= 2;
        for (int i = l; i < step + l; i++) {
            for (int j = i + step; j < r; j += step) {
                int m = j ,temp = arr[j];
                while(m > i && temp < arr[m - step]) {

                    arr[m] = arr[m-step];
                    m -= step;

                }
                arr[m] = temp; 
            }

        }
    
    } while(step > 1);

}


int main() {
    int *arr = getRandData(BIG_DATA_N);
    TEST(shell_sort,arr, BIG_DATA_N);
    TEST(shell_srot_Hibbard,arr, BIG_DATA_N);
    free(arr);
    return 0;
}