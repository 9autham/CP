/* Second Minium Query */

#include <algorithm>
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
#define all(x) (x).begin(), (x).end()
using namespace std;

// Credits Priyansh
// Segment Tree with Point Updates and Range Queries
// Supports multiple Segment Trees with just a change in the Node and Update
// Very few changes required everytime

template<typename Node, typename Update>
struct SegTree {
	vector<Node> tree;
	vector<ll> arr; // type may change
	int n;
	int s;
	SegTree(int a_len, vector<ll> &a) { // change if type updated
		arr = a;
		n = a_len;
		s = 1;
		while(s < 2 * n){
			s = s << 1;
		}
		tree.resize(s); fill(all(tree), Node()); // Construction of SegTree with Node dataType
		build(0, n - 1, 1);
	}
	void build(int start, int end, int index)  // Never change this
	{
		if (start == end)	{
			tree[index] = Node(arr[start]);
			return;
		}
		int mid = (start + end) / 2;
		build(start, mid, 2 * index);
		build(mid + 1, end, 2 * index + 1);
		tree[index].merge(tree[2 * index], tree[2 * index + 1]);
	}
	void update(int start, int end, int index, int query_index, Update &u)  // Never Change this
	{
		if (start == end) {
			u.apply(tree[index]);
			return;
		}
		int mid = (start + end) / 2;
		if (mid >= query_index)
			update(start, mid, 2 * index, query_index, u);
		else
			update(mid + 1, end, 2 * index + 1, query_index, u);
		tree[index].merge(tree[2 * index], tree[2 * index + 1]);
	}
	Node query(int start, int end, int index, int left, int right) { // Never change this
		if (start > right || end < left)
			return Node();
		if (start >= left && end <= right)
			return tree[index];
		int mid = (start + end) / 2;
		Node l, r, ans;
		l = query(start, mid, 2 * index, left, right);
		r = query(mid + 1, end, 2 * index + 1, left, right);
		ans.merge(l, r);
		return ans;
	}
	void make_update(int index, ll val) {  // pass in as many parameters as required
		//Here in this problem onlly index and the value to replaced at this index is passed as parameter
		Update new_update = Update(val); // may change 
		// new_update is a Update DataStructure which can store all the values you need to update here only value at partucular index
		update(0, n - 1, 1, index, new_update);
	}
	Node make_query(int left, int right) {
		return query(0, n - 1, 1, left, right);
	}
};

struct Node1 {
	ll firstMin; // may change because the Segment Tree Data Type is Node 
	ll secondMin;
	Node1() { // Identity element or Default
		firstMin = INF;	// may change
		secondMin = INF;
	}
	Node1(ll p1) {  // Actual Node - ChildNode
		firstMin = p1; // may change
		secondMin = INF;
	}
	void merge(Node1 &l, Node1 &r) { // Merge two child nodes
		// Here left child + right child // may change
		if(l.firstMin>r.firstMin){
			firstMin = r.firstMin;
			secondMin = min(r.secondMin,l.firstMin);
		}
		else{
			firstMin = l.firstMin;
			secondMin = min(l.secondMin,r.firstMin);
		}
	}
};

struct Update1 {
	ll val; // may change
	Update1(ll p1) { // Actual Update
		val = p1; // may change
	}
	void apply(Node1 &a) { // apply update to given node
	// u.apply(Node) You have to update Node(PassByRef) with elements in Update
	// Here 'Node a' value is update by val
		a.firstMin = val; // may change
	}
};

int main(){
    int n;
    cin>>n;
    vector<ll>arr(n);
    for(auto &i:arr)cin>>i;
    SegTree<Node1,Update1> sgt= SegTree<Node1,Update1>(n,arr);
    int q;cin>>q;
    while(q--){
        int type;cin>>type;
        if(type==1){
            // update
            int pos,val;
            cin>>pos>>val;
            sgt.make_update(pos,val);
        }
        else{
            int l,r;
            cin>>l>>r;
            Node1 ans= sgt.make_query(l,r);
            cout<<ans.secondMin<<endl;
        }
    }
}
