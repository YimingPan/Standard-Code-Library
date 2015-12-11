const int MAXN = 100005;

struct SegmentTree
{
    int L, R;
    int sum, lazy;
}node[MAXN*4];

int A[MAXN];

void buildTree(int p, int L, int R)
{
    node[p].L = L;
    node[p].R = R;
    node[p].lazy = -1;
    if(L == R)
    {
        node[p].sum = A[L];
        return;
    }
    int mid = (L+R)/2;
    buildTree(p<<1, L, mid);
    buildTree(p<<1|1, mid+1, R);
    node[p].sum = node[p<<1].sum + node[p<<1|1].sum;
}

void push_down(int p)
{
    node[p<<1].lazy = node[p].lazy;
    node[p<<1].sum = node[p].lazy * (node[p<<1].R-node[p<<1].L+1);
    node[p<<1|1].lazy = node[p].lazy;
    node[p<<1|1].sum = node[p].lazy * (node[p<<1|1].R-node[p<<1|1].L+1);
    node[p].lazy = -1;
}

void update(int p, int L, int R, int v)
{
    if(node[p].L == L && node[p].R == R)
    {
        node[p].sum = (R-L+1) * v;
        node[p].lazy = v;
        return;
    }
    int mid = (node[p].L + node[p].R)/2;
    if(node[p].lazy != -1) push_down(p);
    if(R <= mid) update(p<<1, L, R, v);
    else if(L > mid) update(p<<1|1, L, R, v);
    else
    {
        update(p<<1, L, mid, v);
        update(p<<1|1, mid+1, R, v);
    }
    node[p].sum = node[p<<1].sum + node[p<<1|1].sum;
}

int query(int p, int L, int R)
{
    int mid, ans;
    if(node[p].L == L && node[p].R == R)
        return node[p].sum;
    mid = (node[p].L + node[p].R)/2;
    if(node[p].lazy != -1) push_down(p);
    if(R <= mid) ans = query(p<<1, L, R);
    else if(L > mid) ans = query(p<<1|1, L, R);
    else ans = query(p<<1, L, mid) + query(p<<1|1, mid+1, R);
    return ans;
}
