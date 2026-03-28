#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

clock_t start, end;
double cpu_time_used;

void bubbleSort(unsigned long int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                unsigned long int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

//Fills the array with random numbers
void generateRandomArray(unsigned long int arr[], int n, unsigned long int maxSize) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (maxSize + 1); // Random number between 0 and maxSize
    }
}

void fixedIntervalArray(unsigned long int arr[], int n, unsigned long int x) {
    for (int i = 0; i < n; i++) {
        arr[i] = x++;
    }
}

void merge(unsigned long int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    unsigned long int *leftArr = malloc((size_t)n1 * sizeof(unsigned long int));
    unsigned long int *rightArr = malloc((size_t)n2 * sizeof(unsigned long int));
    if (!leftArr || !rightArr) {
        free(leftArr);
        free(rightArr);
        return; // or handle error
    }

    for (i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else                           arr[k++] = rightArr[j++];
    }
    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];

    free(leftArr);
    free(rightArr);
}

// The subarray to be sorted is in the index range [left-right]
void mergeSort(unsigned long int arr[], int left, int right) {
    if (left < right) {
      
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {    
    unsigned long int maxSize = 1000000000UL; // Maximum value for random numbers //Arbitrarily large number to ensure we get a good distribution of random numbers
    int n = 1000000; // Size of the array
    unsigned long int *arr = (unsigned long int *)malloc(n * sizeof(unsigned long int));

    srand(time(0)); // Seed the random number generator

    // Start measuring time
    for (int i = 0; i < 5; i++)
    {
        
        generateRandomArray(arr, n, maxSize); // Fill the array with random numbers
        
        printf("Starting run %d...\n", i + 1);

        start = clock();

        // Sort the array using bubble sort
        bubbleSort(arr, n);

        // End measuring time
        end = clock();
        
        // Calculate the CPU time used
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\nRun %d Time taken to sort: %f seconds\n", i + 1, cpu_time_used);

    }

    free(arr);
    return 0;
}
