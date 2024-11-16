#include <stdio.h>

void quicksort(int arr[], int start, int end);
int partition(int arr[], int start, int end);
void swap(int[], int x, int y);
void print_array(int arr[], int arr_size);

int main() {

    int arr[] = {5,6,4,9,2,7,8,3};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    print_array(arr, arr_size);

    quicksort(arr,0,arr_size-1);

    print_array(arr, arr_size);

    return 0;
}

void quicksort(int arr[], int start, int end) {
    if (start >= end) return;

    int pivot_idx = partition(arr, start, end);

    quicksort(arr, start, pivot_idx-1);
    quicksort(arr, pivot_idx+1, end);
}

int partition(int arr[], int start, int end) {

    int pivot_idx = start;
    int pivot = *(arr + pivot_idx);

    swap(arr, start, pivot_idx);

    int lo = start + 1;
    int hi = end;

    while (1) {
        while (lo <= hi && *(arr+lo) < pivot) {
            lo ++;
        }
        while (hi >= lo && *(arr+hi) > pivot) {
            hi --;
        }

        if (lo > hi) break;

        swap(arr, lo, hi);
        lo ++; hi--;
    }
    swap(arr, pivot_idx, hi);
    return hi;
}

void swap(int arr[], int x, int y) {
    int temp = *(arr+x);
    *(arr + x) = *(arr + y);
    *(arr + y) = temp;
}

void print_array(int arr[], int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
}
