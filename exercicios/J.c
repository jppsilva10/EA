
#include <stdio.h>
#include <stdlib.h>

int t;
int count;

int min(int a, int b){
    if(a<b) return a;
    return b;
}

void AP(int* low, int* dfs, int* parent, int* ap, int** lines, int len, int index){
    low[index] = t;
    dfs[index] = t;
    t = t+1;
    for(int i=0; i<len; i++){
        if(lines[index][i]){
            if(!dfs[i]){
                parent[i] = index;
                AP(low, dfs, parent, ap, lines, len, i);
                low[index] = min(low[index], low[i]);
                if(dfs[index]==1 && dfs[i]!=2){
                    if(!ap[index]){
                        ap[index] = 1;
                        count++;
                    }
                }
                if(dfs[index]!=1 && low[i]>=dfs[index]){
                    if(!ap[index]){
                        ap[index] = 1;
                        count++;
                    }
                }
            }
            else if(parent[index]!=i){
                low[index] = min(low[index], dfs[i]);
            }
        }
    }
    
}

int main()
{
    int N, i, n; 
    while(1){
        scanf("%d", &N);
        if(!N) break;
        t = 1;
        count =0;
        int** lines = malloc(N*sizeof(int*));
        int low[N];
        int dfs[N];
        int parent[N];
        int ap[N];
        for(int j=0; j<N; j++){
            lines[j]= malloc(N*sizeof(int));
           for(int k=0; k<N; k++){
                lines[j][k]=0;
            } 
            low[j]=0;
            dfs[j]=0;
            parent[j]=0;
            ap[j]=0;
        }
        while(1){
            char c;
            scanf("%d%c", &i, &c);
            if(!i) break;
            
            while(scanf("%d%c", &n, &c)>0){
                lines[i-1][n-1] = 1; 
                lines[n-1][i-1] = 1;
                if(c =='\n') break;
            }
        }
        /*
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                printf("%d ", lines[i][j]);
            }
            printf("\n");
        }
        */
        AP(low, dfs, parent, ap, lines, N, n);
        printf("%d\n", count);
        
    }

    return 0;
}
