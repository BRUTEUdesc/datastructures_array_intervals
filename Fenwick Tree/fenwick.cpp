vector<int> build_fenwick_tree(vector<int> v){
    int n = v.size();
    vector<int> ft(n, 0);
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j+=j&(-j))
            ft[j] += v[i];
    return ft;
}

int queryinterval(int a, int b, vector<int> &ft){
    if(a == 1) return query(b, ft);
    else return query(b, ft) - query(a-1, ft);
}

int query(int i, vector<int> &ft){
    if(i == 0) return 0;
    else return ft[i] + query(i - i&(-i));
}

void update(int i, vector<int> &ft, vector<int>& v, int x){
    for(int pos = i; pos < ft.size(); pos += pos&(-pos))
        ft[pos] = ft[pos]-v[i] + x;
    v[i] = x;
}
