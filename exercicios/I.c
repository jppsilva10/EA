#include <stdio.h>

int lower(int* pesos, int * bloqueados, int len){
    
    int peso = -1;
    int index= -1;
    for(int i=0; i<len; i++){
        if(pesos[i]!=-1 && !bloqueados[i]){
            if(peso==-1){
                peso = pesos[i];
                index = i;
            }
            else if(peso>pesos[i]){
                peso = pesos[i];
                index = i;
            }
        }
    }
    return index;
}

void step(int* pesos, int * bloqueados, int* ligacoes, int index, int len){
    for(int i = 0; i<len; i++){
        if(i!= index && ligacoes[i]!=-1 && !bloqueados[i]){
            if(pesos[i]==-1 || pesos[i]>pesos[index] + ligacoes[i]){
                pesos[i]=pesos[index] + ligacoes[i];
            }
        }
    }
    bloqueados[index]= 1;
}

int main()
{
    
    int N, end;
    
    scanf("%d %d", &N, &end);
    int ligacoes[N][N];
    int pesos[2][N];
    for(int i=0; i<N; i++){
        scanf("%d", &pesos[0][i]);
        pesos[0][i]=-1;
        pesos[1][i]=0;
        for(int j=0; j<N; j++){
            scanf(" %d", &ligacoes[i][j]);
            
        }
    }
    
    int index=0;
    pesos[0][index] = 0;
    pesos[1][index] = 1;
    
    while(index!=end-1){
        step(pesos[0], pesos[1], ligacoes[index], index, N);
        index = lower(pesos[0], pesos[1], N);
        
    }
    
    printf("%d\n", pesos[0][index]);

    return 0;
}
