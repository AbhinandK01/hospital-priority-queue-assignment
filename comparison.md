# Comparison and Conclusion

## Results on the given severity scores

| Method | Heap structure / height | Comparisons observed | Swaps observed | Space | Suitability for live patient queue |
|---|---|---:|---:|---|---|
| Max Heap insertion | Complete binary tree; height 2 edges / 3 levels for 7 values | 9 | 5 | O(n) total heap storage | **Best fit**: root is highest severity, peek O(1), insert O(log n), remove-max O(log n) |
| Heap Sort | Builds a complete max heap of height 2 before extracting maxima | 21 | 18 | O(1) auxiliary in-place | Good predictable batch sort, not a continuously updated queue on its own |
| Quick Sort | No heap structure; partitions around a pivot | 12 | 6 | O(log n) average stack; O(n) worst | Good average batch sorting performance; not a priority queue |

The measured counts are for these specific input values and the precise
implementations described in the source. They should not be treated as
universal performance guarantees. Both sorting programs output ascending
severity scores, so the most severe score appears last in the sorted result.
For the heap insertion count, each comparison against a parent is counted,
including the final comparison that stops an upward sift. Swaps count only
exchanges between different array positions.

## Conclusion

Use a **max heap** to manage arrivals and retrieve the patient with the
highest severity score immediately. Its root gives O(1) access to the current
highest-priority patient. Each arrival can be inserted in O(log n), and after
treating/removing the most severe patient, the next one can be restored to the
root in O(log n). Heap Sort and Quick Sort solve the different task of sorting
a fixed batch; they do not efficiently preserve live priority-queue behavior
after every insertion.
