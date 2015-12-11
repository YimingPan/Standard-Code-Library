const int MAXN = 1e6+3;

int ST[MAXN][21];

void init(int N)
{
    for(int j=1; (1<<j) <= N; j++)
        for(int i=1; i+(1<<j)-1 <= N; i++)
            ST[i][j] = min(ST[i][j-1], ST[ i+(1<<(j-1)) ][j-1]);
}

// return minimum element in [L,R]
int query(int L, int R)
{
    int len = R-L+1, k = 0;
    while( 1<<(k+1) <= len ) k++;
    return min(ST[L][k], ST[ R-(1<<k)+1 ][k]);
}
