#include <iostream>
#include <random>

using namespace std;

void output(int *arr, int n, int ind = -1) {
    int len = 0;
    for (int i = 0; i < n; i++) {
        len+= printf("%4d", i);
    }
    printf("\n");
    for(int i = 0;i < len;i++)printf("-");
    printf("\n");
    for (int i = 0; i < n; i++) {
        if(i == ind) printf("\033[1;32m");
        printf ("%4d", arr[i]);
        if(i == ind) printf("\033[0m");

    }

    printf("\n");
    return ;

}

int binary_search(int *arr, int n, int x) {
    int left = 0, right = n - 1,mid;
    while(left <= right) {
        mid = (left + right)/2;
        printf("[%d, %d],mid = %d,arr[%d] = %d\n",
         left, right, mid,
         mid,arr[mid]
         );
        if(arr[mid] == x) return mid;
        if(arr[mid] > x) right = mid-1;
        else left = mid + 1;
    }
    return -1;

}


void test_binary_search(int n) {
    int x;
    int *arr = (int *)malloc (sizeof(int) * n);
    arr[0] = rand()% 10;
    for (int i = 1 ;i < n;i++) {
        arr[i] = arr[i-1]+ rand() %10;
    }
    output(arr, n);
    while(~scanf("%d", &x)) {

        if(x == -1) break;
        int ind = binary_search(arr, n, x);
        output(arr, n,ind);
    }
}


int main() {
    test_binary_search(10);

    return 0;
}