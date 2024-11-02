/*
Problem Statement : You have 2 operations to be done 
                        1. Update at element at pos to val
                        2. Query the min from l to r

Three things to keep in mind
    1. Data - What to store in a segment tree nodes
    2. Merge - How to evaluate the answer using left and right 
    3. Default - What to return from a node so that answer is ignored (Here returing 1e9 in query function)
*/
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
vector<int>sgt;
vector<int>arr;
int mergeNodes(int left, int right){
    return min(left,right); // Merge
}
void build(int index, int start,int end) {
    if(start == end) {
        // leaf node
        sgt[index]=arr[start];
        return;
    }
    int mid = (start + end)/2;
    build(2*index, start, mid);
    build(2*index+1, mid+1, end);
    sgt[index]=mergeNodes(sgt[2*index],sgt[2*index+1]);
}
void update(int index, int start, int end, int pos, int val){
    if(start==end){
        arr[pos]=val;
        sgt[index]=arr[pos];
        return;
    }
    int mid=(start+end)/2;
    if(pos<=mid){
        update(2*index,start,mid,pos,val);
    }
    else{
        update(2*index+1, mid+1, end, pos, val);
    }
    sgt[index]=mergeNodes(sgt[2*index],sgt[2*index+1]);
}
int  query(int index, int start, int end, int l, int r){
    if(start>=l && end<=r){
        // all elements of l and r are in the range // Full Intersection
        return sgt[index];
    }
    else if(start>r || end<l){
        // Disjoint - No intersection
        return 1e9; // Default value
    }
    else{
        int mid = (start+end)/2;
        int leftAns=query(2*index, start, mid,l,r);
        int rightAns=query(2*index+1, mid+1, end, l, r);
        return mergeNodes(leftAns,rightAns);
    }
}
int32_t main() {
    int n;
    cin>>n;
    arr.resize(n);
    for(auto &i : arr)cin>>i;
    sgt.resize(4*n);
    build(1,0,n-1);
    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            // Update at position-pos and val-x 0 indexed
            int pos,x;
            cin>>pos>>x;
            update(1,0,n-1,pos,x);
        }
        else{
            // query 0 indexed
            int l,r;
            cin>>l>>r;
            cout<<query(1,0,n-1,l,r)<<endl;
        }
    }
    return 0;
}