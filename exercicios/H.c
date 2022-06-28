#include <stdio.h>
#include <stdlib.h>

int function(int index, int color, int* colors, int** conections, int len){
    if(colors[index]!=-1){
        if(colors[index]==color){
            return 1;
        }
        else{
            return 0;
        }
    }
    colors[index] = color;
    for(int i=0; i<len; i++ ){
        if(conections[index][i]){
            if(function(i, (color+1)%2, colors, conections, len)==0){
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    int n, c;
    while(scanf("%d %d", &n, &c)>0){
        int** conections = malloc(n*sizeof(int*));
        int colors[n];
        for(int i=0; i<n; i++){
            colors[i] = -1;
        }
        
        for(int i=0; i<n; i++){
            conections[i] = malloc(n*sizeof(int));
        }
        
        for(int i=0; i<c; i++){
            int L, C;
            scanf("%d %d", &L, &C);
            conections[L-1][C-1]=1;
            conections[C-1][L-1]=1;
        }
        if(function(0, 0, colors, conections, n)){
            printf("NOT SURE\n");
        }
        else{
            printf("NO\n");
        }
        free(conections);
    }

    return 0;
}
