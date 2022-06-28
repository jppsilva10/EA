#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Resposta;
//int nos=0;
int copy = 1; 

int Down(int** array, int len, int* CanMerge, int* Changes, int* Copy){
    int pointer;
    int Colisions=0;
    int comp = -1;
    int desalinhado = 0;
    
    for(int c = 0; c < len; c++){
        pointer = len-1;
        for(int l = len-2; l>= 0; l--){
            if (array[l][c] == 0){
                continue;
            }
            if (array[pointer][c] == 0){
                (*Changes)++;
                array[pointer][c] = array[l][c];
                array[l][c] = 0;
                if(pointer<len-1){
                    if(array[pointer][c] == array[pointer+1][c]){
                        (*CanMerge)++;
                    }
                }
            }
            else{
                if (array[pointer][c] == array[l][c]){
                    (*Changes)++;
                    array[pointer][c] *= 2;
                    array[l][c] = 0; 
                    Colisions++;
                    if(pointer<len-1){
                        if(array[pointer][c] == array[pointer+1][c]){
                            (*CanMerge)++;
                        }
                    }
                }
                pointer--;
                if (array[pointer][c] == 0){
                    (*Changes)++;
                    array[pointer][c] = array[l][c];
                    array[l][c] = 0;
                }
            } 
        }
        if(!desalinhado){
            if(array[pointer][c] == 0) pointer+=1;
            if(pointer!=len){
                if(comp == -1) comp = pointer;
                else{
                    if(comp - pointer) desalinhado++;
                }
            }
        }
    }

    if(!(*Changes)) *Copy = 0;
    if((*Changes) && !Colisions)(*Changes) = desalinhado;
    //printf("CanMerge: %d\n", *CanMerge);
    //printf("Changes: %d\n", *Changes);
    return Colisions;
}

int Up(int** array, int len, int* CanMerge, int* Changes, int* Copy){
    int pointer;
    int Colisions=0;
    int comp = -1;
    int desalinhado = 0;
    
    for(int c = 0; c < len; c++){
        pointer = 0;
        for(int l = 1; l < len; l++){
            if (array[l][c] == 0){
                continue;
            }
            if (array[pointer][c] == 0){
                (*Changes)++;
                array[pointer][c] = array[l][c];
                array[l][c] = 0;
                if(pointer>0){
                    if(array[pointer][c] == array[pointer-1][c]){
                        (*CanMerge)++;
                    }
                }
            }
            else{
                if (array[pointer][c] == array[l][c]){
                    (*Changes)++;
                    array[pointer][c] *= 2;
                    array[l][c] = 0; 
                    Colisions++;
                    if(pointer>0){
                        if(array[pointer][c] == array[pointer-1][c]){
                            (*CanMerge)++;
                        }
                    }
                }
                pointer++;
                if(array[pointer][c] == 0){
                    (*Changes)++;
                    array[pointer][c] = array[l][c];
                    array[l][c] = 0;
                }
            } 
            
        }
        if(!desalinhado){
            if(array[pointer][c] == 0) pointer-=1;
            if(pointer!=-1){
            if(comp == -1) comp = pointer;
                else{
                    if(comp - pointer) desalinhado++;
                }
            }
        }
    }

    if(!(*Changes)) *Copy = 0;
    if((*Changes) && !Colisions)(*Changes) = desalinhado;
    return Colisions;
}

int Left(int** array, int len, int* CanMerge, int* Changes, int* Copy){
    int pointer;
    int Colisions=0;
    int comp = -1;
    int desalinhado = 0;
    
    for(int l = 0; l < len; l++){
        pointer = 0;
        for(int c = 1; c < len; c++){
            if (array[l][c] == 0){
                continue;
            }
            if (array[l][pointer] == 0){
                (*Changes)++;
                array[l][pointer] = array[l][c];
                array[l][c] = 0; 
                if(pointer>0){
                    if(array[l][pointer] == array[l][pointer-1]){
                        (*CanMerge)++;
                    }
                }
            }
            else{
                if (array[l][pointer] == array[l][c]){
                    (*Changes)++;
                    array[l][pointer] *= 2;
                    array[l][c] = 0; 
                    Colisions++;
                    if(pointer>0){
                        if(array[l][pointer] == array[l][pointer-1]){
                            (*CanMerge)++;
                        }
                    }
                }
                pointer++;
                if (array[l][pointer] == 0){
                    (*Changes)++;
                    array[l][pointer] = array[l][c];
                    array[l][c] = 0; 
                }
            } 
        }
        if(!desalinhado){
            if(array[l][pointer] == 0) pointer-=1;
            if(pointer!=-1){
                if(comp == -1) comp = pointer;
                else{
                    if(comp - pointer) desalinhado++;
                }
            }
        }
    }

    if(!(*Changes)) *Copy = 0;
    if((*Changes) && !Colisions)(*Changes) = desalinhado;
    return Colisions;
}

int Right(int** array, int len, int* CanMerge, int* Changes, int* Copy){
    int pointer;
    int Colisions=0;
    int comp = -1;
    int desalinhado = 0;
    
    for(int l = 0; l < len; l++){
        pointer = len-1;
        for(int c = len-2; c >=0; c--){
            if (array[l][c] == 0){
                continue;
            }
            if (array[l][pointer] == 0){
                (*Changes)++;
                array[l][pointer] = array[l][c];
                array[l][c] = 0; 
                if(pointer<len-1){
                    if(array[l][pointer] == array[l][pointer+1]){
                        (*CanMerge)++;
                    }
                }
            }
            else{
                if (array[l][pointer] == array[l][c]){
                    (*Changes)++;
                    array[l][pointer] *= 2;
                    array[l][c] = 0; 
                    Colisions++;
                    if(pointer<len-1){
                        if(array[l][pointer] == array[l][pointer+1]){
                            (*CanMerge)++;
                        }
                    }
                }
                pointer--;
                if (array[l][pointer] == 0){
                    (*Changes)++;
                    array[l][pointer] = array[l][c];
                    array[l][c] = 0;
                }
            } 
        }
        if(!desalinhado){
            if(array[l][pointer] == 0) pointer+=1;
            if(pointer!=len){
                if(comp == -1) comp = pointer;
                else{
                    if(comp - pointer) desalinhado++;
                }
            }
        }
    }
    if(!(*Changes)) *Copy = 0;
    if((*Changes) && !Colisions)(*Changes) = desalinhado;
    return Colisions;
}


int Down2(int** array, int len, int* CanMerge, int* Changes, int* Copy){
    int pointer;
    int Colisions=0;
    
    for(int c = 0; c < len; c++){
        pointer = len-1;
        for(int l = len-2; l>= 0; l--){
            if (array[l][c] == 0){
                continue;
            }
            if (array[pointer][c] == 0){
                (*Changes)++;
                array[pointer][c] = array[l][c];
                array[l][c] = 0;
                if(pointer<len-1){
                    if(array[pointer][c] == array[pointer+1][c]){
                        (*CanMerge)++;
                    }
                }
            }
            else{
                if (array[pointer][c] == array[l][c]){
                    (*Changes)++;
                    array[pointer][c] *= 2;
                    array[l][c] = 0; 
                    Colisions++;
                    if(pointer<len-1){
                        if(array[pointer][c] == array[pointer+1][c]){
                            (*CanMerge)++;
                        }
                    }
                }
                pointer--;
                if (array[pointer][c] == 0){
                    (*Changes)++;
                    array[pointer][c] = array[l][c];
                    array[l][c] = 0;
                }
            } 
        }
    }
    if(!(*Changes)) *Copy = 0;
    //printf("CanMerge: %d\n", *CanMerge);
    //printf("Changes: %d\n", *Changes);
    return Colisions;
}

int Up2(int** array, int len, int* CanMerge, int* Changes, int* Copy){
    int pointer;
    int Colisions=0;
    
    for(int c = 0; c < len; c++){
        pointer = 0;
        for(int l = 1; l < len; l++){
            if (array[l][c] == 0){
                continue;
            }
            if (array[pointer][c] == 0){
                (*Changes)++;
                array[pointer][c] = array[l][c];
                array[l][c] = 0;
                if(pointer>0){
                    if(array[pointer][c] == array[pointer-1][c]){
                        (*CanMerge)++;
                    }
                }
            }
            else{
                if (array[pointer][c] == array[l][c]){
                    (*Changes)++;
                    array[pointer][c] *= 2;
                    array[l][c] = 0; 
                    Colisions++;
                    if(pointer>0){
                        if(array[pointer][c] == array[pointer-1][c]){
                            (*CanMerge)++;
                        }
                    }
                }
                pointer++;
                if(array[pointer][c] == 0){
                    (*Changes)++;
                    array[pointer][c] = array[l][c];
                    array[l][c] = 0;
                }
            } 
            
        }
    }

    if(!(*Changes)) *Copy = 0;
    return Colisions;
}

int Left2(int** array, int len, int* CanMerge, int* Changes, int* Copy){
    int pointer;
    int Colisions=0;
    
    for(int l = 0; l < len; l++){
        pointer = 0;
        for(int c = 1; c < len; c++){
            if (array[l][c] == 0){
                continue;
            }
            if (array[l][pointer] == 0){
                (*Changes)++;
                array[l][pointer] = array[l][c];
                array[l][c] = 0; 
                if(pointer>0){
                    if(array[l][pointer] == array[l][pointer-1]){
                        (*CanMerge)++;
                    }
                }
            }
            else{
                if (array[l][pointer] == array[l][c]){
                    (*Changes)++;
                    array[l][pointer] *= 2;
                    array[l][c] = 0; 
                    Colisions++;
                    if(pointer>0){
                        if(array[l][pointer] == array[l][pointer-1]){
                            (*CanMerge)++;
                        }
                    }
                }
                pointer++;
                if (array[l][pointer] == 0){
                    (*Changes)++;
                    array[l][pointer] = array[l][c];
                    array[l][c] = 0; 
                }
            } 
        }
    }

    if(!(*Changes)) *Copy = 0;
    return Colisions;
}

int Right2(int** array, int len, int* CanMerge, int* Changes, int* Copy){
    int pointer;
    int Colisions=0;
    
    for(int l = 0; l < len; l++){
        pointer = len-1;
        for(int c = len-2; c >=0; c--){
            if (array[l][c] == 0){
                continue;
            }
            if (array[l][pointer] == 0){
                (*Changes)++;
                array[l][pointer] = array[l][c];
                array[l][c] = 0; 
                if(pointer<len-1){
                    if(array[l][pointer] == array[l][pointer+1]){
                        (*CanMerge)++;
                    }
                }
            }
            else{
                if (array[l][pointer] == array[l][c]){
                    (*Changes)++;
                    array[l][pointer] *= 2;
                    array[l][c] = 0; 
                    Colisions++;
                    if(pointer<len-1){
                        if(array[l][pointer] == array[l][pointer+1]){
                            (*CanMerge)++;
                        }
                    }
                }
                pointer--;
                if (array[l][pointer] == 0){
                    (*Changes)++;
                    array[l][pointer] = array[l][c];
                    array[l][c] = 0;
                }
            } 
        }
    }
    if(!(*Changes)) *Copy = 0;
    return Colisions;
}


void print(int** array, int len){
    for(int l = 0; l < len; l++){
        for (int c = 0; c < len; c++){
            printf("%d ", array[l][c]);
        }
        printf("\n");
    }
    printf("\n");
}

int ** createArray(int len){
    int** array;
    array = (int**) malloc (len * sizeof(int*));
    
    for(int i = 0; i < len; i++){
        array[i] = (int*) malloc(len * sizeof(int));
    }
    return array;
}

int setValue(int** array, int len){
    int Value = 0;
    int total = 0;
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            if(array[i][j]){
                Value++;
                total+= array[i][j];
            }
        }
    }
    
    float x = log10(total)/log10(2);
    if ( x - (int)x ) return -1;
    return Value;
}

void dup(int** copy, int** src, int len){
    for(int i=0; i<len; i++){
        for (int j=0; j<len; j++){
            copy[i][j]=src[i][j];
        }
    }
}

void function(int ** array, int len, int moves, int value, int estadoD, int estadoU, int estadoL, int estadoR);

void function2(int ** array, int len, int moves, int value, int estadoD, int estadoU, int estadoL, int estadoR){
    //nos++;
    
    int** backUp = createArray(len);
    int x;
    int CanMerge = 0;
    int Changes = 0;
    int Copy = 1;
    
    int min = moves + ceil(log10(value)/log10(2));
    
    
    if(estadoD){
        
        dup(backUp, array, len);
        x = value-Down2(backUp, len, &CanMerge, &Changes, &Copy);
        
        if(moves+1 + ceil(log10(x)/log10(2)) < Resposta){//cortar a recurção
        
            if(!(x-1)){
                Resposta = moves+1;
                //printf("encontrei: %d--------------------------------\n", Resposta);
                free(backUp);
                return; 
            }
        
        
            if(Changes){ // houve alterações notabuleiro
                if(value-x){// houve merge
                    if(CanMerge){ // ainda há possiveis merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 1); 
                    }
                    else{ // não é possivel fazer mais merges
                        function(backUp, len, moves+1, x, 0, 1, 1, 1); 
                    }
                }
                else{
                    function(backUp, len, moves+1, x, 0, 0, 1, 1);
                    // corta-se o up, caso contrio anulavamos o down
                }
                if(min >= Resposta){ // cortar ramificação
                    free(backUp);
                    return; 
                }
            }
            else{// não houve alterações no tabuleiro
                // não se dá continuidade
            }
        }
    
    }
    
    if(estadoL){
        CanMerge = 0;
        Changes = 0;
        
        if(Copy){ 
            dup(backUp, array, len);
        }
        else{
            Copy=1;
        }
        x = value-Left2(backUp, len, &CanMerge, &Changes, &Copy);
        
        if(moves+1 + ceil(log10(x)/log10(2)) < Resposta){//cortar a recurção
        
            if(!(x-1)){
                Resposta = moves+1;
                //printf("encontrei: %d--------------------------------\n", Resposta);
                free(backUp);
                return; 
            }
            
            
            if(Changes){ // houve alterações notabuleiro
                if(value-x){// houve merge
                    if(CanMerge){ // ainda há possiveis merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 1); 
                    }
                    else{ // não é possivel fazer mais merges
                        function(backUp, len, moves+1, x, 1, 1, 0, 1); 
                    }
                }
                else{
                    function(backUp, len, moves+1, x, 1, 1, 0, 0);
                    // corta-se o up, caso contrio anulavamos o down
                }
                if(min >= Resposta){ // cortar ramificação
                    free(backUp);
                    return; 
                }
            }
            else{// não houve alterações no tabuleiro
                // não se dá continuidade
            }
        }
    
    }
    
    if(estadoU){
        CanMerge = 0;
        Changes = 0;
        
        if(Copy){ 
            dup(backUp, array, len);
        }
        else{
            Copy=1;
        }
        x = value-Up2(backUp, len, &CanMerge, &Changes, &Copy);
        
        if(moves+1 + ceil(log10(x)/log10(2)) < Resposta){//cortar a recurção
        
            if(!(x-1)){
                Resposta = moves+1;
                //printf("encontrei: %d--------------------------------\n", Resposta);
                free(backUp);
                return; 
            }
            
            
            if(Changes){ // houve alterações notabuleiro
                if(value-x){// houve merge
                    if(CanMerge){ // ainda há possiveis merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 1); 
                    }
                    else{ // não é possivel fazer mais merges
                        function(backUp, len, moves+1, x, 1, 0, 1, 1); 
                    }
                }
                else{
                    function(backUp, len, moves+1, x, 0, 0, 1, 1);
                    // corta-se o up, caso contrio anulavamos o down
                }
                if(min >= Resposta){ // cortar ramificação
                    free(backUp);
                    return; 
                }
            }
            else{// não houve alterações no tabuleiro
                // não se dá continuidade
            }
        }
    
    }
    
    if(estadoR){
        CanMerge = 0;
        Changes = 0;
        
        if(Copy){ 
            dup(backUp, array, len);
        }
        else{
            Copy=1;
        }
        x = value-Right2(backUp, len, &CanMerge, &Changes, &Copy);
        
        if(moves+1 + ceil(log10(x)/log10(2)) < Resposta){ //cortar a recurção
        
            if(!(x-1)){
                Resposta = moves+1;
                //printf("encontrei: %d--------------------------------\n", Resposta);
                free(backUp);
                return; 
            }
            
            if(Changes){ // houve alterações notabuleiro
                if(value-x){// houve merge
                    if(CanMerge){ // ainda há possiveis merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 1); 
                    }
                    else{ // não é possivel fazer mais merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 0); 
                    }
                }
                else{
                    function(backUp, len, moves+1, x, 1, 1, 0, 0);
                    // corta-se o up, caso contrio anulavamos o down
                }
                if(min >= Resposta){ // cortar ramificação
                    free(backUp);
                    return; 
                }
            }
            else{// não houve alterações no tabuleiro
                // não se dá continuidade
            }
        }
    }
    
    free(backUp);
    
   
}


void function(int ** array, int len, int moves, int value, int estadoD, int estadoU, int estadoL, int estadoR){
    //nos++;
    
    int** backUp = createArray(len);
    int x;
    int CanMerge = 0;
    int Changes = 0;
    int Copy = 1;
    
    int min = moves + ceil(log10(value)/log10(2));
    
    if(estadoD){
        
        dup(backUp, array, len);
        x = value-Down(backUp, len, &CanMerge, &Changes, &Copy);
        
        if(moves+1 + ceil(log10(x)/log10(2)) < Resposta){//cortar a recurção
        
            if(!(x-1)){
                Resposta = moves+1;
                //printf("encontrei: %d--------------------------------\n", Resposta);
                free(backUp);
                return; 
            }
        
        
            if(Changes){ // houve alterações notabuleiro
                if(value-x){// houve merge
                    if(CanMerge){ // ainda há possiveis merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 1); 
                    }
                    else{ // não é possivel fazer mais merges
                        function(backUp, len, moves+1, x, 0, 1, 1, 1); 
                    }
                }
                else{
                    function(backUp, len, moves+1, x, 0, 0, 1, 1);
                    // corta-se o up, caso contrio anulavamos o down
                }
                if(min >= Resposta){ // cortar ramificação
                    free(backUp);
                    return; 
                }
            }
            else{// não houve alterações no tabuleiro
                // não se dá continuidade
            }
        }
    
    }
    
    if(estadoL){
        CanMerge = 0;
        Changes = 0;
        
        if(Copy){ 
            dup(backUp, array, len);
        }
        else{
            Copy=1;
        }
        x = value-Left(backUp, len, &CanMerge, &Changes, &Copy);
        
        if(moves+1 + ceil(log10(x)/log10(2)) < Resposta){//cortar a recurção
        
            if(!(x-1)){
                Resposta = moves+1;
                //printf("encontrei: %d--------------------------------\n", Resposta);
                free(backUp);
                return; 
            }
            
            
            if(Changes){ // houve alterações notabuleiro
                if(value-x){// houve merge
                    if(CanMerge){ // ainda há possiveis merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 1); 
                    }
                    else{ // não é possivel fazer mais merges
                        function(backUp, len, moves+1, x, 1, 1, 0, 1); 
                    }
                }
                else{
                    function(backUp, len, moves+1, x, 1, 1, 0, 0);
                    // corta-se o up, caso contrio anulavamos o down
                }
                if(min >= Resposta){ // cortar ramificação
                    free(backUp);
                    return; 
                }
            }
            else{// não houve alterações no tabuleiro
                // não se dá continuidade
            }
        }
    
    }
    
    if(estadoU){
        CanMerge = 0;
        Changes = 0;
        
        if(Copy){ 
            dup(backUp, array, len);
        }
        else{
            Copy=1;
        }
        x = value-Up(backUp, len, &CanMerge, &Changes, &Copy);
        
        if(moves+1 + ceil(log10(x)/log10(2)) < Resposta){//cortar a recurção
        
            if(!(x-1)){
                Resposta = moves+1;
                //printf("encontrei: %d--------------------------------\n", Resposta);
                free(backUp);
                return; 
            }
            
            
            if(Changes){ // houve alterações notabuleiro
                if(value-x){// houve merge
                    if(CanMerge){ // ainda há possiveis merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 1); 
                    }
                    else{ // não é possivel fazer mais merges
                        function(backUp, len, moves+1, x, 1, 0, 1, 1); 
                    }
                }
                else{
                    function(backUp, len, moves+1, x, 0, 0, 1, 1);
                    // corta-se o up, caso contrio anulavamos o down
                }
                if(min >= Resposta){ // cortar ramificação
                    free(backUp);
                    return; 
                }
            }
            else{// não houve alterações no tabuleiro
                // não se dá continuidade
            }
        }
    
    }
    
    if(estadoR){
        CanMerge = 0;
        Changes = 0;
        
        if(Copy){ 
            dup(backUp, array, len);
        }
        else{
            Copy=1;
        }
        x = value-Right(backUp, len, &CanMerge, &Changes, &Copy);
        
        if(moves+1 + ceil(log10(x)/log10(2)) < Resposta){ //cortar a recurção
        
            if(!(x-1)){
                Resposta = moves+1;
                //printf("encontrei: %d--------------------------------\n", Resposta);
                free(backUp);
                return; 
            }
            
            if(Changes){ // houve alterações notabuleiro
                if(value-x){// houve merge
                    if(CanMerge){ // ainda há possiveis merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 1); 
                    }
                    else{ // não é possivel fazer mais merges
                        function(backUp, len, moves+1, x, 1, 1, 1, 0); 
                    }
                }
                else{
                    function(backUp, len, moves+1, x, 1, 1, 0, 0);
                    // corta-se o up, caso contrio anulavamos o down
                }
                if(min >= Resposta){ // cortar ramificação
                    free(backUp);
                    return; 
                }
            }
            else{// não houve alterações no tabuleiro
                // não se dá continuidade
            }
        }
    }
    
    free(backUp);
    
   
}

void scan(){
    int limite, n;
    
    scanf("%d %d", &n, &limite);
    
    int** array = createArray(n);
    
	for(int i = 0; i < n; i++){
	    scanf("%d", &array[i][0]);   
	    for(int j = 1; j < n; j++){
	        scanf(" %d", &array[i][j]);
	    }
	}

	Resposta = limite + 1;
	
	int Value = setValue(array, n);
	
	if(Value==-1){
	    free (array);
	    printf("no solution\n");
	    return;
	}
	if(ceil(log10(Value)/log10(2)) >= Resposta){
        free(array);
        printf("no solution\n");
        return;
    }
    
	function2(array, n, 0, Value, 1, 1, 1, 1);

	if(Resposta>limite){
	    printf("no solution\n");
	}
	else{
	    printf("%d\n", Resposta);
	}
	
	free(array);
}

int main() {
    int N;
    scanf("%d", &N);
    
    for(int i=0; i<N; i++){
        scan();
    }
	
	
    //printf("\n%d", nos);
    return 0;
}