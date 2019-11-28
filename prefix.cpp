vector<int> build_prefix(vector<int> V){
    vector<int> P(V.size(), 0);
    P[1] = V[1];
    for(int i = 2; i < V.size(); i++)
        P[i] = P[i-1] + V[i];
    return P;
}

int query_sum(int a, int b, vector<int>& P){
    if(a == 1) return P[b];
    else return P[b] - P[a-1];
}
