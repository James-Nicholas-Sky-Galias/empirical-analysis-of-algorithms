#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

clock_t start, end;
double cpu_time_used;

//Fills the array with random numbers
void generateRandomArray(unsigned long int arr[], int n, unsigned long int maxSize) {
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Error: Invalid arguments passed to generateRandomArray.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (maxSize + 1); // Random number between 0 and maxSize
    }
}

void fixedIntervalArray(unsigned long int arr[], int n, unsigned long int x) {
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Error: Invalid arguments passed to fixedIntervalArray.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = x++;
    }
}

void selectionSort(unsigned long int arr[], int n) {
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Error: Invalid arguments passed to selectionSort.\n");
        return;
    }
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
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Error: Invalid arguments passed to insertionSort.\n");
        return;
    }
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
    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Error: Invalid arguments passed to bubbleSort.\n");
        return;
    }
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
    if (arr == NULL) {
        fprintf(stderr, "Error: NULL array passed to merge.\n");
        return;
    }

    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    unsigned long int *leftArr = malloc((size_t)n1 * sizeof(unsigned long int));
    unsigned long int *rightArr = malloc((size_t)n2 * sizeof(unsigned long int));

    if (!leftArr || !rightArr) {
        fprintf(stderr, "Error: Memory allocation failed in merge — %s.\n", strerror(errno));
        free(leftArr);
        free(rightArr);
        return;
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
    if (arr == NULL) {
        fprintf(stderr, "Error: NULL array passed to mergeSort.\n");
        return;
    }
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
    if (a == NULL || b == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to swap.\n");
        return;
    }
    unsigned long int t = *a;
    *a = *b;
    *b = t;
}

// partition function
int partition(unsigned long int arr[], int low, int high) {
    if (arr == NULL) {
        fprintf(stderr, "Error: NULL array passed to partition.\n");
        return -1;
    }
    
    // Choose the pivot as median of first, middle, last
    int mid = low + (high - low) / 2;
    unsigned long int a = arr[low], b = arr[mid], c = arr[high];
    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        // b is median
        swap(&arr[mid], &arr[high]);
    } else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        // a is median
        swap(&arr[low], &arr[high]);
    }
    // else c is median, already at high
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
    if (arr == NULL) {
        fprintf(stderr, "Error: NULL array passed to quickSort.\n");
        return;
    }
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

    if (arr == NULL) {
        fprintf(stderr, "Error: NULL array passed to heapify.\n");
        return;
    }

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

    if (arr == NULL || n <= 0) {
        fprintf(stderr, "Error: Invalid arguments passed to heapSort.\n");
        return;
    }

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

// Returns a string name for the chosen algorithm
const char *algorithmName(int algChoice) {
    switch (algChoice) {
        case 1: return "Selection Sort";
        case 2: return "Insertion Sort";
        case 3: return "Bubble Sort";
        case 4: return "Merge Sort";
        case 5: return "Quick Sort";
        case 6: return "Heap Sort";
        default: return "Unknown";
    }
}

// Opens the output file and writes the session header.
// Returns the FILE pointer on success, NULL on failure.
FILE *openOutputFile(const char *filename, int n, int algChoice, int choice, unsigned long int x) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Warning: Could not open output file '%s' — %s. Results will not be saved.\n",
                filename, strerror(errno));
        return NULL;
    }

    time_t now = time(NULL);
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&now));

    fprintf(fp, "========================================\n");
    fprintf(fp, " Sorting Benchmark Results\n");
    fprintf(fp, " Date/Time  : %s\n", timebuf);
    fprintf(fp, " Algorithm  : %s\n", algorithmName(algChoice));
    fprintf(fp, " Array size : %d\n", n);
    if (choice == 1)
        fprintf(fp, " Data type  : Random numbers\n");
    else
        fprintf(fp, " Data type  : Sorted numbers (starting from %lu)\n", x);
    fprintf(fp, "========================================\n\n");

    return fp;
}

// Reads a single int from stdin, returning 1 on success, 0 on failure.
// Clears the input buffer on bad input.
int readInt(int *out) {
    if (scanf("%d", out) != 1) {
        // Clear the bad input from the buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    return 1;
}

// Reads a single unsigned long int from stdin, returning 1 on success, 0 on failure.
int readULong(unsigned long int *out) {
    if (scanf("%lu", out) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    return 1;
}

//writes the header for the CSV file for excel
FILE *openCSVFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Warning: Could not open CSV file '%s' — %s.\n",
                filename, strerror(errno));
        return NULL;
    }
    fprintf(fp, "Algorithm,N,Data Type,Run 1,Run 2,Run 3,Run 4,Run 5,Average\n");
    return fp;
}

int main() {    
    const unsigned long int maxSize = 1000000000UL; // Maximum value for random numbers //Arbitrarily large number to ensure we get a good distribution of random numbers
    int n = 0; // n = size of the array
    unsigned long int x = 0; // x = starting value for sorted array
    srand((unsigned int)time(NULL));

    // --- Array size input ---
    printf("Enter the size of the array to sort: ");
    while (!readInt(&n) || n <= 0) {
        printf("Please enter a positive integer for the size of the array: ");
    }

    unsigned long int *arr = (unsigned long int *)malloc((size_t)n * sizeof(unsigned long int));
    if (arr == NULL) {
        fprintf(stderr, "Fatal: Memory allocation failed for array of size %d — %s.\n", n, strerror(errno));
        return EXIT_FAILURE;
    }

    // --- Data generation choice ---
    int choice = 0;
    printf("Which data generation method would you like to use?\n");
    printf("1. Random numbers\n");
    printf("2. Sorted numbers\n");
    printf("Enter your choice (1 or 2): ");
    while (!readInt(&choice) || choice < 1 || choice > 2) {
        printf("Invalid choice. Please enter 1 or 2: ");
    }

    if (choice == 2) {
        printf("Enter the starting value for the sorted array: ");
        while (!readULong(&x)) {
            printf("Invalid value. Please enter a non-negative integer: ");
        }
    }

    // --- Algorithm choice ---
    int algChoice = 0;
    printf("Which sorting algorithm would you like to use?\n");
    printf("1. Selection Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Bubble Sort\n");
    printf("4. Merge Sort\n");
    printf("5. Quick Sort\n");
    printf("6. Heap Sort\n");
    printf("Enter your choice (1-6): ");
    while (!readInt(&algChoice) || algChoice < 1 || algChoice > 6) {
        printf("Invalid choice. Please enter a number between 1 and 6: ");
    }

    printf("\n");

    // --- Open output file ---
    // Filename format: results_*sorting algorithm*_*n size*_*date & time*.txt
    char filename[128];
    char csvFilename[128];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(filename, sizeof(filename), "results_%s_n%d_%04d%02d%02d_%02d%02d%02d.txt",
            algorithmName(algChoice), n,
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    snprintf(csvFilename, sizeof(csvFilename), "results_%s_n%d_%04d%02d%02d_%02d%02d%02d.csv",
            algorithmName(algChoice), n,
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);

    // Replace spaces in algorithm name with underscores in both filenames
    for (int i = 0; filename[i]; i++) {
        if (filename[i] == ' ') filename[i] = '_';
    }
    for (int i = 0; csvFilename[i]; i++) {
        if (csvFilename[i] == ' ') csvFilename[i] = '_';
    }

    // fp may be NULL if file cannot be opened — program continues without saving
    FILE *fp = openOutputFile(filename, n, algChoice, choice, x);
    FILE *csvFp = openCSVFile(csvFilename);

    // --- 5 timed runs ---
    double totalTime = 0.0;
    double runTimes[5] = {0}; // For CSV output

    // Start measuring time
    for (int i = 0; i < 5; i++) {
        if (choice == 1) {
            generateRandomArray(arr, n, maxSize); // Fill the array with random numbers
        } else {
            fixedIntervalArray(arr, n, x); // Fill the array with sorted numbers starting from x
        }

        printf("Starting run %d...\n", i + 1);
        printf("Sorting array of size %d...\n", n);
        if (fp) fprintf(fp, "--- Run %d ---\n", i + 1);

        if (fp)
        {
            fprintf(fp, "Array before sorting:\n");
            for (int j = 0; j < n; j++) {
                fprintf(fp, "%lu ", arr[j]);
            }
            fprintf(fp, "\n");
        }

        // Sort the array using the selected sort algorithm
        switch (algChoice) {
            case 1:
                start = clock();
                selectionSort(arr, n);
                end = clock();
                break;
            case 2:
                start = clock();
                insertionSort(arr, n);
                end = clock();
                break;
            case 3:
                start = clock();
                bubbleSort(arr, n);
                end = clock();
                break;
            case 4:
                start = clock();
                mergeSort(arr, 0, n - 1);
                end = clock();
                break;
            case 5:
                start = clock();
                quickSort(arr, 0, n - 1);
                end = clock();
                break;
            case 6:
                start = clock();
                heapSort(arr, n);
                end = clock();
                break;
        }

        // Calculate the CPU time used
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        totalTime += cpu_time_used;
        runTimes[i] = cpu_time_used; // Store for CSV output

        // Console output
        printf("\nRun %d:\nTime taken to sort: %0.3f seconds\n\n", i + 1, cpu_time_used);

        // File output
        if (fp) fprintf(fp, "Time taken to sort: %0.3f seconds\n\n", cpu_time_used);
        if (fp)
        {
            fprintf(fp, "Array after sorting:\n");
            for (int j = 0; j < n; j++) {
                fprintf(fp, "%lu ", arr[j]);
            }
            fprintf(fp, "\n\n");
        }
    }

    // --- Summary (console + file) ---
    double avgTime = totalTime / 5.0;

    printf("========================================\n");
    printf("Summary\n");
    printf("Algorithm  : %s\n", algorithmName(algChoice));
    printf("Array size : %d\n", n);
    printf("Total time : %0.3f seconds\n", totalTime);
    printf("Average    : %0.3f seconds per run\n", avgTime);
    printf("========================================\n");

    if (fp) {
        fprintf(fp, "========================================\n");
        fprintf(fp, "Summary\n");
        fprintf(fp, "Algorithm  : %s\n", algorithmName(algChoice));
        fprintf(fp, "Array size : %d\n", n);
        fprintf(fp, "Total time : %0.3f seconds\n", totalTime);
        fprintf(fp, "Average    : %0.3f seconds per run\n", avgTime);
        fprintf(fp, "========================================\n");
        fclose(fp);
        printf("\nResults saved to: %s\n", filename);
    }
    
    if (csvFp) {
        fprintf(csvFp, "%s,%d,%s,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",
                algorithmName(algChoice), n, (choice == 1) ? "Random" : "Sorted",
                runTimes[0], runTimes[1], runTimes[2], runTimes[3], runTimes[4], avgTime);
        fclose(csvFp);
        printf("CSV results saved to: %s\n", csvFilename);
    }

    free(arr);
    return EXIT_SUCCESS;
}
