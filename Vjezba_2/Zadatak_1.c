#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float x, y;
}point;

typedef struct{
    point* dot;
    int pointCount;
}polygon;

polygon* new_polygon(float *arr_x, float *arr_y, int n){
    polygon* out = (polygon*)malloc(sizeof(polygon));
    out -> dot = (point*)malloc(sizeof(point) * n);
    
    for (int i = 0; i < n; i++){
        out -> dot[i].x = arr_x[i];
        out -> dot[i].y = arr_y[i];
    }
    out->pointCount = n;
    return out;
}

point** positive(polygon* p, int* np){
    point** out = (point**)malloc(sizeof(point*) * p -> pointCount);
    int newSize = 0;
    for (int i = 0; i < p -> pointCount; i++){
        if(p->dot[i].x > 0 && p->dot[i].y > 0){
            out[newSize] = &(p -> dot[i]);
            newSize++;
        }
    }
    *np = newSize;
    out = (point**)realloc(out, sizeof(point*) * *np);
    return out;
}

void arrPrint(int arrOrg[], int arrSize){
    int* arr = arrOrg;

    printf("[ ");
    for (int i = 0; i < arrSize; i++){
        int tmp = arr[i];
        printf("%d", tmp);
        if (i < arrSize - 1){
            printf(", ");
        }
    }
    printf(" ]\n");
}

int* podniz(int* arr, int start, int stop){
    int* out = (int*)malloc((stop - start) * sizeof(int));

    for (int i = start, j = 0; i <= stop; i++, j++){
        out[j] = arr[i];
    }

    return out;
}

int* filtriraj(int *niz, int n, int th, int *nth){
    int* out = (int*)malloc(n * sizeof(int));
    *nth = 0;

    for (int i = 0, j = 0; i < n; i++){
        if(niz[i] < th){
            out[j] = niz[i];
            j++;
        }
        *nth = j + 1;
    }

    out = (int*)realloc(out, (*nth - 1) * sizeof(int));

    return out;
}

int** podijeli(int *niz, int n){
    int odd = (n % 2 != 0);
    
    int* arr1 = (int*)malloc(n * sizeof(int));
    int* arr2 = (int*)malloc(n / 2 * sizeof(int) + odd);

    int** out = (int**)malloc(sizeof(int*) * 2);
    out[0] = arr1; out[1] = arr2;

    for (int i = 0; i < n / 2; i++){
        arr1[i] = niz[i];
    }
    int secArrStart = n / 2 + odd;
    for (int i = secArrStart; i < n; i++){
        arr2[i - secArrStart] = niz[i];
    }

    return out;
}

int main(){
    //podniz
    int arra[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int* newarra = podniz(arra, 4, 7);
    arrPrint(newarra, 3);
    free(newarra);
    newarra = NULL;

    //filtriraj
    int arra2[] = { 1, 7, 6, 4, 2, 6, 4, 5, 8, 9 };
    int newarra2Size;
    int* newarra2 = filtriraj(arra2, 10, 6, &newarra2Size);
    arrPrint(newarra2, newarra2Size);
    free(newarra2);
    newarra2 = NULL;

    //podijeli
    int** split = podijeli(arra, 10);
    arrPrint(*split, 4);
    arrPrint(*(split+1), 5);
    free(*split); free(*(split + 1));
    free(split);
    split = NULL;

    //poligoni i tocke
    float xArr[] = {-1, 2, 8, -7, 5, 6};
    float yArr[] = {2, 5, 47, 8, 9, 5};
    int size = 6;
    polygon* myPoly = new_polygon(xArr, yArr, size);
    printf("%0.2f\n", myPoly -> dot[0].x);
    int posSize;
    point** myPositive = positive(myPoly, &posSize);
    printf("%d %0.2f\n", posSize, myPositive[0]->x);
    
}