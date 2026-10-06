# Complexity Analysis

Let `n` be the number of patients and `h = floor(log2(n))` the height of a
complete binary heap (for `n >= 1`; an empty heap has height 0 by convention).

## Max Heap priority queue

| Operation | Time | Extra space |
|---|---:|---:|
| Read highest priority (root) | O(1) | O(1) |
| Insert one patient | O(log n) worst case | O(1) per insertion |
| Remove highest-priority patient | O(log n) | O(1) |
| Build heap by repeated insertion | O(n log n) worst case | O(n) storage for the heap |

For these seven patients, the heap is complete and has height
`floor(log2(7)) = 2` edges (three levels).

## Sorting algorithms

| Algorithm | Best time | Average time | Worst time | Auxiliary space |
|---|---:|---:|---:|---:|
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) when sorting in place |
| Quick Sort (Lomuto, last-element pivot) | O(n log n) | O(n log n) | O(n^2) | O(log n) average recursion; O(n) worst recursion |

The demonstrated Heap Sort copies the input into a local working array so it
can independently compare both algorithms; its sort itself uses O(1)
auxiliary space beyond that copy. The demonstrated recursive Quick Sort also
copies the input, and its recursion stack is separate from the working array.
Counts in `output/sorting_output.txt` count key-to-key comparisons and
non-self swaps only. Heap Sort comparison counts include comparisons against
each existing child during sift-down; Quick Sort counts each comparison of an
array value with the pivot. A swap is counted only when its two indices differ.
