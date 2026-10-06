#include <stdio.h>
#include <stdlib.h>

#define MAX_PATIENTS 1000

typedef struct {
    long comparisons;
    long swaps;
} OperationCounts;

static void print_array(const int values[], int size)
{
    int i;

    printf("[");
    for (i = 0; i < size; ++i) {
        printf("%d%s", values[i], i == size - 1 ? "" : ", ");
    }
    printf("]");
}

static void swap_values(int values[], int first, int second, OperationCounts *counts)
{
    int temporary;

    if (first == second) {
        return;
    }

    temporary = values[first];
    values[first] = values[second];
    values[second] = temporary;
    ++counts->swaps;
}

static void sift_down(int values[], int root, int heap_size,
                      OperationCounts *counts)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < heap_size) {
        ++counts->comparisons;
        if (values[left] > values[largest]) {
            largest = left;
        }
    }
    if (right < heap_size) {
        ++counts->comparisons;
        if (values[right] > values[largest]) {
            largest = right;
        }
    }

    if (largest != root) {
        swap_values(values, root, largest, counts);
        sift_down(values, largest, heap_size, counts);
    }
}

static void heap_sort(const int input[], int size)
{
    int values[MAX_PATIENTS];
    int i;
    OperationCounts counts = {0, 0};

    for (i = 0; i < size; ++i) {
        values[i] = input[i];
    }

    printf("Heap Sort (ascending; max heap)\n");
    printf("Initial: ");
    print_array(values, size);
    printf("\n");

    for (i = size / 2 - 1; i >= 0; --i) {
        sift_down(values, i, size, &counts);
    }
    printf("Max heap built: ");
    print_array(values, size);
    printf("\n");

    for (i = size - 1; i > 0; --i) {
        swap_values(values, 0, i, &counts);
        sift_down(values, 0, i, &counts);
        printf("Move max %d to index %d: ", values[i], i);
        print_array(values, size);
        printf(" | active heap size: %d\n", i);
    }

    printf("Sorted: ");
    print_array(values, size);
    printf("\nComparisons: %ld | swaps: %ld\n\n", counts.comparisons, counts.swaps);
}

static int partition(int values[], int low, int high, OperationCounts *counts)
{
    int pivot = values[high];
    int boundary = low - 1;
    int current;

    for (current = low; current < high; ++current) {
        ++counts->comparisons;
        if (values[current] <= pivot) {
            ++boundary;
            swap_values(values, boundary, current, counts);
        }
    }
    swap_values(values, boundary + 1, high, counts);
    return boundary + 1;
}

static void quick_sort_recursive(int values[], int low, int high,
                                 OperationCounts *counts)
{
    if (low < high) {
        int pivot_index = partition(values, low, high, counts);

        printf("Partition [%d..%d], pivot %d at index %d: ",
               low, high, values[pivot_index], pivot_index);
        print_array(values, high + 1);
        printf("\n");

        quick_sort_recursive(values, low, pivot_index - 1, counts);
        quick_sort_recursive(values, pivot_index + 1, high, counts);
    }
}

static void quick_sort(const int input[], int size)
{
    int values[MAX_PATIENTS];
    int i;
    OperationCounts counts = {0, 0};

    for (i = 0; i < size; ++i) {
        values[i] = input[i];
    }

    printf("Quick Sort (ascending; Lomuto partition, last element pivot)\n");
    printf("Initial: ");
    print_array(values, size);
    printf("\n");
    quick_sort_recursive(values, 0, size - 1, &counts);
    printf("Sorted: ");
    print_array(values, size);
    printf("\nComparisons: %ld | swaps: %ld\n", counts.comparisons, counts.swaps);
}

int main(int argc, char *argv[])
{
    const char *input_path = argc > 1 ? argv[1] : "input/patient_severity.txt";
    FILE *input = fopen(input_path, "r");
    int values[MAX_PATIENTS];
    int count;
    int i;

    if (input == NULL) {
        fprintf(stderr, "Error: could not open input file '%s'.\n", input_path);
        return EXIT_FAILURE;
    }

    if (fscanf(input, "%d", &count) != 1 || count < 0 || count > MAX_PATIENTS) {
        fprintf(stderr, "Error: input must begin with a patient count from 0 to %d.\n",
                MAX_PATIENTS);
        fclose(input);
        return EXIT_FAILURE;
    }
    for (i = 0; i < count; ++i) {
        if (fscanf(input, "%d", &values[i]) != 1) {
            fprintf(stderr, "Error: expected %d severity scores; input ended at item %d.\n",
                    count, i + 1);
            fclose(input);
            return EXIT_FAILURE;
        }
    }
    if (fscanf(input, "%d", &i) == 1) {
        fprintf(stderr, "Error: input contains more severity scores than declared.\n");
        fclose(input);
        return EXIT_FAILURE;
    }
    if (fclose(input) != 0) {
        fprintf(stderr, "Error: could not close input file '%s'.\n", input_path);
        return EXIT_FAILURE;
    }

    heap_sort(values, count);
    quick_sort(values, count);
    return EXIT_SUCCESS;
}
