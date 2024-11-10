/*

Lazy Propagation - Sum Query + Add val from l-r
Problem Statement : You have 2 operations to be done 
                    1. Add all the elements elements at l - r to val
                    2. Query the first number in l and r which is greater than X


*/

#include <bits/stdc++.h>
using namespace std;

vector<int> sgt;   // Segment tree
vector<int> lazy;  // Lazy array
vector<int> arr;   // Original array

// Merges two nodes (can be modified based on the problem requirement)
int mergeNodes(int left, int right) {
    return left + right;
}

// Push the lazy updates down the tree
void push(int index, int start, int end) {
    // This method will change
    if (lazy[index] != 0) {
        // Apply the lazy update to the segment tree node
        sgt[index] += lazy[index] * (end - start + 1); // Modify based on range sum
        if (start != end) { // If not a leaf node, propagate to children
            lazy[2 * index] += lazy[index];
            lazy[2 * index + 1] += lazy[index];
        }
        lazy[index] = 0; // Clear the lazy value after pushing
    }
}

// Build the segment tree
void build(int index, int start, int end) {
    if (start == end) {
        // Leaf node
        sgt[index] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * index, start, mid);
    build(2 * index + 1, mid + 1, end);
    sgt[index] = mergeNodes(sgt[2 * index], sgt[2 * index + 1]);
}

// Range update with lazy propagation
void update(int index, int start, int end, int l, int r, int val) {
    push(index, start, end); // Ensure any pending updates are applied
    if (start > r || end < l) {
        return; // No overlap
    }
    if (start >= l && end <= r) {
        // Full overlap
        lazy[index] += val;
        push(index, start, end);
        return; // Should return
    }
    // Partial overlap
    int mid = (start + end) / 2;
    update(2 * index, start, mid, l, r, val);
    update(2 * index + 1, mid + 1, end, l, r, val);
    sgt[index] = mergeNodes(sgt[2 * index], sgt[2 * index + 1]);
}

// Range query with lazy propagation
int query(int index, int start, int end, int l, int r) {
    push(index, start, end); // Ensure any pending updates are applied
    if (start > r || end < l) {
        return 0; // No overlap, return the default value (0 for sum)
    }
    if (start >= l && end <= r) {
        // Full overlap
        return sgt[index];
    }
    // Partial overlap
    int mid = (start + end) / 2;
    int leftAns = query(2 * index, start, mid, l, r);
    int rightAns = query(2 * index + 1, mid + 1, end, l, r);
    return mergeNodes(leftAns, rightAns);
}

int32_t main() {
    int n;
    cin >> n;
    arr.resize(n);
    for (auto &i : arr) cin >> i;

    sgt.resize(4 * n);
    lazy.resize(4 * n, 0); // Initialize lazy array with 0

    build(1, 0, n - 1);

    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            // Range update: Add `val` to elements from `l` to `r`
            int l, r, val;
            cin >> l >> r >> val;
            update(1, 0, n - 1, l, r, val);
        } else {
            // Range query: Sum of elements from `l` to `r`
            int l, r;
            cin >> l >> r;
            cout << query(1, 0, n - 1, l, r) << endl;
        }
    }
    return 0;
}
