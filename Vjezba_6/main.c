
#include <stdio.h>
#include <stdlib.h>

#define PARENT(n) (((n) - 1) / 2)
#define LEFT(n) (2 * (n) + 1)
#define RIGHT(n) (2 * (n) + 2)

void arrPrint(int arrOrg[], int arrSize){
    int* arr = arrOrg;

    printf("[ ");
    for (int i = 0; i < arrSize; i+=4){// modded for element struct
        int tmp = arr[i];
        printf("%d", tmp);
        if (i < arrSize - 1){
            printf(", ");
        }
    }
    printf(" ]\n");
}

typedef struct{
    int n;
    void* data;
}element;

typedef struct{
    element* arr;
    int size, capacity;
}tree;

void initTree(tree* inTree, int cap){
    inTree->size = 0;
    inTree->capacity = cap;
    inTree->arr = (element*)malloc(sizeof(element) * cap);
}

void fixTreeAtIndexRec(tree* inTree, int r, int c, int l, int d){
    if(r >= inTree->size) return;
    if (!c){ //checks if it should go up or down based on the presence of the child variable
        int nextI = inTree->arr[l].n > inTree->arr[d].n ? l : d;
        if(inTree->arr[nextI].n > inTree->arr[r].n){
            element tmp = inTree->arr[nextI];
            inTree->arr[nextI] = inTree->arr[r];
            inTree->arr[r] = tmp;
        }
        fixTreeAtIndexRec(inTree, nextI, 0, LEFT(nextI), RIGHT(nextI));
    }
    if (c <= 0) return;

    if(inTree->arr[c].n > inTree->arr[r].n){
        element tmp = inTree->arr[c];
        inTree->arr[c] = inTree->arr[r];
        inTree->arr[r] = tmp;
        fixTreeAtIndexRec(inTree, PARENT(r), r, 0, 0);
    }
}

void addToTree(element a, tree* inTree){
    if(inTree->size >= inTree->capacity) return;

    inTree->arr[inTree->size] = a;
    inTree->size++;

    int size = inTree->size;

    if(size == 1) return;

    fixTreeAtIndexRec(inTree, PARENT(size - 1), size - 1, 0, 0);

    //iterative
    // for(int i = size - 1; i > 0; i = PARENT(i)){
    //     if(inTree->arr[i].n > inTree->arr[PARENT(i)].n){
    //         element tmp = inTree->arr[i];
    //         inTree->arr[i] = inTree->arr[PARENT(i)];
    //         inTree->arr[PARENT(i)] = tmp;
    //     }
    // }
}

tree* removeFromTree(tree* inTree){
    if(inTree->size == 0) return inTree;

    if(inTree->size == 1){
        inTree->arr[0].n = 0;
        inTree->size--;
        return inTree;
    }

    inTree->arr[0] = inTree->arr[inTree->size - 1];
    inTree->arr[inTree->size - 1] = {0, 0};
    inTree->size--;

    int size = inTree->size;

    fixTreeAtIndexRec(inTree, 0, 0, 1, 2);

    //iterative
    // for(int i = 0, nextI; i <= size - 1; i = nextI){
    //     nextI = inTree->arr[LEFT(i)].n > inTree->arr[RIGHT(i)].n ? LEFT(i) : RIGHT(i);
    //     if(inTree->arr[nextI].n > inTree->arr[i].n){
    //         element tmp = inTree->arr[nextI];
    //         inTree->arr[nextI] = inTree->arr[i];
    //         inTree->arr[i] = tmp;
    //     }
    // }

    return inTree;
}

int main() {
    tree stablo;
    
    initTree(&stablo, 10000);
    addToTree({151, 0}, &stablo);
    addToTree({130, 0}, &stablo);
    addToTree({256, 0}, &stablo);
    addToTree({140, 0}, &stablo);
    addToTree({125, 0}, &stablo);
    addToTree({45, 0}, &stablo);
    addToTree({89, 0}, &stablo);
    addToTree({645, 0}, &stablo);
    addToTree({212, 0}, &stablo);
    addToTree({111, 0}, &stablo);

    arrPrint((int*)stablo.arr, 50);

    while(stablo.size){
        stablo = *removeFromTree(&stablo);
        arrPrint((int*)stablo.arr, 50);
    }



    return 0;
}