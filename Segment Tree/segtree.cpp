void push(int u, int L, int R, vector<int>& lazy, vector<int>& T){
    if(lazy[u] != 0){
        T[u] = lazy[u];
        if(L != R){
            lazy[2*u] = lazy[u];
            lazy[2*u+1] = lazy[u];
        }
        lazy[u] = 0;
    }
}

int query(int u, int L, int R, int i, int j, vector<int>& lazy, vector<int>& T){
    push(u, L, R, lazy, T);
    if(R > i or j < L) return 0;
    if(L >= i and R <= j) return T[u];
    else{
        int mid = (L+R)/2;
        int esq = query(2*u, L, mid, i, j, lazy, T);
        int dir = query(2*u+1, mid+1, R, i, j, lazy, T);
        return max(esq, dir);
    }
}

int update(int u, int L, int R, int i, int j, int x, vector<int>& lazy, vector<int>& T){
    push(u, L, R, lazy, T);
    if(R > i or j < L) return T[u];
    if(L >= i and R <= j){
        lazy[u] = x;
        push(u, L, R, lazy, T);
        return T[u];
    }
    else{
        int mid = (L+R)/2;
        int esq = update(2*u, L, mid, i, j, x, lazy, T);
        int dir = update(2*u+1, mid+1, R, i, j, x, lazy, T);
        return max(esq, dir);
    }
}

/*
This section contains the Segment Tree without Lazy Propagation

int build_segment_tree(int u, int L, int R, vector<int>& V, vector<int>& T){
    if(L == R)
        return T[u] = v[L];
    else{
        int mid = (L+R)/2;
        int esq = build_segment_tree(2*u, L, mid, V, T);
        int dir = build_segment_tree(2*u+1, mid+1, R, V, T);
        return T[u] = max(esq, dir);
    }
}

int query(int u, int L, int R, int i, int j, vector<int>& T){
    if(R > i or j < L) return 0;
    if(L >= i and R <= j) return T[u];
    else{
        int mid = (L+R)/2;
        int esq = query(2*u, L, mid, i, j, T);
        int dir = query(2*u+1, mid+1, R, i, j, T);
        return max(esq, dir);
    }
}

int update(int u, int L, int R, int pos, int x, vector<int>& T){
    if(pos > R or pos < L) return T[u];
    if(L == R) return T[u] = x;
    else{
        int mid = (L+R)/2;
        int esq = update(2*u, L, mid, pos, x, T);
        int dir = update(2*u+1, mid, R, pos, x, T);
        return T[u] = max(esq, dir);
    }
}

*/
