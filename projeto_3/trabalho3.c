#include <stdio.h>
#include <stdlib.h>

int t;
int q;

typedef struct connection{
    int POI;
    int distance;
    struct connection* next;
} Connection;

typedef struct listNode{
    int POI;
    Connection* c;
    struct listNode* next;
} ListNode;

typedef struct Node{
    int POI;
    struct Node* next;
} node;

typedef struct circuit{
    node* Scc;
    struct circuit* next;
} Circuit;

int min(int a, int b){
    if(a<b) return a;
    return b;
}

Connection* PUSH(Connection* stack, int POI, int distance){
    Connection* c = (Connection*)malloc(sizeof(Connection)); 
    c->POI = POI;
    c->distance = distance;
    c->next = stack;
    return c;
}

node* push(node* stack, int POI){
    node* n = (node*)malloc(sizeof(node)); 
    n->POI = POI;
    n->next = stack;
    return n;
}

Circuit* Push(Circuit* stack, node* Scc){
    Circuit* c = (Circuit*)malloc(sizeof(Circuit)); 
    c->Scc = Scc;
    c->next = stack;
    return c;
}

node* pop(node* n){

    node* aux = n->next;
    //free(n);
    return aux;
}

Circuit* Pop(Circuit* c){

    Circuit* aux = c->next;
    //free(c);
    return aux;
}

void insert(ListNode* list, int POI, Connection* c){
    ListNode* node = list->next;
    ListNode* previous = list;
    
    ListNode* n = (ListNode*)malloc(sizeof(ListNode));
    n->POI = POI;
    n->c = c;
    
    while(node!=NULL){
        if(c->distance < node->c->distance){
            n->next = node;
            previous->next = n;
            return;
        }
        previous = previous->next;
        node = node->next;
    }
    previous->next = n;
}


// Union Find

int* set;
int* rank;

void make_set(node* Scc){
    node* n = Scc;
    while(n!=NULL){
        set[n->POI] = n->POI;
        rank[n->POI] = 0;
        n = n->next;
    }
}

void remove_set(node* Scc){
    node* n = Scc;
    while(n!=NULL){
        set[n->POI] = -1;
        rank[n->POI] = 0;
        n = n->next;
    }
}

void link(int a, int b){
    if(rank[a] > rank[b]){
        set[b] = a;
    }
    else{
        set[a] = b;
    }
    if (rank[a] == rank[b]){
        rank[b]++;
    }
}

int find(int a){
    if (set[a] != a){
        set[a] = find(set[a]);
    }
    return set[a];
}

void Union(int a, int b){
    link(find(a), find(b));
}

//Minimum Spanning Tree

int getLane(Connection** connections, node* Scc){
    
    make_set(Scc);
    
    ListNode* list= (ListNode*)malloc(sizeof(ListNode));
    
    node* n = Scc;
    while(n!=NULL){
        Connection* c = connections[n->POI];
        while(c!=NULL){
            if(set[c->POI]>0) {
                insert(list, n->POI, c);
            }
            c = c->next;
        }
        n = n->next;
    }
    
    
    /*
    ListNode* l = list->next;
    while(l!=NULL){
        printf("%d, ", l->c->distance);
        l = l->next;
    }
    printf("\n");
    */
    
    //ListNode* aux = list;
    list = list->next;
    //free(aux);
    
    int laneLength = 0;
    while(list!=NULL){
        if( find(list->POI) != find(list->c->POI) ){
            laneLength += list->c->distance;
            Union(list->POI, list->c->POI);
        }
        //faux = list;
        list = list->next;
        //free(aux);
    }
    remove_set(Scc);
    
    return laneLength;
}

// Strongly Connected Components

node* S;
Circuit* circuits;
int countCircuits;
int countPOIs;
int longestLane;
int totalLaneLength;

void findCircuits(Connection** connections, int* low, int* dfs, int* onStack, int v){
    low[v] = t;
    dfs[v] = t;
    t++;
    S = push(S, v);
    onStack[v]=1;
    
    Connection* c = connections[v];
    while(c!=NULL){
        if(!dfs[c->POI]){
            findCircuits(connections, low, dfs, onStack, c->POI);
            low[v] = min(low[v], low[c->POI]);
        }
        else if(onStack[v]){
            low[v] = min(low[v], dfs[c->POI]);
        }
        c = c->next;
    }
    
    if(low[v] == dfs[v]){
        int w = S->POI;
        S = pop(S);
        onStack[w]=0;
        node* Scc = push(NULL, w);
        int POIs = 1;
        while(w!=v){
            w = S->POI;
            S = pop(S);
            onStack[w]=0;
            Scc = push(Scc, w);
            POIs++;
        }
        if(POIs>1){
            circuits = Push(circuits, Scc);
            countCircuits++;
            if(POIs>countPOIs) countPOIs = POIs;
            if(q>2){
                int laneLength = getLane(connections, Scc);
                if(laneLength>longestLane) longestLane = laneLength;
                totalLaneLength += laneLength;
            }
        }
    }
}

void print(Circuit* circuit){
    Circuit* c = circuit;
    while(c!=NULL){
        node* Scc = c->Scc;
        while(Scc!=NULL){
            printf("%d -> ", Scc->POI);
            Scc = Scc->next;
        }
        printf("\n");
        c = c->next;
    }
}


int main()
{
    circuits = Push(circuits, NULL);
    S = push(NULL, -1);
    int testCases, n, m; 
    scanf("%d", &testCases);
    for(int i=0; i<testCases; i++){
        
        countCircuits = 0;
        countPOIs = 0;
        longestLane = 0;
        totalLaneLength = 0;
    
        
        scanf("%d %d %d", &n, &m, &q);
        
        if(n>1){
            
            int dfs[n];
            int low[n];
            int onStack[n];
            int parants[n];
            set = (int*) malloc(n*sizeof(int));
            rank = (int*) malloc(n*sizeof(int));
            Connection** connections = (Connection**) malloc(n*sizeof(Connection*));
            
            for(int j=0; j<n; j++){
                dfs[j] = 0;
                low[j] = 0;
                onStack[j] = 0;
                parants[0] = 0;
                set[j] = -1;
            }
            
            for(int j=0; j<m; j++){
                int A, B, D;
                scanf("%d %d %d", &A, &B, &D);
                connections[A-1] = PUSH(connections[A-1], B-1, D);
                parants[B-1]=1;
            }
            
            int v = 0;
            while(1){
                while(v<n){
                    if(dfs[v] || connections[v]==NULL || !parants[v]){
                        v++;
                        continue;
                    }
                    break;
                }
                if (v==n) break;
                t = 1;
                findCircuits(connections, low, dfs, onStack, v);
            }
        }
        
        //print(circuits);
        switch(q){
            case 4:
                printf("%d %d %d %d\n", countCircuits, countPOIs, longestLane, totalLaneLength);
                break;
            case 3:
                printf("%d %d %d\n", countCircuits, countPOIs, longestLane);
                break;
            case 2:
                printf("%d %d\n", countCircuits, countPOIs);
                break;
            default:
                printf("%d\n", countCircuits);
                break;
        }
    }
    

    return 0;
}
