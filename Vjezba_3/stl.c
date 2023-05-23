#include "stl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Object3D *readTextStl(FILE *fp){
    Object3D *out = (Object3D*)malloc(sizeof(Object3D));
    
    char *str0 = (char*)malloc(sizeof(char) * 100); //dummy string
    int lineCount = 0;
    int facetCount = 0;

    // //confirm file format
    // char* solidStr = (char*)malloc(sizeof(char) * 100);
    // fgets(solidStr, 100, fp);
    // sscanf(solidStr, "%s", solidStr);
    // if(strcmp(solidStr, "solid")){
    //    puts("Not an STL text file");
    // }
    // free(solidStr);
    // solidStr = (char*)NULL;
    // fseek(fp, 0, SEEK_SET);
    // //assume the rest is perfectly formatted

    //count lines
    while(!feof(fp)){
        if(fgetc(fp) == '\n'){
            lineCount++;
        }
    }
    fseek(fp, 0, SEEK_SET);

    facetCount = (lineCount - 2) / 7;
    out -> size = facetCount;

    //move to next line
    fgets(str0, 100, fp);
    free(str0);
    str0 = NULL;

    out -> tro = (trokut*)malloc(sizeof(trokut) * facetCount);

    for(int i = 0; i < facetCount; i++){
        fscanf(fp, " facet normal %f %f %f\n\
                         outer loop\n\
                             vertex %f %f %f\n\
                             vertex %f %f %f\n\
                             vertex %f %f %f\n\
                         endloop\n\
                     endfacet", \
                    &(out -> tro[i].n1), &(out -> tro[i].n2), &(out -> tro[i].n3), \
                    &(out -> tro[i].v1x), &(out -> tro[i].v1y), &(out -> tro[i].v1z), \
                    &(out -> tro[i].v2x), &(out -> tro[i].v2y), &(out -> tro[i].v2z), \
                    &(out -> tro[i].v3x), &(out -> tro[i].v3y), &(out -> tro[i].v3z));
                    
    }


    //printf("Nije se skršija!\n");

    return out;
}

void writeTextStl(Object3D *in, FILE *fp){
    char solidName[] = "BingChilling";

    fprintf(fp, "solid %s\n", solidName);

    for(int i = 0; i < in -> size; i++){
        fprintf(fp, " \
    facet normal %f %f %f\n\
        outer loop\n\
            vertex %f %f %f\n\
            vertex %f %f %f\n\
            vertex %f %f %f\n\
        tendloop\n\
    endfacet\n", \
                    in -> tro[i].n1, in -> tro[i].n2, in -> tro[i].n3, \
                    in -> tro[i].v1x, in -> tro[i].v1y, in -> tro[i].v1z, \
                    in -> tro[i].v2x, in -> tro[i].v2y, in -> tro[i].v2z, \
                    in -> tro[i].v3x, in -> tro[i].v3y, in -> tro[i].v3z);
                    
    }

    fprintf(fp, "endsolid %s\n", solidName);
}

Object3D *readBinStl(FILE *fp){
    Object3D *out = (Object3D*)malloc(sizeof(Object3D));

    //irrelevant header skip
    fseek(fp, 80, SEEK_SET);

    //read the number of triangles and malloc
    unsigned int size;
    fread(&(size), sizeof(unsigned int), 1, fp);
    out -> size = size;
    out -> tro = (trokut*)malloc(sizeof(trokut) * size);
    
    for(int i = 0; i < size; i++){
        fread(&(out -> tro[i].n1), sizeof(float), 12, fp);//same structure in struct and file, might as well read all at once
        fseek(fp, sizeof(unsigned short), SEEK_CUR);//more irrelevant skips
    }

    return out;
}

void writeBinStl(Object3D *in, FILE *fp){
    int zero = 0;//make fwrite happy

    for(int i = 0; i < 80; i++){
        fwrite(&(zero), 1, 1, fp);
    }

    fwrite(&(in -> size), sizeof(in -> size), 1, fp);

    for(int i = 0; i < in -> size; i++){
        fwrite(&(in -> tro[i].n1), sizeof(float), 12, fp);
        fwrite(&(zero), sizeof(unsigned short), 1, fp);
    }
}

void deleteObject3D(Object3D *in){
    free(in -> tro);
    free(in);
    in = NULL;
}