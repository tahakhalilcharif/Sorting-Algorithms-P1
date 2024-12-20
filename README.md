# Sorting Algorithms Performance Comparison

## Project Overview

This C program compares the performance of different sorting algorithms by measuring their execution times across various array sizes. The project implements and benchmarks the following sorting algorithms:

- Selection Sort
- Insertion Sort
- Binary Insertion Sort
- Merge Sort
- Heap Sort
- Quick Sort

## Features

- Generates random arrays of increasing sizes
- Measures and records execution time for each sorting algorithm
- Exports results to a CSV file for further analysis
- Includes a flexible performance testing framework

## Prerequisites

- GCC or another C compiler
- Python (optional, for visualization)
- Matplotlib and Pandas (optional, for plotting results)

## Compilation

To compile the program, use the following command:

```bash
gcc -std=c99 -o com com.c
```
or

```bash
gcc -std=c99 -o comp2 comp2.c
```

## Usage

1. Compile the program
2. Run the executable
3. Check the generated `sorting_results.csv` file

### On PowerShell
```bash
./com
```

or 

```bash
./comp2
```

### On Command Prompt
```bash
com
```

or 

```bash
comp2
```

## Visualization

Included is a Python script to visualize the sorting algorithm performance:
```bash
python visualise.py
```

## Performance Characteristics

### Selection Sort
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Suitable for small datasets
- Not efficient for large arrays

### Insertion Sort
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Performs well on small or nearly sorted arrays

### Binary Insertion Sort
- Time Complexity: O(n log n) for search, O(n²) overall
- Reduces number of comparisons compared to standard insertion sort
- More efficient for larger datasets

### Merge Sort
- Time Complexity: O(n log n)
- Space Complexity: O(n)
- Stable sorting algorithm
- Efficient for larger datasets

### Heap Sort
- Time Complexity: O(n log n)
- Space Complexity: O(1)
- In-place sorting algorithm
- Consistent performance across different input sizes

### Quick Sort
- Time Complexity: Average O(n log n), Worst O(n²)
- Space Complexity: O(log n)
- Efficient in practice
- Performance depends on pivot selection

## Expected Output

The program generates:
- Console output with execution times
- `sorting_results.csv` with detailed timing data
- Optional visualization graph

## Limitations

- Uses random number generation for array creation
- Measures CPU time, which can vary between runs
- Designed for comparative analysis, not absolute performance measurement


## Contributing

Contributions, issues, and feature requests are welcome!

## Author

Charif Taha Khalil