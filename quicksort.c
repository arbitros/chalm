#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quicksort(int arr[], int start, int end);
int partition(int arr[], int start, int end);
void insertion_sort(int arr[], int start, int end);
int pivot_median3(int arr[], int start, int end);
void swap(int[], int x, int y);
void print_array(int arr[], int arr_size);

const unsigned int ARR_SIZE = 100;

int main() {

    srand(1);

    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);

    int *p0 = malloc(sizeof(int[ARR_SIZE]));

    for (int i = 0; i < ARR_SIZE; i++) {
        int rd = rand()%100;
        p0[i] = rd;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double elapsed_init = (end.tv_sec-begin.tv_sec)
                              + (end.tv_nsec-begin.tv_nsec)*1e-9;

    clock_gettime(CLOCK_REALTIME, &begin);

    print_array(p0, ARR_SIZE);
    quicksort(p0,0,ARR_SIZE-1);
    print_array(p0, ARR_SIZE);
    free(p0);

    clock_gettime(CLOCK_REALTIME, &end);
    double elapsed_sort = (end.tv_sec-begin.tv_sec)
                              + (end.tv_nsec-begin.tv_nsec)*1e-9;

    printf("Time elapsed creating array of %d elements: %.3f s\n", ARR_SIZE, elapsed_init);
    printf("Time elapsed sorting array: %.3f s\n", elapsed_sort);

    return 0;
}

void quicksort(int arr[], int start, int end) {
    if (start >= end) return;

    int pivot_idx = partition(arr, start, end);

    quicksort(arr, start, pivot_idx-1);
    quicksort(arr, pivot_idx+1, end);
}

int partition(int arr[], int start, int end) {

    //int pivot_idx = pivot_median3(arr,start,end);
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
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int pivot_median3(int arr[], int start, int end) {
    if (end-start == 2) {
        return start;
    }

    int mid_idx = (int)((start+end)/2);
    int mid = *(arr + mid_idx);
    int left = *(arr + start);
    int right = *(arr + end);
    int arr3[3] = {mid,left,right};
    insertion_sort(arr3,0,2);
    int median3_val = arr3[1];

    if (median3_val == mid) {
        return mid_idx;
    } else if (median3_val == left) {
        return start;
    } else {
        return end;
    }
}

void insertion_sort(int arr[], int start, int end) {
    for (int i = 1; i <= end-start; i++) {
        int value_idx = i;
        int value = *(arr + value_idx);
        int pos = i-1;
        while (pos >= 0 && *(arr + pos) > value) {
            swap(arr, pos, value_idx);
            value_idx = pos;
            pos --;
        }
    }
}
