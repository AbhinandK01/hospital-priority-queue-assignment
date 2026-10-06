#include <stdio.h>
#include <stdlib.h>

#define MAX_PATIENTS 1000

typedef struct {
    int comparisons;
    int swaps;
} OperationCounts;

static void print_heap(const int heap[], int size)
{
    int i;

    printf("[");
    for (i = 0; i < size; ++i) {
        printf("%d%s", heap[i], i == size - 1 ? "" : ", ");
    }
    printf("]");
}

int main(int argc, char *argv[])
{
    const char *input_path = argc > 1 ? argv[1] : "input/patient_severity.txt";
    FILE *input = fopen(input_path, "r");
    int heap[MAX_PATIENTS];
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

    printf("Max Heap insertion trace (array representation)\n");
    printf("Input file: %s\n", input_path);

    for (i = 0; i < count; ++i) {
        int value;
        int child;
        OperationCounts step = {0, 0};

        if (fscanf(input, "%d", &value) != 1) {
            fprintf(stderr, "Error: expected %d severity scores; input ended at item %d.\n",
                    count, i + 1);
            fclose(input);
            return EXIT_FAILURE;
        }

        child = i;
        heap[child] = value;
        while (child > 0) {
            int parent = (child - 1) / 2;

            ++step.comparisons;
            if (heap[child] <= heap[parent]) {
                break;
            }

            {
                int temporary = heap[child];
                heap[child] = heap[parent];
                heap[parent] = temporary;
            }
            ++step.swaps;
            child = parent;
        }

        printf("Insert %d: ", value);
        print_heap(heap, i + 1);
        printf(" | comparisons: %d | swaps: %d\n", step.comparisons, step.swaps);
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

    if (count > 0) {
        printf("Highest priority (heap root): %d\n", heap[0]);
    } else {
        printf("No patients in the queue.\n");
    }
    return EXIT_SUCCESS;
}
