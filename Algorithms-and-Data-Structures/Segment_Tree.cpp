const int MAXN = 1e6+5;

struct SegmentTree
{
    int L, R;
    int minv;
}node[MAXN << 2];

int A[MAXN], N;

void buildTree(int p, int L, int R)
{
    node[p].L = L;
    node[p].R = R;
    if(L == R)
    {
        node[p].minv = A[L];
        return;
    }
    int mid = (L+R)>>1;
    buildTree(p<<1, L, mid);
    buildTree(p<<1|1, mid+1, R);
    node[p].minv = min(node[p<<1].minv, node[p<<1|1].minv);
}

// update A[i] to v
void update(int p, int i, int v)
{
    if(node[p].L == node[p].R)
    {
        node[p].minv = v;
        return;
    }
    int mid = (node[p].L + node[p].R) >> 1;
    if(i > mid) update(p<<1|1, i, v);
    else update(p<<1, i, v);
    node[p].minv = min(node[p<<1].minv, node[p<<1|1].minv);
}

// find the minimum element in [L,R]
int query(int p, int L, int R)
{
    int ans, mid;
    if(node[p].L == L && node[p].R == R)
        return node[p].minv;
    mid = (node[p].L + node[p].R) >> 1;
    if(R <= mid) ans = query(p<<1, L, R);
    else if(L > mid) ans = query(p<<1|1, L, R);
    else ans = min(query(p<<1, L, mid), query(p<<1|1, mid+1, R));
    return ans;
}
