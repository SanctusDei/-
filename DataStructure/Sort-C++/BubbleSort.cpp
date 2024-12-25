#include <iostream>
#include "Sort_test.h"

using namespace std;

void BubbleSort(int *arr, int l, int r)
{
    for (int i = r - 1, I = l + 1; i >= I; --i)
    {
        for (int j = l; j < i; j++)
        {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}

int main()
{
    int *arr = getRandData(SMALL_DATA_N);
    TEST(BubbleSort,arr,SMALL_DATA_N);

    return 0;
}