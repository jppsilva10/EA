#include <stdio.h>
#include <stdlib.h>

int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


int function(int* objects, int len, int m){
    qsort(objects, len, sizeof(int), cmp);
    int position = objects[0] + m;
    int i = 1;
    for(int j=1; j<len; j++){
        if(objects[j]<=position + m) continue;
        else{
            position = objects[j] + m;
            i++;
        }
    }
    return i;
}

int main()
{
    int len, M, N;
    
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d %d", &len, &M);
        int obj[len];
        for(int j=0; j<len; j++){
            scanf("%d", &obj[j]);
        }
        printf("%d\n", function(obj, len, M));
    }

    return 0;
}