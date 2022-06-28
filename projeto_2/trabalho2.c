#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int mod_abs(int a) {
    return a % 1000000007;
}

int mod_add(int a, int b) {
    return (mod_abs(a) + mod_abs(b)) % 1000000007;
}

int min(int a, int b){
    if(a<b)return a;
    return b;
}

int max(int a, int b){
    if(a>b)return a;
    return b;
}

int mod_mult(int a, int b) {

    a = mod_abs(a);
    b = mod_abs(b);

    unsigned long long int x = (unsigned long long int)a;
    x *= (unsigned long long int)b;
    x = x%1000000007;

    return (int)x;
}

int min_n(int h, int H) /* numero minimo de blocos para atingir a altura H */
{
    if(H<h) return 0;
    float x = (float)(H-h);
    x = x/(h-1);
    return 1 + (int)ceil(x);
}

int max_n(int h, int H){ /* numero maximo de blocos para atingir a altura H */
    if(H<h) return 0;
    return 1+ H-h;
}

int max_H(int n, int h){ /* altura maxima de um arco com n blocos */
    if(n==0) return 0;
    n = n + (n%2); // transformar em numero par;
    n = n/2;
    return h + (n-1)*(h-1);
}

int min_H(int n, int h){ /* altura minima de um arco com n blocos */
    if(n==0) return 0;
    n = n + (n%2); // transformar em numero par;
    n = n/2;
    return h + (n-1);
}

int max_H2(int n, int h){ /* altura maxima de um ramo com n blocos */
    return h + (n-1)*(h-1);
}

int min_H2(int n, int h){ /* altura minima de um ramo com n blocos */
    return h + (n-1);
}

void block_combinations_bu(  int n /*numero de blocos*/,
                             int h /*altura dos blocos*/,
                             int H /*altura da sala*/,
                             int** cash)
{

    cash[h-1][1-1]=1; // caso base

    for(int ni=2; ni<n; ni++){
        for(int hi=min_H2(ni, h); hi<=min(max_H2(ni, h), H) && ni>=min_n(h, hi) && n-ni+1>=min_n(h, hi); hi++){
            int count = 0;
            if( ni<=max_n(h,hi) /*nao podem sobrar blocos*/)
            {

                for(int i=1; i<h; i++) /*variar a altura compartilhada por blocos vizinhos*/
                {
                    if(ni-1<=max_n(h,hi-i)){
                        count = mod_abs(count + cash[hi-i-1][ni-1-1]);
                    }

                }

            }
            cash[hi-1][ni-1]=count;
        }
    }
}

int branch_combinations_bu(int n/*numero de blocos*/,
                           int h/*altura dos blocos*/,
                           int H/*altura da sala*/,
                           int** cash)
{
    int counter=0;
    int i = max(min_n(h, H), n-max_n(h, H)+1);

    if(max_H2(i, h)==H || i == 2){
        counter = mod_abs(cash[H-1][n-i+1-1]+counter);
        if(i==n-i+1){
            return counter;
        }
        i++;
    }
    else if(i == n-max_n(h, H)+1){
        counter = mod_abs(cash[H-1][i-1]+counter);
        if(i==n-i+1){
            return counter;
        }
        i++;
    }

    for(; i<n-i+1; i++)/*combinar ramos de tamanhos diferentes*/
    {
        /* combinacoes = conbinaoes do ramo esquerdo * combinacoes do ramo direito
                       + conbinaoes do ramo direito * combinacoes do ramo esquerdo

                      <=>

            combinacoes = conbinaoes do ramo esquerdo * combinacoes do ramo direito * 2 */
        counter = mod_abs(mod_mult(cash[H-1][i-1], cash[H-1][n-i+1-1]) + counter);
    }
    counter = mod_abs(counter*2);

    if(i==n-i+1) /*combinar ramos de tamanhos iguais*/
    {
        /* combinacoes = conbinaoes do ramo esquerdo * conbinaoes do ramo esquerdo */
        counter = mod_abs(mod_mult(cash[H-1][i-1], cash[H-1][i-1])+ counter);
    }
    return counter;
}

int** create_cash(int n, int h, int H){

    int** c = (int**)malloc(H*sizeof(int*));

    for(int i=0; i<H; i++){
        int N = min(n, max_n(h, i+1));
        if(n-min_n(h,i+1)+1>= min_n(h,i+1)) /*alocar memoria apenas para os casos validos*/
        {
            c[i] = (int*)malloc(N*sizeof(int));
        }
    }
    return c;
}

int main()
{

    int t, n, h, H;
    scanf("%d", &t);

    for(int i=0; i<t; i++){
        scanf("%d %d %d", &n, &h, &H);

        /* nao e preciso tratar os casos para alturas impossiveis de alcancar */
        H = min(H, max_H(n, h));
        /* nao e preciso tratar os casos para quantidades de blocos impossiveis de alcancar */
        n = min(n, max_n(h, H)*2-1);

        /* preencher a cash */
        int** cash = create_cash(n, h, H);
        block_combinations_bu(min(n, max_n(h, H)*2-1), h, H, cash);

        /* combinacoes = sum( cominacoes de arcos com j blocos e de altura i )*/
        int count =0;
        for(int i = min_H(3, h); i<=H; i++) /* variar a altura do arco */
        {
            for(int j = max(3, min_n(h, i)*2-1); j<= min(n, max_n(h, i)*2-1); j++) /* variar o numero de blocos usados */
            {
                count = mod_abs(branch_combinations_bu(j, h, i, cash)+ count);
            }
        }

        printf("%d\n", count);
    }

    return 0;
}


