vector< vector<int> > build_sparse_table(vector<int> v){
    int n = v.size(), m = log2(n) + 1;
    vector< vector<int> > ST(n, vector<int>(m, 0));
    for(int i = 1; i < v.size(); i++)
        ST[i][0] = v[i];
    for(int j = 1; j < m; j++)
        for(int i = 1; i+(1 << j) < v.size(); i++)
            ST[i][j] = max(ST[i][j-1], ST[i+(1 << (j-1))][j-1]);
    return ST;
}

int query_max(vector< vector<int> >& ST, int a, int b){
    int k = b-a+1, res = 0;
    int m = log2(k);
    for(int i = m; i >= 0; i--)
        if((1 << i)&k){
            res = max(res, ST[a][i]);
            a += (1 << i);
        }
    return res;
}
