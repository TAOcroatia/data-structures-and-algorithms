#ifndef STL_H
#define STL_H
#include <stdio.h>

typedef struct{
    float n1, n2, n3;
    float v1x, v1y, v1z;
    float v2x, v2y, v2z;
    float v3x, v3y, v3z;
    unsigned short color;
}trokut;

typedef struct{
    trokut* tro;
    int size;
}Object3D;

Object3D *readTextStl(FILE *fp);
void writeTextStl(Object3D *in, FILE *fp);
Object3D *readBinStl(FILE *fp);
void writeBinStl(Object3D *in, FILE *fp);
void deleteObject3D(Object3D *in);

#endif