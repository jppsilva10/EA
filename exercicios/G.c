
#include <stdio.h>
#include <stdlib.h>

int best;
int** M;
int* neighbor;
int n;

void function(int i, int size){
    
    if(size>best) best = size;
    if(i==n) return;
    
    int ub = 0;
    for(int j=i+1; j<n; j++){
        if(neighbor[j]==0) ub += 1;
    }
    if(size + ub <=best) return;
    
    for(int j=i+1; j<n; j++){
        if(M[i][j]==1) neighbor[j]+=1;
    }
    for(int j=i+1; j<n; j++){
        if(neighbor[j]==0) function(j, size+1);
    }
    
    for(int j=i+1; j<n; j++){
        if(M[i][j]==1) neighbor[j]-=1;
    }
}

int main()
{
    
    int m; 
    scanf("%d %d", &n, &m);
    neighbor = (int*)malloc(n*sizeof(int));
    for(int i=0; i<n; i++){
        neighbor[i]=0;
    }
    
    M = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        M[i] = (int*)malloc(n*sizeof(int));
        for(int j=0; j<n; j++){
            M[i][j]=0;
        }
    }
    
    for(int i=0; i<m; i++){
        int l, c;
        scanf("%d %d", &l, &c);
        M[l][c]=1;
        M[c][l]=1;
    }
    
    best = 0; 
    
    for(int i=0; i<n; i++){
        function(i, 1);
    }    
    
    printf("%d\n", best);

    return 0;
}