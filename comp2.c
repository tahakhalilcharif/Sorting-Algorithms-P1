#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(&arr[i], &arr[minIdx]);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int binarySearch(int arr[], int item, int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (item == arr[mid])
            return mid + 1;
        else if (item > arr[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

void binaryInsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int pos = binarySearch(arr, key, 0, i - 1);
        for (int j = i - 1; j >= pos; j--) {
            arr[j + 1] = arr[j];
        }
        arr[pos] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

void mergeSortHelper(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(int arr[], int n) {
    mergeSortHelper(arr, 0, n - 1);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortHelper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int n) {
    quickSortHelper(arr, 0, n - 1);
}

void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

double measureTime(void (*sortFunction)(int[], int), int arr[], int n) {
    int *tempArr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tempArr[i] = arr[i];
    }

    clock_t start = clock();
    sortFunction(tempArr, n);
    clock_t end = clock();

    free(tempArr);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    int sizes[100];
    for (int i = 0; i < 100; i++) {
        sizes[i] = (i + 1) * 10000;
    }

    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    double time;
    FILE *csvFile = fopen("sorting_results.csv", "w");
    if (csvFile == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    fprintf(csvFile, "Array Size,Selection Sort,Insertion Sort,Binary Insertion Sort,Merge Sort,Heap Sort,Quick Sort\n");

    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        int *array = malloc(size * sizeof(int));
        generateArray(array, size);

        time = measureTime(selectionSort, array, size);
        double selectionTime = time;

        time = measureTime(insertionSort, array, size);
        double insertionTime = time;

        time = measureTime(binaryInsertionSort, array, size);
        double binaryInsertionTime = time;

        time = measureTime(mergeSort, array, size);
        double mergeTime = time;

        time = measureTime(heapSort, array, size);
        double heapTime = time;

        time = measureTime(quickSort, array, size);
        double quickTime = time;

        fprintf(csvFile, "%d,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n", size, selectionTime, insertionTime, binaryInsertionTime, mergeTime, heapTime, quickTime);

        free(array);
    }

    fclose(csvFile);
    printf("\nResults saved to sorting_results.csv\n");

    return 0;
}
