# Execution Trace Tables

Array positions use zero-based indices in the programs. A max heap keeps each
parent at least as large as its children. Its root is therefore the most
severe patient.

## Max Heap insertion trace

| Step | Inserted severity | Heap array after insertion | Comparisons | Swaps |
|---:|---:|---|---:|---:|
| 1 | 45 | `[45]` | 0 | 0 |
| 2 | 72 | `[72, 45]` | 1 | 1 |
| 3 | 30 | `[72, 45, 30]` | 1 | 0 |
| 4 | 90 | `[90, 72, 30, 45]` | 2 | 2 |
| 5 | 65 | `[90, 72, 30, 45, 65]` | 1 | 0 |
| 6 | 50 | `[90, 72, 50, 45, 65, 30]` | 2 | 1 |
| 7 | 85 | `[90, 72, 85, 45, 65, 30, 50]` | 2 | 1 |

Totals for insertion: **9 parent comparisons, 5 swaps**. The final heap has
height 2 edges (3 levels), and severity **90** is at the root.

## Heap Sort trace

Heap Sort uses a max heap to place the current maximum at the end of the
active range. The suffix after the active heap is already sorted.

| Step | Heap / array state |
|---|---|
| Initial | `[45, 72, 30, 90, 65, 50, 85]` |
| Max heap built | `[90, 72, 85, 45, 65, 50, 30]` |
| Move max 90 to index 6; active heap size 6 | `[85, 72, 50, 45, 65, 30, 90]` |
| Move max 85 to index 5; active heap size 5 | `[72, 65, 50, 45, 30, 85, 90]` |
| Move max 72 to index 4; active heap size 4 | `[65, 45, 50, 30, 72, 85, 90]` |
| Move max 65 to index 3; active heap size 3 | `[50, 45, 30, 65, 72, 85, 90]` |
| Move max 50 to index 2; active heap size 2 | `[45, 30, 50, 65, 72, 85, 90]` |
| Move max 45 to index 1; active heap size 1 | `[30, 45, 50, 65, 72, 85, 90]` |
| Sorted output | `[30, 45, 50, 65, 72, 85, 90]` |

Measured total: **21 key comparisons, 18 non-self swaps**.

## Quick Sort trace

Quick Sort uses Lomuto partitioning with the last item in each active range as
the pivot. Each row records the array after placing that pivot in its final
position; the output prints the prefix ending at the active range's high
index.

| Partition range | Pivot | Pivot final index | Array state shown |
|---|---:|---:|---|
| `[0..6]` | 85 | 5 | `[45, 72, 30, 65, 50, 85, 90]` |
| `[0..4]` | 50 | 2 | `[45, 30, 50, 65, 72]` |
| `[0..1]` | 30 | 0 | `[30, 45]` |
| `[3..4]` | 72 | 4 | `[30, 45, 50, 65, 72]` |
| Sorted output | - | - | `[30, 45, 50, 65, 72, 85, 90]` |

Measured total: **12 pivot comparisons, 6 non-self swaps**.
