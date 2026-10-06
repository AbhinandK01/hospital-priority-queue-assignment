# Hospital Patient Priority Queue

This assignment implements a max heap for a hospital's severity-based patient
queue and compares Heap Sort with Quick Sort on the same scores.

## Input

`input/patient_severity.txt` contains the patient count followed by the severity
scores:

```text
7
45 72 30 90 65 50 85
```

## Build and run

From this directory, using GCC in PowerShell on Windows:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src\max_heap.c -o max_heap.exe
.\max_heap.exe input\patient_severity.txt

gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src\sorting.c -o sorting.exe
.\sorting.exe input\patient_severity.txt
```

On Linux or macOS, replace `\` with `/`, omit `.exe`, and run the programs as
`./max_heap` and `./sorting`.

The recorded executions are saved in:

- `output/max_heap_output.txt`
- `output/sorting_output.txt`

Both sorting functions operate on copies of the input so they can each sort the
same original data independently.

The programs report errors to standard error and return a nonzero status if
the input file cannot be read or does not match its declared count. The input
count is limited to 1,000 values.

## Deliverables

- [Source code](src/)
- [Input data](input/patient_severity.txt)
- [Captured executions](output/)
- [Trace tables](trace_table.md)
- [Complexity analysis](complexity_analysis.md)
- [Comparison table and conclusion](comparison.md)

## Final conclusion

For a continuously changing patient queue where the most severe patient must
be available immediately, use a **max heap as the priority queue**. It provides
the highest score at the root in O(1), while insertion and removing the
highest-priority item each take O(log n). Heap Sort and Quick Sort sort a batch
of scores; neither alone offers the same direct priority-queue behavior when
new patients keep arriving.
