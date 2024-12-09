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

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
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
    int sizes[500];
    for (int i = 0; i < 500; i++) {
        sizes[i] = (i + 1) * 100;
    }

    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    double time;
    FILE *csvFile = fopen("sorting_results.csv", "w");
    if (csvFile == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    fprintf(csvFile, "Array Size,Selection Sort,Insertion Sort,Binary Insertion Sort,Merge Sort\n");

    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        int *array = malloc(size * sizeof(int));
        generateArray(array, size);
        
        printf("\nTaille du tableau : %d\n", size);

        time = measureTime(selectionSort, array, size);
        printf("Tri par sélection : %.6f secondes\n", time);
        double selectionTime = time;

        time = measureTime(insertionSort, array, size);
        printf("Tri par insertion : %.6f secondes\n", time);
        double insertionTime = time;

        time = measureTime(binaryInsertionSort, array, size);
        printf("Tri par insertion avec recherche dichotomique : %.6f secondes\n", time);
        double binaryInsertionTime = time;

        time = measureTime(mergeSort, array, size);
        printf("Tri par fusion : %.6f secondes\n", time);
        double mergeTime = time;

        fprintf(csvFile, "%d,%.6f,%.6f,%.6f,%.6f\n", size, selectionTime, insertionTime, binaryInsertionTime, mergeTime);

        free(array);
    }

    fclose(csvFile);
    printf("\nResults saved to sorting_results.csv\n");

    return 0;
}
