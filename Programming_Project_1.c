#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

clock_t start, end;
double cpu_time_used;

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

void selectionSort(unsigned long int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
      
        // Assume the current position holds
        // the minimum element
        int min_idx = i;
        
        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
              
                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }
        
        // Move minimum element to its
        // correct position
        unsigned long int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void insertionSort(unsigned long int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        unsigned long int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

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

void swap(unsigned long int* a, unsigned long int* b) {
    unsigned long int t = *a;
    *a = *b;
    *b = t;
}

// partition function
int partition(unsigned long int arr[], int low, int high) {
    
    // Choose the pivot
    unsigned long int pivot = arr[high];
    
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements to the left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

// The QuickSort function implementation
void quickSort(unsigned long int arr[], int low, int high) {
    if (low < high) {
        
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(unsigned long int arr[], int n, int i){

    // Initialize largest as root
    int largest = i;

    // left index = 2*i + 1
    int l = 2 * i + 1;

    // right index = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        unsigned long int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(unsigned long int arr[], int n){

    // Build heap (rearrange vector)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {

        // Move current root to end
        unsigned long int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {    
    const unsigned long int maxSize = 1000000000UL; // Maximum value for random numbers //Arbitrarily large number to ensure we get a good distribution of random numbers
    int n = 0; // n = size of the array
    unsigned long int x = 0; // x = starting value for sorted array
    srand(time(0)); // Seed the random number generator

    printf("Enter the size of the array to sort: ");
    scanf("%d", &n);

    if (n <= 0) {
        while (n <= 0) {
            printf("Please enter a positive integer for the size of the array: ");
            scanf("%d", &n);
        }
    }

    unsigned long int *arr = (unsigned long int *)malloc(n * sizeof(unsigned long int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int choice;
    printf("Which data generation method would you like to use?\n");
    printf("1. Random numbers\n");
    printf("2. Sorted numbers\n");

    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 2) {
        while (choice < 1 || choice > 2) {
            printf("Invalid choice. Please enter 1 or 2: ");
            scanf("%d", &choice);
        }
    }

    if (choice == 2) 
    {
        printf("Enter the starting value for the sorted array: ");
        scanf("%lu", &x);
    }

    printf("\n\n");
    // Start measuring time
    for (int i = 0; i < 5; i++)
    {
        if (choice == 1) {
            generateRandomArray(arr, n, maxSize); // Fill the array with random numbers
        } else if (choice == 2) {
            fixedIntervalArray(arr, n, x); // Fill the array with sorted numbers starting from x
        } else {
            printf("Invalid choice. Please enter 1 or 2.\n");
            free(arr);
            return 1;
        }
        
        printf("Starting run %d...\n", i + 1);
        printf("Sorting array of size %d...\n", n);

        start = clock();

        // Sort the array using bubble sort
        selectionSort(arr, n);

        // End measuring time
        end = clock();
        
        // Calculate the CPU time used
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\nRun %d:\nTime taken to sort: %f seconds\n\n", i + 1, cpu_time_used);

    }

    free(arr);
    return 0;
}
