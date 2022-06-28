

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int v;
    int c;
    struct Node* next;
} node;

node* push(node* queque, int v, int c){
    node* n = (node*)malloc(sizeof(node)); 
    n->v = v;
    n->c = c;
    n->next = queque;
    return n;
}

node* pop(node* n){

    node* aux = n->next;
    free(n);
    return aux;
}

int min(node* queque, int** G2){
    node* aux = queque;
    int c = 0;
    if(aux!=NULL && aux->next!=NULL){
        //printf("%d, %d\n", aux->v, aux->next->v);
        c = G2[aux->v][aux->next->v];
        aux = aux->next;
    }
    while(aux!=NULL && aux->next!=NULL){
        int u = aux->v;
        aux = aux->next;
        int v = aux->v;
        if(c > G2[u][v]){
            c = G2[u][v];
        }
        
    }
    return c;
}

node* BFS(int** G, int** G2, int s, int t, int len){
    int parent[len];
    node* queque = NULL;
    for(int i=0; i<len; i++){
        parent[i] = -1;
    }
    parent[s] = s;
    queque = push(queque, s, 0);
    
    //printf("%d\n", queque->v);
    while (queque!=NULL){
        int v = queque->v;
        int c = queque->c;
        queque = pop(queque);
        if(v==t) break;
        for(int i=0; i<len; i++){
            if(G[v][i]){
                if(G2[v][i]>0 && parent[i]==-1){
                    parent[i]=v;
                    //printf("p[%d] = %d; ", i, v);
                    queque = push(queque, i, c+1);
                    
                }
            }
            /*
            else if(G2[i][v]){
                if(parent[i]==-1){
                    parent[i]=v;
                    //printf("p[%d] = %d; ", i, v);
                    queque = push(queque, i, c+1);
                    
                }
            }
            */
        }
        //printf("\n");
    }
    if(parent[t]==-1){
        return NULL;
    }
    
    node * P = NULL;
    int v=t;
    while(v!=s){
        P = push(P, v, v);
        v = parent[v];
    }
    P = push(P, parent[s], s);
    return P;
}

int EK(int ** G, int** G2, int len){
    int mflow = 0;
    node* P = BFS(G, G2, 0, len-1, len);
    while(P!=NULL && P->next!=NULL){
        int fp = min(P, G2);
        //printf(" fp = %d\n", fp);
        //if(fp == 0) break;
        while(P!=NULL && P->next!=NULL){
            int u = P->v;
            //printf("%d -> ", P->v);
            P = pop(P);
            int v = P->v;
            
            G2[u][v] = G2[u][v] -fp;
            G2[v][u] = G2[u][v] +fp;
            
            /*
            if(G[u][v] && !G2[u][v]){
                G[u][v] = (G[u][v] + 1)%2;
                //printf("%d -> %d = %d\n", u, v, G[u][v]);
                G2[u][v] = (G2[v][u] + 1)%2;
                //printf(" - %d -> %d = %d\n", u, v, G2[u][v]);
            }
            else if(G2[v][u] && !G[v][u]){
                G2[v][u] = (G2[v][u] + 1)%2;
                //printf("- %d -> %d = %d\n", u, v, G2[v][u]);
                G[v][u] = (G[u][v] + 1)%2;
                //printf("%d -> %d = %d\n", u, v, G[v][u]);
            }
            */
        }
        mflow = mflow + fp;
        //printf("%d\n", P->v);
        P = BFS(G, G2, 0, len-1, len);
    }
    return mflow;
}

int main()
{
    
    int m, n; 
    scanf("%d", &m);
    scanf(" %d", &n);
    int **G =(int**)malloc(m*sizeof(int*));
    int **G2 =(int**)malloc(m*sizeof(int*));
    for(int i =0; i<n; i++){
        G[i] = (int*)malloc(n*sizeof(int));
        G2[i] = (int*)malloc(n*sizeof(int));
        for(int j=0; j<n; j++){
            G[i][j] = 0;
            G2[i][j] = 0;
        }
    }
    
    for(int i=0; i<m; i++){
        int l, c;
        scanf("%d %d", &l, &c);
        G[l-1][c-1] = 1;
        G[c-1][l-1] = 1;
        G2[l-1][c-1] = 1;
        G2[c-1][l-1] = 1;
        //G2[l-1][c-1] = 1;
        //G[c-1][l-1] = 1;
    }
    
    printf("%d\n", EK(G, G2, n));
    
    return 0;
}

