struct nodo{
    int chave, prioridade, size;
    nodo *left, *right;
    nodo(int _chave){
        chave = _chave;
        prioridade = rand();
        left = right = size = 0;
    }
};

void update(nodo* &T){
    if(T != NULL){
        T->size = 1;
        T->maxi = T->chave;
        if(T->left != NULL){
            T->size += T->left->size;
            T->maxi = max(T->maxi, T->left->maxi);
        }
        if(T->right != NULL){
            T->size += T->right->size;
            T->maxi = max(T->maxi, T->right->maxi);
        }
    }
}

nodo* fundir(nodo* &esq, nodo* &dir){
    if(esq == NULL) return dir;
    if(dir == NULL) return esq;
    if(esq->prioridade > dir->prioridade){
        esq->right = fundir(esq->right, dir);
        update(esq);
        return esq;
    }
    else{
        dir->left = fundir(esq, dir->left);
        update(dir);
        return dir;
    }
}

pair<nodo*,nodo*> quebrar(nodo* &T, int x, int leftsize = 0){
    if(T == NULL) return {NULL, NULL};
    int total_left = T->left != NULL ? T->left->len : 0;
    int position = leftsize + total_left + 1;
    if(position < x){
        nodo *t1, *t2; tie(t1, t2) = quebrar(T->right, x, position);
        T->right = t1;
        update(T); update(t2);
        return {T, t2};
    } else {
        nodo *t1, *t2; tie(t1, t2) = quebrar(T->left, x, leftsize);
        T->left = t2;
        update(t1); update(T);
        return {t1, T};
    }
}

void inserir(nodo* &T, nodo* novo, int i){
    nodo *t1, *t2; tie(t1,t2) = quebrar(T, i);
    nodo *t11 = fundir(t1, novo);
    T = fundir(t11, t2);
}

void remover(nodo* &T, int i){
    nodo *t1, *t2; tie(t1,t2) = quebrar(T, i);
    nodo *t21, *t22 = quebrar(t2, 2);
    T = fundir(t1, t22);
}

void maximo_intervalo(nodo* &T, int a, int b){
    nodo *t1, *t2; tie(t1,t2) = quebrar(T, a);
    nodo *t21, *t22 = quebrar(t2, b-a+2);
    int x = t21->maxi;
    t2 = fundir(t21, t22);
    T = fundir(fundir(t1, t2));
}

/*

void update(nodo* &T){
    if(T != NULL){
        T->size = 1;
        if(T->left != NULL) T->size += T->left->size;
        if(T->right != NULL) T->size += T->right->size;
    }
}

This section contains the Treap without the Implicit expansion
nodo* fundir(nodo* &esq, nodo* &dir){
    if(esq == NULL) return dir;
    if(dir == NULL) return esq;
    if(esq->prioridade > dir->prioridade){
        esq->right = fundir(esq->right, dir);
        return esq;
    }
    else{
        dir->left = fundir(esq, dir->left);
        return dir;
    }
}

pair<nodo*,nodo*> quebrar(nodo* &T, int x){
    if(T == NULL) return {NULL, NULL};
    if(T->chave < x){
        nodo *t1, *t2; tie(t1, t2) = quebrar(T->right, x);
        T->right = t1;
        return {T, t2};
    } else {
        nodo *t1, *t2; tie(t1, t2) = quebrar(T->left, x);
        T->left = t2;
        return {t1, T};
    }
}

void inserir(nodo* &T, int x){
    nodo* u = new nodo(x);
    nodo *t1, *t2; tie(t1,t2) = quebrar(T, x);
    nodo *t11 = fundir(t1, u);
    T = fundir(t11, t2);
}

void remover(nodo* &T, int x){
    nodo *t1, *t2; tie(t1,t2) = quebrar(T, x);
    nodo *t21, *t22 = quebrar(t2, x+1);
    T = fundir(t1, t22);
}

*/
